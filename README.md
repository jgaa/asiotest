# asiotest
Performance test for asio work-queues with and without strands

This program simply tests the raw performance of boost.asio as a thread-pool/work-queue.

The tests is aimed at simulating work-flows where something comes into the pool. Then some operations are performed, which puts something else onto the pool in the same thread, or in the same strand.

The test can run in two modes:

- One thread per asio context and any number of contexts
- One context, using strand's for synchronization with any number of threads and any number of strands.

For example, the following command:

```sh
./asiotest --threads 32 --calls 1000000 --callbacks 1000 --strands 1024
```

... will try to run the test on 32 cores (32 threads), entering 1 million tasks into the queue, each causing an additional 1 thousand tasks to be added to the strand picked for it's initial request. A total of one billion tasks should be processed. The initial tasks are added to strands in a round-robin fashion.


The test above executed on a Linux PC with a AMD Ryzen Threadripper 3970X 32-Core CPU:
```
$ ./asiotest --threads 32 --calls 1000000 --callbacks 1000 --strands 102400
[2020-03-31 17:37:10.021230] [0x00007f154925b780] [info]    Slot 0 finished 31,670,962 iterations in 3.83948 seconds, avg: 121 ns.
[2020-03-31 17:37:10.021265] [0x00007f154925b780] [info]    Slot 1 finished 30,917,293 iterations in 3.83942 seconds, avg: 124 ns.
[2020-03-31 17:37:10.021302] [0x00007f154925b780] [info]    Slot 2 finished 31,281,065 iterations in 3.83937 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021319] [0x00007f154925b780] [info]    Slot 3 finished 31,342,360 iterations in 3.83965 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021363] [0x00007f154925b780] [info]    Slot 4 finished 31,175,234 iterations in 3.83933 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021387] [0x00007f154925b780] [info]    Slot 5 finished 31,865,543 iterations in 3.83936 seconds, avg: 120 ns.
[2020-03-31 17:37:10.021409] [0x00007f154925b780] [info]    Slot 6 finished 30,757,235 iterations in 3.8394 seconds, avg: 124 ns.
[2020-03-31 17:37:10.021432] [0x00007f154925b780] [info]    Slot 7 finished 31,252,273 iterations in 3.8393 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021454] [0x00007f154925b780] [info]    Slot 8 finished 30,664,062 iterations in 3.83924 seconds, avg: 125 ns.
[2020-03-31 17:37:10.021475] [0x00007f154925b780] [info]    Slot 9 finished 31,314,775 iterations in 3.8392 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021498] [0x00007f154925b780] [info]    Slot 10 finished 31,852,039 iterations in 3.83918 seconds, avg: 120 ns.
[2020-03-31 17:37:10.021520] [0x00007f154925b780] [info]    Slot 11 finished 31,363,111 iterations in 3.83921 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021541] [0x00007f154925b780] [info]    Slot 12 finished 31,336,045 iterations in 3.83916 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021563] [0x00007f154925b780] [info]    Slot 13 finished 31,197,801 iterations in 3.83927 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021584] [0x00007f154925b780] [info]    Slot 14 finished 31,336,255 iterations in 3.83918 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021605] [0x00007f154925b780] [info]    Slot 15 finished 31,553,558 iterations in 3.83907 seconds, avg: 121 ns.
[2020-03-31 17:37:10.021627] [0x00007f154925b780] [info]    Slot 16 finished 30,605,282 iterations in 3.83918 seconds, avg: 125 ns.
[2020-03-31 17:37:10.021649] [0x00007f154925b780] [info]    Slot 17 finished 31,182,922 iterations in 3.83906 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021671] [0x00007f154925b780] [info]    Slot 18 finished 31,812,678 iterations in 3.83907 seconds, avg: 120 ns.
[2020-03-31 17:37:10.021695] [0x00007f154925b780] [info]    Slot 19 finished 31,189,952 iterations in 3.83905 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021718] [0x00007f154925b780] [info]    Slot 20 finished 31,009,630 iterations in 3.83893 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021739] [0x00007f154925b780] [info]    Slot 21 finished 31,126,506 iterations in 3.83895 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021762] [0x00007f154925b780] [info]    Slot 22 finished 31,046,888 iterations in 3.83894 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021783] [0x00007f154925b780] [info]    Slot 23 finished 31,383,499 iterations in 3.83892 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021805] [0x00007f154925b780] [info]    Slot 24 finished 30,702,565 iterations in 3.8389 seconds, avg: 125 ns.
[2020-03-31 17:37:10.021826] [0x00007f154925b780] [info]    Slot 25 finished 31,313,341 iterations in 3.83887 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021848] [0x00007f154925b780] [info]    Slot 26 finished 31,543,130 iterations in 3.83886 seconds, avg: 121 ns.
[2020-03-31 17:37:10.021869] [0x00007f154925b780] [info]    Slot 27 finished 31,186,893 iterations in 3.83891 seconds, avg: 123 ns.
[2020-03-31 17:37:10.021890] [0x00007f154925b780] [info]    Slot 28 finished 30,670,208 iterations in 3.83886 seconds, avg: 125 ns.
[2020-03-31 17:37:10.021911] [0x00007f154925b780] [info]    Slot 29 finished 31,278,678 iterations in 3.83881 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021932] [0x00007f154925b780] [info]    Slot 30 finished 31,784,914 iterations in 3.8388 seconds, avg: 120 ns.
[2020-03-31 17:37:10.021953] [0x00007f154925b780] [info]    Slot 31 finished 31,283,303 iterations in 3.83871 seconds, avg: 122 ns.
[2020-03-31 17:37:10.021970] [0x00007f154925b780] [info]    Single threaded context with 32 threads finished 1,000,000,000 iterations in 3.83293 seconds
[2020-03-31 17:37:10.021986] [0x00007f154925b780] [info]    Parallel average time with 102,400 strands was 3 ns.
```

