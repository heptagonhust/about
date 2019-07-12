# 关于
这个repo为华科七边形于2019年整理，欢迎各位朋友的指教

部分内容如有侵权，请联系 Rao, Geng Yu <zouyoo@outlook.com>,我们会尽快移除

# 加入我们
   请联系每年负责的同学，请安排好个人的时间（ 时间安排可以参考下面的比赛列表 ），避免产生不必要的咕咕咕行为
   
   近年，华科一般团队组成为：一名运维（或许队长也要兼任部分运维职务，一个人可能不够），其他人分成组，负责写各个题目的代码。
   
   AI题太多变了，一般出题之后找专门有研究的人来做，需要几个人跟着帮忙。
   
   我们希望从每年9月份的新大二中招人，具体的情况请联系当年的队长。
   
   不同学校队伍之间的比较：
  * 有的学校没有专门的运维，每个人都有运维的能力。
  * 有的学校有很多队员是在做科学计算的 CS/非CS 学生，清北的朋友一般能找到很多这方面的资源，他们学校也有很多做相关科学研究的教师，近年华科主要还是纯粹CS的，没有专门做科学计算的其他系的学生

# 如何预防鸽子? 
一旦遇到了鸽子，对整个团队的规划会产生非常大的影响，如果有人要中途退出，一定尽快说明，并重新分配任务。
一般造成鸽子的原因：

    *寒假一直在写课设
    *准备找工作
    *远程参与

# 比赛列表和一般推荐时间表

大二暑假</br>
[RDMA](http://hpcadvisorycouncil.com/events/2019/rdma/) </br>
[PAC](http://www.pac-hpc.com/index.php)</br>
[CPC国产CPU](http://www.cpc-hpc.com/) 可以借机会接触一下神威[太湖之光](http://www.nsccwx.cn/process.php?word=process&i=54) </br>
大三和大四</br>
[ASC](https://www.asc-events.org/ASC19/)</br>
[ISC](https://www.isc-hpc.com/student-cluster-competition-2019.html)</br>
[SC](http://www.studentclustercompetition.us/)</br>



#### 代码：

    深入理解 linux 内核 （RGY：对超算应用或许不是很重要？）
    现代操作系统（基础知识，选一些章节看就好了）（RGY：同上）

    多核应用编程实战（入门）
    计算机科学丛书：高性能科学与工程计算（入门）

    编译工具链相关文档（这个repo里也有整理编译相关的东西）
    CUDA 并行程序设计：GPU 编程指南 （学校图书馆有）（CUDA programming : a developer's guide to parallel computing with GPUS）
    MIC 相关书籍 （最近很少有了，不推荐新人啃）
    看别人各种调优的文档和优化建议（如果是大型的应用的话，一般有相关文档）

#### RDMA
[here](https://github.com/heptagonhust/about/blob/master/RDMA.md)
#### MPI编程入门
[here](https://github.com/heptagonhust/about/blob/master/MPI&openMP/README.md)

#### GPGPU
[here](https://github.com/heptagonhust/about/blob/master/GPGPU&MIC/readme.md)
#### 运维
[here](https://github.com/heptagonhust/about/blob/master/运维.md)
#### HPC 从什么都不会到入门（2016年的整理？）
团队分工

    机器组装, 硬件搭配
    linux, 系统维护
    英语交流, 与老师合作
    并行化 异构计算 coder
    [数学建模] [数值计算]

题目

    HPL HPCG HPCC 性能测试（不需要代码修改）
    
    AI题，可以看我在另一个文件夹下的整理，因为这几年（-19）每年都有，并且AI题出题风格各异，AI细分的方向比较多，在出题之前找专门做AI的人比较难。建议出题了之后，找擅长的人，然后借南一楼集群的P100机器。一般都是 state of art 的题目，可能需要实现最新的论文


    神秘应用
    一般是编译后直接跑, 要求对编译和环境非常熟悉（注意坑（oom等），需要快速找到最佳/时间上最经济的跑法）


    团队题：预计编译过程会非常非常的难
    ASC19新出的一种赛题，一般是强校弄出docker/其他打包，然后给其他队友
    
    真正的超算平台
    今年是神威, 这个题目不在自己组装的机器上跑, 要求的代码能力很强, 综合素质强 （只他们那一年有过这种，神威相关的信息在这个repo也有整理）
    


工具

    redhat 有系统性能优化和系统管理员文档
    openmp
    一般与 mpi 混合使用, 方便但其空间有限

    mpi
    有 openmpi intel-mpi mpich2 platform-mpi
    一般 CUDA 程序常用 openmpi
    一般 intel-mpi 性能更好（还是一个个都测试一遍吧）
    注意 numa 双路 cpu 对内存访问不对称, 及核绑定避免线程切换

    intel parallel studio
    icc ifort intel-mpi intel-optimize-header intel-mathlib（MKL）
    advisor inspector vtune 性能分析工具
    优化文档也是必读, 重点掌握

    cuda
    NVIDIA套装

    openacc OpenCL
    通用多平台编程, 用的很少，有很多坑（但是并不推荐新人在知道题目之前，就学这个）

    Doxygen（使用doxywizard，勾选上 Expert/Dot 里的各种*_GRAPH）

    链接库
    **换库** , 数学计算有 BLAS 等数学库,需要对比不同库的速度。
    fft有fftw和其他的实现，intel MKL 实现了兼容fftw的接口 （ASC19从一个fft99的库改成了fftw）
    fftw的性能有不少窍门：plan，关于是在当前的内存空间做fft还是输入输出在不同的array，这些对性能有不少影响

另外

做超算算很多事情很杂, 很多优化可能相当繁琐, 也有很多参数和库可以调, 代码 debug 起来也很困难, 环境还有巨多坑,
做起题目来不要乱, 从顶至底一步一步来, 少做 dirty 的事情, 保持任务分工明确, 然后把所有优化的点都重视起来, 多交流


之前比赛的[文档积累](https://gitlab.com/heptagonhust/),telegram群，请联系 [Y00](https://t.me/anon_yoo) 进入
