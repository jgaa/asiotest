#include <iostream>
#include <memory>
#include <chrono>
#include <atomic>

#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

using namespace std;

struct Config {
    size_t io_threads = 1;
    size_t calls = 1000000;
    size_t callbacks = 32;
    size_t strands = 0;
};

class Timer {
public:
  Timer()
    : start_{std::chrono::steady_clock::now()} {}

  // Return elapsed time in nanoseconds
  auto elapsed() const {
      const auto ended = std::chrono::steady_clock::now();
      return chrono::duration_cast<chrono::nanoseconds>(ended - start_).count();
  }

  const decltype (std::chrono::steady_clock::now()) start_;
};


class BaseThread {
public:
    unique_ptr<thread> thrd;
    atomic_uint64_t cnt = {};
    Timer timer;
    uint64_t elapsed = {};
};

class SingleThread : public BaseThread{
public:
    SingleThread() {
        work = make_unique<boost::asio::io_service::work>(ctx);
        thrd = make_unique<thread>([&](){
            ctx.run();
        });
    }

    boost::asio::io_context ctx;
    unique_ptr<boost::asio::io_service::work> work;
};

class MultiThread : public BaseThread {
public:
    MultiThread(boost::asio::io_context& ctx) {
        thrd = make_unique<thread>([&](){
            bt = this;
            ctx.run();
        });
    }

    static thread_local BaseThread *bt;
};

BaseThread thread_local *MultiThread::bt = nullptr;

template<typename T>
void inner_call(const size_t i, BaseThread *base, const Config& cfg, T& ctx) {

    auto bt = base ? base : MultiThread::bt;
    ++bt->cnt;
    bt->elapsed = bt->timer.elapsed();

    if (i < cfg.callbacks) {
        boost::asio::post(ctx, [i, base, &cfg, &ctx]() {
            inner_call(i + 1, base, cfg, ctx);
        });
    }
}

std::string number(const uint64_t num) {
    stringstream out;
    out.imbue(std::locale{"en_US.UTF-8"});
    out << num;
    return out.str();
}

// Test with one asio context per thread
void single_thread(const Config& config) {

    std::vector<unique_ptr<SingleThread>> pool;

    for(size_t i = 0; i < config.io_threads; ++i) {
        pool.push_back(make_unique<SingleThread>());
    }

    Timer st_elapsed;

    // Start pounding requests into the task-queues
    for(size_t i = 0; i < config.calls; ++i) {
        const auto n = pool.size();
        const auto slot = i % n;
        auto& q = *pool[slot];
        boost::asio::post(q.ctx, [&config, &q]() {
            inner_call(1, &q, config, q.ctx);
        });
    }

    uint64_t iterations = {};
    // Remove the work objects so the threads can stop, and then join them
    for(size_t i = 0; i < pool.size(); ++i) {
        pool[i]->work.reset();
        pool[i]->thrd->join();
        iterations += pool[i]->cnt;
        BOOST_LOG_TRIVIAL(info) << "Slot " << i << " finished " << number(pool[i]->cnt) << " iterations in "
                                << (pool[i]->elapsed / 1000000000.0) << " seconds, avg: "
                                << (pool[i]->elapsed / pool[i]->cnt) << " ns.";
    }


    const auto elapsed = st_elapsed.elapsed();
    BOOST_LOG_TRIVIAL(info) << pool.size() << " Single threaded contexts finished "
                            << number(iterations)
                            << " iterations in " << (elapsed / 1000000000.0) << " seconds.";
    BOOST_LOG_TRIVIAL(info) << "Parallel average time was " << (elapsed / iterations) << " ns.";
    BOOST_LOG_TRIVIAL(info) << "Processed "
                            << number(iterations / (elapsed / 1000000000.0))
                            << " tasks per seconds.";
}

void multi_thread(const Config& config) {
    boost::asio::io_context ctx;
    auto work = make_unique<boost::asio::io_service::work>(ctx);

    std::vector<std::unique_ptr<MultiThread>> pool;
    for(size_t i = 0; i < config.io_threads; ++i) {
        pool.push_back(make_unique<MultiThread>(ctx));
    }

    std::vector<std::unique_ptr<boost::asio::io_context::strand>> strands;

    for(size_t i = 0; i < config.strands; ++i) {
        strands.push_back(make_unique<boost::asio::io_context::strand>(ctx));
    }

    Timer st_elapsed;

    // Start pounding requests into the task-queues
    for(size_t i = 0; i < config.calls; ++i) {
        const auto n = strands.size();
        const auto slot = i % n;
        auto& s = *strands[slot];
        boost::asio::post(s, [&config, &s]() {
            inner_call(1, nullptr, config, s);
        });
    }

    uint64_t iterations = {};
    // Remove the work objects so the threads can stop, and then join them
    work.reset();
    for(size_t i = 0; i < pool.size(); ++i) {
        pool[i]->thrd->join();
        iterations += pool[i]->cnt;
        BOOST_LOG_TRIVIAL(info) << "Slot " << i << " finished " << number(pool[i]->cnt) << " iterations in "
                                << (pool[i]->elapsed / 1000000000.0) << " seconds, avg: "
                                << (pool[i]->elapsed / pool[i]->cnt) << " ns.";
    }


    const auto elapsed = st_elapsed.elapsed();
    BOOST_LOG_TRIVIAL(info) << "Shared context with " << pool.size() << " threads finished "
                            << number(iterations)
                            << " iterations in " << (elapsed / 1000000000.0) << " seconds.";
    BOOST_LOG_TRIVIAL(info) << "Parallel average time with "
                            << number(config.strands)
                            <<" strands was " << (elapsed / iterations) << " ns.";
    BOOST_LOG_TRIVIAL(info) << "Processed "
                            << number(iterations / (elapsed / 1000000000.0))
                            << " tasks per seconds.";
}

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    namespace logging = boost::log;

    Config config;
    string log_level;

    po::options_description general("General Options");

    general.add_options()
        ("help,h", "Print help and exit")
        ("log-level,l", po::value<string>(&log_level)->default_value("info"),
            "Log-level for the log-file")
        ;

    po::options_description testopts("Test Options");
    testopts.add_options()
        ("threads", po::value<size_t>(&config.io_threads)->default_value(config.io_threads),
            "Number of IO threads.")
        ("calls", po::value<size_t>(&config.calls)->default_value(config.calls),
            "Number of calls to measure.")
        ("callbacks", po::value<size_t>(&config.callbacks)->default_value(config.callbacks),
            "Number of callbacks to call for each call.")
        ("strands", po::value<size_t>(&config.strands)->default_value(config.strands),
            "Number of strands (will run all io-threads in the same asio context).")
        ;

    po::options_description cmdline_options;
    cmdline_options.add(general).add(testopts);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << cmdline_options << endl
            << "Log-levels are:" << endl
            << "   trace debug info " << endl;

        return -2;
    }

    auto llevel = logging::trivial::info;
    if (log_level == "debug") {
        llevel = logging::trivial::debug;
    } else if (log_level == "trace") {
        llevel = logging::trivial::trace;
    } else if (log_level == "info") {
        ; // Do nothing
    } else {
        std::cerr << "Unknown log-level: " << log_level << endl;
        return  -1;
    }

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= llevel
    );

    if (config.strands) {
        multi_thread(config);
    } else {
        single_thread(config);
    }

    return 0;
}
