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
[2020-04-01 09:42:47.175031] [0x00007f4648155780] [info]    Slot 0 finished 31,679,796 iterations in 3.87481 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175071] [0x00007f4648155780] [info]    Slot 1 finished 31,473,359 iterations in 3.87481 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175095] [0x00007f4648155780] [info]    Slot 2 finished 31,148,306 iterations in 3.87658 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175181] [0x00007f4648155780] [info]    Slot 3 finished 31,319,125 iterations in 3.87477 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175231] [0x00007f4648155780] [info]    Slot 4 finished 29,356,964 iterations in 3.87468 seconds, avg: 131 ns.
[2020-04-01 09:42:47.175258] [0x00007f4648155780] [info]    Slot 5 finished 31,580,733 iterations in 3.87467 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175283] [0x00007f4648155780] [info]    Slot 6 finished 31,694,234 iterations in 3.87466 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175308] [0x00007f4648155780] [info]    Slot 7 finished 31,105,697 iterations in 3.87476 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175330] [0x00007f4648155780] [info]    Slot 8 finished 31,276,209 iterations in 3.87463 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175353] [0x00007f4648155780] [info]    Slot 9 finished 31,395,618 iterations in 3.87471 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175374] [0x00007f4648155780] [info]    Slot 10 finished 31,358,356 iterations in 3.87462 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175396] [0x00007f4648155780] [info]    Slot 11 finished 31,737,924 iterations in 3.87464 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175417] [0x00007f4648155780] [info]    Slot 12 finished 31,328,266 iterations in 3.87466 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175438] [0x00007f4648155780] [info]    Slot 13 finished 31,683,612 iterations in 3.87464 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175460] [0x00007f4648155780] [info]    Slot 14 finished 31,969,264 iterations in 3.87453 seconds, avg: 121 ns.
[2020-04-01 09:42:47.175481] [0x00007f4648155780] [info]    Slot 15 finished 31,353,333 iterations in 3.87465 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175503] [0x00007f4648155780] [info]    Slot 16 finished 31,253,366 iterations in 3.87602 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175531] [0x00007f4648155780] [info]    Slot 17 finished 29,572,568 iterations in 3.87447 seconds, avg: 131 ns.
[2020-04-01 09:42:47.175553] [0x00007f4648155780] [info]    Slot 18 finished 31,328,431 iterations in 3.87437 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175575] [0x00007f4648155780] [info]    Slot 19 finished 31,425,232 iterations in 3.87436 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175598] [0x00007f4648155780] [info]    Slot 20 finished 30,718,521 iterations in 3.87435 seconds, avg: 126 ns.
[2020-04-01 09:42:47.175620] [0x00007f4648155780] [info]    Slot 21 finished 31,178,808 iterations in 3.8744 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175641] [0x00007f4648155780] [info]    Slot 22 finished 31,434,917 iterations in 3.87434 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175663] [0x00007f4648155780] [info]    Slot 23 finished 31,052,430 iterations in 3.87426 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175683] [0x00007f4648155780] [info]    Slot 24 finished 31,536,040 iterations in 3.87435 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175704] [0x00007f4648155780] [info]    Slot 25 finished 30,895,389 iterations in 3.87452 seconds, avg: 125 ns.
[2020-04-01 09:42:47.175725] [0x00007f4648155780] [info]    Slot 26 finished 30,894,524 iterations in 3.87426 seconds, avg: 125 ns.
[2020-04-01 09:42:47.175747] [0x00007f4648155780] [info]    Slot 27 finished 31,438,902 iterations in 3.87427 seconds, avg: 123 ns.
[2020-04-01 09:42:47.175768] [0x00007f4648155780] [info]    Slot 28 finished 31,223,129 iterations in 3.87453 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175789] [0x00007f4648155780] [info]    Slot 29 finished 31,801,310 iterations in 3.87421 seconds, avg: 121 ns.
[2020-04-01 09:42:47.175809] [0x00007f4648155780] [info]    Slot 30 finished 31,088,457 iterations in 3.87416 seconds, avg: 124 ns.
[2020-04-01 09:42:47.175831] [0x00007f4648155780] [info]    Slot 31 finished 31,697,180 iterations in 3.87415 seconds, avg: 122 ns.
[2020-04-01 09:42:47.175848] [0x00007f4648155780] [info]    Shared context with 32 threads finished 1,000,000,000 iterations in 3.86896 seconds.
[2020-04-01 09:42:47.175863] [0x00007f4648155780] [info]    Parallel average time with 102,400 strands was 3 ns.
[2020-04-01 09:42:47.175880] [0x00007f4648155780] [info]    Processed 258,467,580 tasks per seconds.

