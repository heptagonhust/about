### MPI编程入门
https://github.com/wesleykendall/mpitutorial</br>
http://mpitutorial.com/recommended-books/ </br>
TACC的教授写的两个教程，可以看看[mpi的部分](https://bitbucket.org/VictorEijkhout/parallel-computing-book/src/db56d1286e89e4ef29ce8a30276376f5adeb6234/EijkhoutMPIlecture.pdf?at=default&fileviewer=file-view-default)</br>
http://pages.tacc.utexas.edu/~eijkhout/istc/istc.html</br>
https://bitbucket.org/VictorEijkhout/hpc-book-and-course</br>
https://bitbucket.org/VictorEijkhout/parallel-computing-book/src</br>

#### 更加古老的整理
#####  OPENMP OPEN MT-PROCESSING

共享存储器并行环境

fork/join

实现为标准的库函数，包含一套编译器伪指令，运行时的库函数，环境变量

OPENMP 用于解决串行分解 和 负载不均 问题

注意:

        fork/join 的开销 : 避免隐式同步/ 尝试直接串行 / 合并并行区 / 避免动态分配问题
        变量共享问题 和 颗粒度冲突

编译器伪指令

并行指令 
```
＃pragma omp command [clause][...] 
parallel，指定并行区 代码将被多个线程并行执行 
for，可用在 parallel 代码中，于 for 循环之前，将循环分配到多个线程中并行执行 
parallel for， parallel 和 for 语句的结合，表示 for循环的代码将被多个线程并行执行，必须保证每次循环之间无相关性 
sections，用在 parallel 代码中，划分代码段，划分的代码段并行 
parallel sections，parallel和sections两个语句的结合 
critical，临界区 
single，仅被单个线程执行 
master，主线程执行 
barrier，线程同步 
flush， 对于指定变量与内存一直 
atomic，原子操作, 制定变量被动更新 
ordered， 指定for循环顺序执行 
threadprivate,用于指定一个全局/静态变量是线程私有的
```
变量/控制子句 
```
＃pragma omp command
default，指定变量使用方式，缺省shared 
shared，指定变量为多个线程共享 
private 指定每个线程存储变量私有副本，不继承初值 
firstprivate，同上，并继承初值 
lastprivate，同上，结束并赋值回初值 
reduce，用来指定变量私有,处理完后规约操作 
nowait，忽略DO/FOR SECTIONS SINGLE隐式等待 
num_threads，指定线程的个数 
schedule，指定如何调度for循环迭代

· dynamic
· guided  >自调度
· runtime >OMP_SCHEDULE
· static

copyprivate，用于single指令中的指定变量为多个线程共享 
copyin，用来指定一个threadprivate的变量的值要用主线程的值进行初始化。
```
库函数：
```
omp_get_num_procs, 返回运行本线程的多处理机的处理器个数。 
omp_get_num_threads, 返回当前并行区域中的活动线程个数。 
omp_get_thread_num, 返回线程号 
omp_set_num_threads, 设置并行执行代码时的线程个数 
omp_init_lock, 初始化简单锁 
omp_set_lock，锁 
omp_unset_lock， 
omp_destroy_lock， 对应omp_init_lock，销毁锁
```
##### MPI 标准信息传递界面

分布式存储器并行 
进程(MPI rank)间通讯方式

mpi实现 openmpi mpich lammpi mvapich
```
ssh 
mpiexec -np 5 -hosts client,localhost ./exe
```
执行模式：

spmd 单程序多数据流 </br>
程序代码-> 复制多分独立运行成为独立的进程-> { 进程1 进程2 进程3 }-> mpi消息传递 -> 消息 发送 接受 同步 规约 ->结束

多程序 -> 初始启动多个可执行代码
工作模式：

    Master/ Worker
    coupled 独立 特定时候交换数据
    Map/ Reduce
    streamline 流水线

基本概念：

    通讯域 Communicator
        包含 Group 和 context
        进程的集合|通讯协议（MPI通讯必须在某个通讯器内发生
        提供缺省的两个通讯器：MPI_COMM_WORLD MPI_COMM_SELF

    进程序号 MPI Rank

    进程组 Group

    消息号

    数据类型 常用MPI_INT… MPI_BYTE MPI_PACKED

    进程拓扑结构

一般设计流程：
```
MPI_INIT()  让所有的进程加入MPI系统 形成MPI_COMM_WORLD 
        ||
MPI_COMM_RANK() 得到进程序号
MPI_COMM_SIZE() 得到总进程数  
        ||                  <初始化>
初始化网格  和 边界  
        ||
|边界通讯. 区域计算. 同步. 交换网格|
MPI_Send()
MPI_Recv()
        ||
MPI_FINALIZE() 
```
消息传递函数

点对点

int MPI_Send(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)

int MPI_Recv(void *buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm,MPI_Status *status)

允许动态接收状态, 否则MPI_Status置为MPI_STATUS_IGNORE

函数形式为MPI_XXSEND() MPI_XXRECV()

    标准的 Send 利用标准的缓冲区
    Bsend 使用用户空间的buffer管理
    Rsend 不需要buffer 发送端不能提前等待
    Ssend 不需要buffer, 允许等待

异步方式可以理解为 另起一个县城在后台做实际的消息传输,通过wait和test等机制与主线程通行和同步

MPI_Wait( MPI_Resquest &req, MPI_Status &status);
MPI_Test(MPI_Resquest &req, int* flag, MPI_Status &status); 

测试相关操作是否完成

预防死锁//组合发送接受
聚合通信

    广播(一对多) MPI_Bcast(
    收集(多对一) MPI_Gather(

    分散 MPI_SCATTER()

    规约MPI_REDUCE()
        这里每个进程的待处理数据存放在sendbuf中，可以是标量也可以是向量。所有进程将这些值通过输入的操作子op计算为最终结果并将它存入root进程的recvbuf
        规约操作符op MPI_SUM, MPI_MIN, MPI_MAX, 
        MPI_PRODd等

    扫描 MPI_Scan()

其他

    同步 MPI_Barrier(MPI_Comm comm);
    通讯域函数()
    时间 MPI_Wtime()
    错误 MPI_Abort()
    进程拓扑
    并行io/ 多个进程访问一个文件
    单边/远程存储访问

##### 混合编程

    在MPI中，每个节点上的MPI rank的数量持续增加，所有MPI ranks的消耗内存数量将最终超过节点上可提供的内存，或使网络带宽收到限制，并行度受限
    注意MPI在细颗粒度的不足，减少opnmp在线程中的通讯
 
