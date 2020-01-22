# 体系结构
    **TLB** 大小不一样,我们学校集群的TLB比较小 (ASC19的一个应用会疯狂TLB miss)
    **cache** 两边集群大小不一样，cache命中率也会不一样
    **指令集**，学校的向量化指令集非常低，比赛集群大概比学校向量化长度高4倍，所以对热点会有不少的影响
    **核数** ，学校集群核数少，所以MPI通信时间和计算时间的比值会不一样
    什么样的应用更加适合开 **超线程** ？ 如果访存非常好，但是CPU后端使用率非常低（通过vtune可以看到），可以实验一下超线程。
 快速profile tlb miss
 https://unix.stackexchange.com/questions/29853/command-to-measure-tlb-misses-on-linux

# 一般原则

    如果优化只是针对特殊样例的，应该用宏控制，如果现场发现对与实际样例负优化了，就改宏重新编译
    不要改坏应用原有的功能
    不要再引入glog这种东西来做logging，请使用 header only 的库，添加源文件进去就好，可以考虑我fork在这个组织的几个库