```

The same test, without strands, but in stead with 32 asio contexts; each with one thread. The initial tasks are added to the contexts on a round-robin fashion. 

```
$ ./asiotest --threads 32 --calls 1000000 --callbacks 1000 
[2020-04-01 09:43:13.490074] [0x00007f9ec999f780] [info]    Slot 0 finished 31,250,000 iterations in 1.95279 seconds, avg: 62 ns.
[2020-04-01 09:43:13.504570] [0x00007f9ec999f780] [info]    Slot 1 finished 31,250,000 iterations in 1.96753 seconds, avg: 62 ns.
[2020-04-01 09:43:13.504646] [0x00007f9ec999f780] [info]    Slot 2 finished 31,250,000 iterations in 1.96191 seconds, avg: 62 ns.
[2020-04-01 09:43:13.525259] [0x00007f9ec999f780] [info]    Slot 3 finished 31,250,000 iterations in 1.98813 seconds, avg: 63 ns.
[2020-04-01 09:43:13.525386] [0x00007f9ec999f780] [info]    Slot 4 finished 31,250,000 iterations in 1.95942 seconds, avg: 62 ns.
[2020-04-01 09:43:13.525482] [0x00007f9ec999f780] [info]    Slot 5 finished 31,250,000 iterations in 1.9605 seconds, avg: 62 ns.
[2020-04-01 09:43:13.525587] [0x00007f9ec999f780] [info]    Slot 6 finished 31,250,000 iterations in 1.95921 seconds, avg: 62 ns.
[2020-04-01 09:43:13.525669] [0x00007f9ec999f780] [info]    Slot 7 finished 31,250,000 iterations in 1.90446 seconds, avg: 60 ns.
[2020-04-01 09:43:13.525766] [0x00007f9ec999f780] [info]    Slot 8 finished 31,250,000 iterations in 1.93135 seconds, avg: 61 ns.
[2020-04-01 09:43:13.525842] [0x00007f9ec999f780] [info]    Slot 9 finished 31,250,000 iterations in 1.92597 seconds, avg: 61 ns.
[2020-04-01 09:43:13.525918] [0x00007f9ec999f780] [info]    Slot 10 finished 31,250,000 iterations in 1.91803 seconds, avg: 61 ns.
[2020-04-01 09:43:13.525980] [0x00007f9ec999f780] [info]    Slot 11 finished 31,250,000 iterations in 1.91691 seconds, avg: 61 ns.
[2020-04-01 09:43:13.532209] [0x00007f9ec999f780] [info]    Slot 12 finished 31,250,000 iterations in 1.99487 seconds, avg: 63 ns.
[2020-04-01 09:43:13.532305] [0x00007f9ec999f780] [info]    Slot 13 finished 31,250,000 iterations in 1.94109 seconds, avg: 62 ns.
[2020-04-01 09:43:13.532408] [0x00007f9ec999f780] [info]    Slot 14 finished 31,250,000 iterations in 1.94148 seconds, avg: 62 ns.
[2020-04-01 09:43:13.532504] [0x00007f9ec999f780] [info]    Slot 15 finished 31,250,000 iterations in 1.9258 seconds, avg: 61 ns.
[2020-04-01 09:43:13.537323] [0x00007f9ec999f780] [info]    Slot 16 finished 31,250,000 iterations in 1.99991 seconds, avg: 63 ns.
[2020-04-01 09:43:13.537422] [0x00007f9ec999f780] [info]    Slot 17 finished 31,250,000 iterations in 1.92637 seconds, avg: 61 ns.
[2020-04-01 09:43:13.547654] [0x00007f9ec999f780] [info]    Slot 18 finished 31,250,000 iterations in 2.01021 seconds, avg: 64 ns.
[2020-04-01 09:43:13.635801] [0x00007f9ec999f780] [info]    Slot 19 finished 31,250,000 iterations in 2.09831 seconds, avg: 67 ns.
[2020-04-01 09:43:13.755868] [0x00007f9ec999f780] [info]    Slot 20 finished 31,250,000 iterations in 2.21834 seconds, avg: 70 ns.
[2020-04-01 09:43:13.755962] [0x00007f9ec999f780] [info]    Slot 21 finished 31,250,000 iterations in 2.13287 seconds, avg: 68 ns.
[2020-04-01 09:43:13.756055] [0x00007f9ec999f780] [info]    Slot 22 finished 31,250,000 iterations in 1.9688 seconds, avg: 63 ns.
[2020-04-01 09:43:13.771097] [0x00007f9ec999f780] [info]    Slot 23 finished 31,250,000 iterations in 2.2335 seconds, avg: 71 ns.
[2020-04-01 09:43:13.771203] [0x00007f9ec999f780] [info]    Slot 24 finished 31,250,000 iterations in 1.98982 seconds, avg: 63 ns.
[2020-04-01 09:43:13.771281] [0x00007f9ec999f780] [info]    Slot 25 finished 31,250,000 iterations in 2.00453 seconds, avg: 64 ns.
[2020-04-01 09:43:13.771368] [0x00007f9ec999f780] [info]    Slot 26 finished 31,250,000 iterations in 2.12923 seconds, avg: 68 ns.
[2020-04-01 09:43:13.771442] [0x00007f9ec999f780] [info]    Slot 27 finished 31,250,000 iterations in 2.22 seconds, avg: 71 ns.
[2020-04-01 09:43:13.771518] [0x00007f9ec999f780] [info]    Slot 28 finished 31,250,000 iterations in 2.01376 seconds, avg: 64 ns.
[2020-04-01 09:43:13.771599] [0x00007f9ec999f780] [info]    Slot 29 finished 31,250,000 iterations in 2.01868 seconds, avg: 64 ns.
[2020-04-01 09:43:13.771668] [0x00007f9ec999f780] [info]    Slot 30 finished 31,250,000 iterations in 2.12107 seconds, avg: 67 ns.
[2020-04-01 09:43:13.771736] [0x00007f9ec999f780] [info]    Slot 31 finished 31,250,000 iterations in 2.15635 seconds, avg: 69 ns.
[2020-04-01 09:43:13.771767] [0x00007f9ec999f780] [info]    32 Single threaded contexts finished 1,000,000,000 iterations in 2.23406 seconds.
[2020-04-01 09:43:13.771773] [0x00007f9ec999f780] [info]    Parallel average time was 2 ns.
[2020-04-01 09:43:13.771800] [0x00007f9ec999f780] [info]    Processed 447,614,812 tasks per seconds.
```

And the latest test with 64 threads:

```
./asiotest --threads 64 --calls 1000000 --callbacks 1000 
[2020-04-01 09:43:39.753869] [0x00007f8612e04780] [info]    Slot 0 finished 15,625,000 iterations in 1.40092 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754002] [0x00007f8612e04780] [info]    Slot 1 finished 15,625,000 iterations in 1.39764 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754098] [0x00007f8612e04780] [info]    Slot 2 finished 15,625,000 iterations in 1.40015 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754186] [0x00007f8612e04780] [info]    Slot 3 finished 15,625,000 iterations in 1.39998 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754277] [0x00007f8612e04780] [info]    Slot 4 finished 15,625,000 iterations in 1.39993 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754333] [0x00007f8612e04780] [info]    Slot 5 finished 15,625,000 iterations in 1.39795 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754415] [0x00007f8612e04780] [info]    Slot 6 finished 15,625,000 iterations in 1.39909 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754488] [0x00007f8612e04780] [info]    Slot 7 finished 15,625,000 iterations in 1.39725 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754559] [0x00007f8612e04780] [info]    Slot 8 finished 15,625,000 iterations in 1.39725 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754618] [0x00007f8612e04780] [info]    Slot 9 finished 15,625,000 iterations in 1.3972 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754696] [0x00007f8612e04780] [info]    Slot 10 finished 15,625,000 iterations in 1.3985 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754753] [0x00007f8612e04780] [info]    Slot 11 finished 15,625,000 iterations in 1.39875 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754810] [0x00007f8612e04780] [info]    Slot 12 finished 15,625,000 iterations in 1.3991 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754866] [0x00007f8612e04780] [info]    Slot 13 finished 15,625,000 iterations in 1.39712 seconds, avg: 89 ns.
[2020-04-01 09:43:39.754949] [0x00007f8612e04780] [info]    Slot 14 finished 15,625,000 iterations in 1.39841 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755179] [0x00007f8612e04780] [info]    Slot 15 finished 15,625,000 iterations in 1.40191 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755240] [0x00007f8612e04780] [info]    Slot 16 finished 15,625,000 iterations in 1.39707 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755297] [0x00007f8612e04780] [info]    Slot 17 finished 15,625,000 iterations in 1.39704 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755353] [0x00007f8612e04780] [info]    Slot 18 finished 15,625,000 iterations in 1.39923 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755415] [0x00007f8612e04780] [info]    Slot 19 finished 15,625,000 iterations in 1.397 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755470] [0x00007f8612e04780] [info]    Slot 20 finished 15,625,000 iterations in 1.39698 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755524] [0x00007f8612e04780] [info]    Slot 21 finished 15,625,000 iterations in 1.39696 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755572] [0x00007f8612e04780] [info]    Slot 22 finished 15,625,000 iterations in 1.39712 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755618] [0x00007f8612e04780] [info]    Slot 23 finished 15,625,000 iterations in 1.39866 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755662] [0x00007f8612e04780] [info]    Slot 24 finished 15,625,000 iterations in 1.40209 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755710] [0x00007f8612e04780] [info]    Slot 25 finished 15,625,000 iterations in 1.39688 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755760] [0x00007f8612e04780] [info]    Slot 26 finished 15,625,000 iterations in 1.39844 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755808] [0x00007f8612e04780] [info]    Slot 27 finished 15,625,000 iterations in 1.39684 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755852] [0x00007f8612e04780] [info]    Slot 28 finished 15,625,000 iterations in 1.39704 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755903] [0x00007f8612e04780] [info]    Slot 29 finished 15,625,000 iterations in 1.39812 seconds, avg: 89 ns.
[2020-04-01 09:43:39.755942] [0x00007f8612e04780] [info]    Slot 30 finished 15,625,000 iterations in 1.39678 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756011] [0x00007f8612e04780] [info]    Slot 31 finished 15,625,000 iterations in 1.39815 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756057] [0x00007f8612e04780] [info]    Slot 32 finished 15,625,000 iterations in 1.3988 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756103] [0x00007f8612e04780] [info]    Slot 33 finished 15,625,000 iterations in 1.39686 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756147] [0x00007f8612e04780] [info]    Slot 34 finished 15,625,000 iterations in 1.3967 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756195] [0x00007f8612e04780] [info]    Slot 35 finished 15,625,000 iterations in 1.39668 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756247] [0x00007f8612e04780] [info]    Slot 36 finished 15,625,000 iterations in 1.39666 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756297] [0x00007f8612e04780] [info]    Slot 37 finished 15,625,000 iterations in 1.39824 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756340] [0x00007f8612e04780] [info]    Slot 38 finished 15,625,000 iterations in 1.39816 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756385] [0x00007f8612e04780] [info]    Slot 39 finished 15,625,000 iterations in 1.39969 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756429] [0x00007f8612e04780] [info]    Slot 40 finished 15,625,000 iterations in 1.39658 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756474] [0x00007f8612e04780] [info]    Slot 41 finished 15,625,000 iterations in 1.39657 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756540] [0x00007f8612e04780] [info]    Slot 42 finished 15,625,000 iterations in 1.39655 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756587] [0x00007f8612e04780] [info]    Slot 43 finished 15,625,000 iterations in 1.39653 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756633] [0x00007f8612e04780] [info]    Slot 44 finished 15,625,000 iterations in 1.39651 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756678] [0x00007f8612e04780] [info]    Slot 45 finished 15,625,000 iterations in 1.39649 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756727] [0x00007f8612e04780] [info]    Slot 46 finished 15,625,000 iterations in 1.39783 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756777] [0x00007f8612e04780] [info]    Slot 47 finished 15,625,000 iterations in 1.39653 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756825] [0x00007f8612e04780] [info]    Slot 48 finished 15,625,000 iterations in 1.39874 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756881] [0x00007f8612e04780] [info]    Slot 49 finished 15,625,000 iterations in 1.3964 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756921] [0x00007f8612e04780] [info]    Slot 50 finished 15,625,000 iterations in 1.39855 seconds, avg: 89 ns.
[2020-04-01 09:43:39.756972] [0x00007f8612e04780] [info]    Slot 51 finished 15,625,000 iterations in 1.3966 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757024] [0x00007f8612e04780] [info]    Slot 52 finished 15,625,000 iterations in 1.39802 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757064] [0x00007f8612e04780] [info]    Slot 53 finished 15,625,000 iterations in 1.39633 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757111] [0x00007f8612e04780] [info]    Slot 54 finished 15,625,000 iterations in 1.3964 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757177] [0x00007f8612e04780] [info]    Slot 55 finished 15,625,000 iterations in 1.3963 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757227] [0x00007f8612e04780] [info]    Slot 56 finished 15,625,000 iterations in 1.39777 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757275] [0x00007f8612e04780] [info]    Slot 57 finished 15,625,000 iterations in 1.39626 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757319] [0x00007f8612e04780] [info]    Slot 58 finished 15,625,000 iterations in 1.39624 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757365] [0x00007f8612e04780] [info]    Slot 59 finished 15,625,000 iterations in 1.39622 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757406] [0x00007f8612e04780] [info]    Slot 60 finished 15,625,000 iterations in 1.39619 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757455] [0x00007f8612e04780] [info]    Slot 61 finished 15,625,000 iterations in 1.39761 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757521] [0x00007f8612e04780] [info]    Slot 62 finished 15,625,000 iterations in 1.39616 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757568] [0x00007f8612e04780] [info]    Slot 63 finished 15,625,000 iterations in 1.39613 seconds, avg: 89 ns.
[2020-04-01 09:43:39.757585] [0x00007f8612e04780] [info]    64 Single threaded contexts finished 1,000,000,000 iterations in 1.40333 seconds.
[2020-04-01 09:43:39.757589] [0x00007f8612e04780] [info]    Parallel average time was 1 ns.
[2020-04-01 09:43:39.757604] [0x00007f8612e04780] [info]    Processed 712,589,780 tasks per seconds.
```

And just for comparsion, 1 thread with and without strand
```
$ ./asiotest --threads 1 --calls 1000000 --callbacks 1000 --strand 1
[2020-04-01 09:46:45.323359] [0x00007fe0fac5e780] [info]    Slot 0 finished 1,000,000,000 iterations in 43.9473 seconds, avg: 43 ns.
[2020-04-01 09:46:45.323421] [0x00007fe0fac5e780] [info]    Shared context with 1 threads finished 1,000,000,000 iterations in 43.9567 seconds.
[2020-04-01 09:46:45.323473] [0x00007fe0fac5e780] [info]    Parallel average time with 1 strands was 43 ns.
[2020-04-01 09:46:45.323504] [0x00007fe0fac5e780] [info]    Processed 22,749,677 tasks per seconds.

$ ./asiotest --threads 1 --calls 1000000 --callbacks 1000 
[2020-04-01 09:45:33.209863] [0x00007f95c8a88780] [info]    Slot 0 finished 1,000,000,000 iterations in 57.0638 seconds, avg: 57 ns.
[2020-04-01 09:45:33.209934] [0x00007f95c8a88780] [info]    1 Single threaded contexts finished 1,000,000,000 iterations in 57.0741 seconds.
[2020-04-01 09:45:33.209962] [0x00007f95c8a88780] [info]    Parallel average time was 57 ns.
[2020-04-01 09:45:33.210000] [0x00007f95c8a88780] [info]    Processed 17,521,080 tasks per seconds. 
```