The same test, without strands, but in stead with 32 asio contexts; each with one thread. The initial tasks are added to the contexts on a round-robin fashion. 

```
$ ./asiotest --threads 32 --calls 1000000 --callbacks 1000
[2020-03-31 17:43:01.307688] [0x00007fcd7aa0a780] [info]    Slot 0 finished 31,250,000 iterations in 1.96139 seconds, avg: 62 ns.
[2020-03-31 17:43:01.307798] [0x00007fcd7aa0a780] [info]    Slot 1 finished 31,250,000 iterations in 1.92797 seconds, avg: 61 ns.
[2020-03-31 17:43:01.307877] [0x00007fcd7aa0a780] [info]    Slot 2 finished 31,250,000 iterations in 1.95175 seconds, avg: 62 ns.
[2020-03-31 17:43:01.307949] [0x00007fcd7aa0a780] [info]    Slot 3 finished 31,250,000 iterations in 1.95628 seconds, avg: 62 ns.
[2020-03-31 17:43:01.308069] [0x00007fcd7aa0a780] [info]    Slot 4 finished 31,250,000 iterations in 1.93859 seconds, avg: 62 ns.
[2020-03-31 17:43:01.325276] [0x00007fcd7aa0a780] [info]    Slot 5 finished 31,250,000 iterations in 1.97918 seconds, avg: 63 ns.
[2020-03-31 17:43:01.325386] [0x00007fcd7aa0a780] [info]    Slot 6 finished 31,250,000 iterations in 1.92315 seconds, avg: 61 ns.
[2020-03-31 17:43:01.325472] [0x00007fcd7aa0a780] [info]    Slot 7 finished 31,250,000 iterations in 1.92417 seconds, avg: 61 ns.
[2020-03-31 17:43:01.325560] [0x00007fcd7aa0a780] [info]    Slot 8 finished 31,250,000 iterations in 1.9303 seconds, avg: 61 ns.
[2020-03-31 17:43:01.419634] [0x00007fcd7aa0a780] [info]    Slot 9 finished 31,250,000 iterations in 2.07342 seconds, avg: 66 ns.
[2020-03-31 17:43:01.419772] [0x00007fcd7aa0a780] [info]    Slot 10 finished 31,250,000 iterations in 1.91881 seconds, avg: 61 ns.
[2020-03-31 17:43:01.419880] [0x00007fcd7aa0a780] [info]    Slot 11 finished 31,250,000 iterations in 1.92861 seconds, avg: 61 ns.
[2020-03-31 17:43:01.419963] [0x00007fcd7aa0a780] [info]    Slot 12 finished 31,250,000 iterations in 1.98568 seconds, avg: 63 ns.
[2020-03-31 17:43:01.420077] [0x00007fcd7aa0a780] [info]    Slot 13 finished 31,250,000 iterations in 1.92995 seconds, avg: 61 ns.
[2020-03-31 17:43:01.442626] [0x00007fcd7aa0a780] [info]    Slot 14 finished 31,250,000 iterations in 2.09606 seconds, avg: 67 ns.
[2020-03-31 17:43:01.442713] [0x00007fcd7aa0a780] [info]    Slot 15 finished 31,250,000 iterations in 1.95066 seconds, avg: 62 ns.
[2020-03-31 17:43:01.442991] [0x00007fcd7aa0a780] [info]    Slot 16 finished 31,250,000 iterations in 1.97823 seconds, avg: 63 ns.
[2020-03-31 17:43:01.443075] [0x00007fcd7aa0a780] [info]    Slot 17 finished 31,250,000 iterations in 1.96519 seconds, avg: 62 ns.
[2020-03-31 17:43:01.443153] [0x00007fcd7aa0a780] [info]    Slot 18 finished 31,250,000 iterations in 1.99585 seconds, avg: 63 ns.
[2020-03-31 17:43:01.443233] [0x00007fcd7aa0a780] [info]    Slot 19 finished 31,250,000 iterations in 1.93663 seconds, avg: 61 ns.
[2020-03-31 17:43:01.443303] [0x00007fcd7aa0a780] [info]    Slot 20 finished 31,250,000 iterations in 1.90648 seconds, avg: 61 ns.
[2020-03-31 17:43:01.443385] [0x00007fcd7aa0a780] [info]    Slot 21 finished 31,250,000 iterations in 2.02254 seconds, avg: 64 ns.
[2020-03-31 17:43:01.443462] [0x00007fcd7aa0a780] [info]    Slot 22 finished 31,250,000 iterations in 1.94363 seconds, avg: 62 ns.
[2020-03-31 17:43:01.443551] [0x00007fcd7aa0a780] [info]    Slot 23 finished 31,250,000 iterations in 2.02747 seconds, avg: 64 ns.
[2020-03-31 17:43:01.443631] [0x00007fcd7aa0a780] [info]    Slot 24 finished 31,250,000 iterations in 2.06953 seconds, avg: 66 ns.
[2020-03-31 17:43:01.443716] [0x00007fcd7aa0a780] [info]    Slot 25 finished 31,250,000 iterations in 2.01921 seconds, avg: 64 ns.
[2020-03-31 17:43:01.443796] [0x00007fcd7aa0a780] [info]    Slot 26 finished 31,250,000 iterations in 2.05436 seconds, avg: 65 ns.
[2020-03-31 17:43:01.443866] [0x00007fcd7aa0a780] [info]    Slot 27 finished 31,250,000 iterations in 2.02737 seconds, avg: 64 ns.
[2020-03-31 17:43:01.551278] [0x00007fcd7aa0a780] [info]    Slot 28 finished 31,250,000 iterations in 2.2042 seconds, avg: 70 ns.
[2020-03-31 17:43:01.551442] [0x00007fcd7aa0a780] [info]    Slot 29 finished 31,250,000 iterations in 1.90092 seconds, avg: 60 ns.
[2020-03-31 17:43:01.551552] [0x00007fcd7aa0a780] [info]    Slot 30 finished 31,250,000 iterations in 1.98486 seconds, avg: 63 ns.
[2020-03-31 17:43:01.551657] [0x00007fcd7aa0a780] [info]    Slot 31 finished 31,250,000 iterations in 2.15544 seconds, avg: 68 ns.
[2020-03-31 17:43:01.551705] [0x00007fcd7aa0a780] [info]    Single threaded context with 32 threads finished 1,000,000,000 iterations in 2.20471 seconds
[2020-03-31 17:43:01.551715] [0x00007fcd7aa0a780] [info]    Parallel average time was 2 ns.
```
