#### Profiling tools
Liang Shi 写于 2015 <liangshi@hustunique.com> 
##### gprof - Displays profiling information.

    Get your program working!! gprof is not a debugger. Use it once you have a working program to optimize that program.
    Compile and link with the -pg option. If you use an Owen Astrachan patented makefile this simply means changing the CFLAGS variable.
    Run your program normally; that is, pretend you didn't do anything to it and do what you would normally do (checking difficult, slow, or fast cases, of course).
    Type gprof exec > out where exec is replaced by your executable's name and out by some meaningful name for the profiling information. For instance, if your executable were "foo" on the third run compiled with the -O2 option then you might type:

        gprof foo > run3.withO2.stats

    Look over the output and learn what it means. Hint, go to the second table. The first is pretty useless. To get there, search for "granularity" twice from the top of the file (in emacs, use C-s; in less or more use /).


##### valgrind - an instrumentation framework for building dynamic analysis tools.


##### nvprof
(最新的cuda似乎已经不推荐这个了？ 最新的profile工具看官网就好)

##### vampirTrace
- VampirTrace is an open source library that allows detailed logging of program execution for parallel applications using message passing (MPI) and threads (OpenMP), Pthreads). Besides these typical parallelization paradigms, VampirTrace is capable of tracing GPU accelerated applications and generates exact time stamps for all GPU related events.


##### IntelVTune 
适用于MPI应用，如果是想做体系结构的优化的话可以考虑用一下 Intel Advixe
(可以注册下载学生免费版)
