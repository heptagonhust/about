# HPC硬件入门

以下是一些基础知识，不定期更新

------

## HPC的硬件有哪些

CPU、主板(包含主板上的BMC和部分主板的内置NIC)、内存条、硬盘(有各种协议和接口)、GPU/各种奇奇怪怪的加速卡、NIC(用来以太网通信的千兆和RDMA/RoCE高性能网络)等等。

PC和Server的构成很像，但是也有很大差别，例如：

- PC一般没有ECC内存条，即长时间运行内存变得不可靠。
- PC的CPU核心通常大核心数量<=8，但是睿频很高，单核性能强；相对的，服务器低频多核，单核弱多核强
- PC一般来说PCIe通道比较少，难以实现单机8卡的操作

区别还有很多，不一一赘述。

------

### CPU

服务器主要是amd64的CPU，少部分ARM64(例如华为鲲鹏920)，amd64主要有Intel的Xeon和AMD的EPYC。其中，Intel以前主要是做Mesh结构，现在转向了和AMD一样的Chiplet。产品线也从全大核心发展到有全大核心和全小核心的产品线(截至2024年11月)，而且新小核的性能很强。

具体的架构差异可以自行去查找，下面给出2个例子：

- [Zen 3 - 微架构 - AMD - WikiChip](https://en.wikichip.org/wiki/amd/microarchitectures/zen_3)
- [Willow Cove - 微架构 - Intel - WikiChip](https://en.wikichip.org/wiki/intel/microarchitectures/willow_cove)

wikichip更新不一定及时和准确，最好是Intel/AMD的ppt或者datasheet，加上第三方对微架构的评测

[关于Intel CPU浮点性能、内存带宽计算 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/444850434#:~:text=双精度浮点（即FP64）： 双精度浮点理论峰值GFLOPS%3D频率 times 核数 times,frac {512} {64} times2 （单核FMA数量）times 2（一次运算融合加和乘）)

CPU的理论性能有一些粗略的估算方式，可以去了解一下。

更进一步的，就不是基础知识了，需要一些计算机体系结构的专业知识，这里，强烈推荐**CSAPP**(深入了解计算机系统)

想钻研CPU微架构上面一些细节的，下面的网站很棒：

[总体架构 - XiangShan 官方文档](https://docs.xiangshan.cc/zh-cn/latest/arch/)

(虽然很多人吐槽香山,但是这个文档是真不错)

关于微架构的演进，下面的内容很好：

[17-0.主要CPU微架构列表 · 现代CPU上的性能分析与优化 (weedge.github.io)](https://weedge.github.io/perf-book-cn/zh/chapters/17-List-of-Uarch-ISA/17-0_List_of_uarchs_cn.html)

EPYC的microarchitecture可以参考下面：

[AMD Zen CPU 架构以及不同CPU性能大PK |植物蛋 (plantegg.github.io)](https://plantegg.github.io/2021/08/13/AMD_Zen_CPU架构/)

Intel的Numa问题(但是这个有点老了，新的不一样):

[十年后数据库还是不敢拥抱NUMA？ |植物蛋 (plantegg.github.io)](https://plantegg.github.io/2021/05/14/十年后数据库还是不敢拥抱NUMA/)

对微架构进行优化：

[3-3.开发指令级并行性 · 现代CPU上的性能分析与优化 (weedge.github.io)](https://weedge.github.io/perf-book-cn/zh/chapters/3-CPU-Microarchitecture/3-3_Exploiting_ILP_cn.html)

测试microarchitecture也是一个方向(通过测试结果其实可以逆向其内部结构)：

[ARM BTB 逆向工程 (stefan1wan.github.io)](https://stefan1wan.github.io/2024/05/BTB/)

AND，处理器一样有Bug：

[这L2 Cache有点怪，13900ES的BUG还是FEATURE？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/595024029)

------

### 主板

[主板 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/主板)

想了解一个服务器主板，最好先看厂商给的白皮书(不过现在一般都要服务器的序列号，这个时候就求助万能的网盘分享吧)

服务器主板要注意下面几个问题：

- PCIe通道，怎么插riser，Slim线和主板、riser上的对应关系是什么
- 是不是SXM的服务器(4U/8U)，那样的话GPU的安装方式和功耗都有所不同
- 内存条的顺序问题，主要是不插满的时候怎么插
- BMC如何清空CMOS，如何清除密码，IPMI登录的密码等等
- GPU供电的制式，是EPS还是ATX3.0(服务器很少是例如RTX2080这种6+2pin的，老计算卡基本上是EPS，也就是CPU供电的4+4pin，新GPU一般是ATX3.0的12+4pin，其中4pin的线决定了线材的功率上限)

一般8GPU/10GPU的服务器没有那么多PCIe通道，因此出现了PLX芯片，也就是PCIe Switch，例如可以1个PCIe x16扩展4个PCIe x16 GPU。这样，双路CPU就可以上8GPU。同样，也有独立的PCIe Switch，即GPU Box(典型型号例如浪潮BX512-IP，这是腾讯定制的4GPU扩展柜)。

------

