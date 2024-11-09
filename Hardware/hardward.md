# HPC硬件入门

以下是一些基础知识，不定期更新(last update 2024.11.9)

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

[中央处理器 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/中央处理器)

服务器主要是amd64的CPU，少部分ARM64(例如华为鲲鹏920)，amd64主要有Intel的Xeon和AMD的EPYC。其中，Intel以前主要是做Mesh结构，现在转向了和AMD一样的Chiplet。产品线也从全大核心发展到有全大核心和全小核心的产品线(截至2024年11月)，而且新小核的性能很强。

具体的架构差异可以自行去查找，下面给出2个例子：

- [Zen 3 - 微架构 - AMD - WikiChip](https://en.wikichip.org/wiki/amd/microarchitectures/zen_3)
- [Willow Cove - 微架构 - Intel - WikiChip](https://en.wikichip.org/wiki/intel/microarchitectures/willow_cove)

wikichip更新不一定及时和准确，最好是Intel/AMD的ppt或者datasheet，加上第三方对微架构的评测

[关于Intel CPU浮点性能、内存带宽计算 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/444850434#:~:text=双精度浮点（即FP64）： 双精度浮点理论峰值GFLOPS%3D频率 times 核数 times,frac {512} {64} times2 （单核FMA数量）times 2（一次运算融合加和乘）)

CPU的理论性能有一些粗略的估算方式，可以去了解一下。

更进一步的，就不是基础知识了，需要一些计算机体系结构的专业知识，这里强烈推荐**CSAPP**(深入了解计算机系统)

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

安装SXM GPU比较复杂，具体见：

[SXM5 PCIe 开关板电缆布线 |ThinkSystem SR675 V3 |联想文档 (lenovo.com)](https://pubs.lenovo.com/sr675-v3/cable_routing_for_pcie_switch_board)

这是一个系列文档并且有视频，目前只有联想有这么详细的doc。

垃圾佬必然要玩过x99，毛子的网站有一定的参考价值：

[Veineda x99 v367: характеристики, обзор возможностей, bios и прошивка, совместимость, покупка и цены (xeon-e5450.ru)](https://xeon-e5450.ru/socket-2011-3/veineda-x99-v367/)

------

### 内存(RAM)

[随机存储器 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/随机存储器)

DDR内存目前主要是DDR4和DDR5，低压的lpddr在服务器上不常见。还有一些特殊的：已停产的傲腾持久型内存、cxl存储的主存模式等等。DDR4现在主流频率是3200，早期的标准一般是2400开xmp到2666/3200；DDR5现在默认4800，实际上6400较为容易，更高频的一般是LPDDR5。

注意，LPDDR/LPDDRx的频率和标准DDR的频率不是一个概念，具体每一代不一样，但是同频的基本上性能都弱于标准DDR。

服务器DDR的显著特征是支持ECC，ECC分2种：纯ECC和RECC。RECC即Reg ECC，内存条上多一个芯片。一般来说HPC服务器的RAM都是RECC。

内存条有1R x8、2R x4等等规格，R指rank，具体来说：

[服务器内存中的2rx4与4rx4各指的什么？各有什么区别？-EasySupport | 易速 (easu.net)](https://easu.net/ddr4-2rx4-4rx4/)

什么是CXL：

[什么是CXL（Compute Express Link）技术？一文读懂CXL - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/627890778)

什么是Optane PMem：

[持久内存（PMem）科普-CSDN博客](https://blog.csdn.net/sunqinshan/article/details/124140274)

------

### 硬盘

[硬盘 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/硬盘)

硬盘主要有2大类：机械和固态。机械一般指磁盘，即HDD，服务器的企业机械盘一般是大容量的氦气盘，一般来说是单盘10-20TB的多层磁盘的氦气万转SAS盘。由于多碟且高转速，性能一般比家用盘好，同时，噪音也很大(经典打豆子的声音)，这里提供个声音链接：

[WD HC550 16T氦气盘 启停声音实录（防空警报）4KHDR_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1VT411g7qU/?spm_id_from=333.337.search-card.all.click&vd_source=9ad491e269331e706f232b3a72628cc2)

氦气盘的缺点也很大：首先，氦气会泄露，所以N年后就寄了；其次就是机械盘通病：撞击或者磕碰非常容易寄。

固态有以下几类：

- SATA固态：  和机械盘一样，注意SATA口有3Gbps和6Gbps两种速度
- m.2 nvme固态： m2接口，nvme协议，现在笔记本上的硬盘基本都是这个
- U.2 nvme固态：  兼容SATA口形状，跑的nvme协议，服务器上的nvme很多是这个
- PCIe固态： 较为古老，老企业盘多见，同样，optane的SSD有不少走PCIe的
- CXL固态： [什么是CXL（Compute Express Link）技术？一文读懂CXL - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/627890778)
- AHCI固态： 较为古老，古董Mac喜欢用，新的都是nvme了

HPC常用的就2种：SATA、U.2 nvme

[固态硬盘的PCIE，SATA，M2，NVMe，AHCI - yimuxi - 博客园 (cnblogs.com)](https://www.cnblogs.com/yi-mu-xi/p/10469458.html)

固态最核心的是2点：颗粒、主控。

颗粒有SLC、MLC、TLC、QLC以及目前未能推广的PLC。分别对应single、multi、triple、quad等，也就是1bit-4bit。SLC寿命最好，同时容量最低；QLC容量最高，寿命最低。

[越先进越落后？SLC/MLC/TLC/QLC固态硬盘全面解析_固态硬盘_什么值得买 (smzdm.com)](https://post.smzdm.com/p/akld04l8/)

一般来说，QLC远不如TLC，只能当大容量机械盘用，缓外速度可怜(真就和机械差不多)，寿命也非常低，问题是价格比TLC基本没有优势，因此完全不推荐(截至2024年，以后也许有所变化)。

SLC和MLC目前基本都只有2手，全新的最好的就是TLC了，但是TLC的寿命也说的过去。

上面提到了缓存，显然，固态硬盘存在缓内和缓外。现在主流策略是TLC模拟SLC，即TLC能携带3bit，但是缓存部分只用1bit，TLC开成SLC用，这样就可以当高寿命、高速度的缓存用。

还有另一种缓存，即有缓/无缓盘。这个指硬盘上有一块DDR RAM，这个RAM上面保存的是一张FTL表。无缓存其实也不是真的无缓存，而是HBM缓存，即用电脑自身的DDR RAM里面划分出比如说1GB当缓存。

------

### GPU/各类加速卡、计算卡

最主流的毫无疑问是NVIDIA的GPU，尤其是Tesla系列数据中心计算卡。目前国内大量存世的有FP64的计算卡是A100，其实A800也有，但是砍了带宽。A100/A800有40G和80G两种版本，80GB的显存是HBM2e，对HPL提升显著，HPCG提升很少。H100是最后一代短暂在国内上市的旗舰规格GPU，但是主要是SXM的，PCIe版本很少。H800阉割了FP64算力和带宽，别的规格和H100一致，同样主要是SXM版本。B100/B200系列的旗舰就和我们没什么关系了(禁售)。

非NV计算卡有以下几种：

- AMD GPU，Rocm软件栈，全套的解决方案，主打一个力大砖飞：生态肯定是不如NV的，但是同代产品的绝对数值基本上更强。
- Imagine的IP核，比如目前(2024.11的摩尔线程，之前就是买了Imagine的IP核，但是驱动更新的勤快，好评)。国内还有很多家的GPU都是一个来源。
- 昇腾系，华为的GPU，性能不错，兼容性由于国产化用昇腾很多，做产品其实问题不大，但是做HPC的优化由于文档和其他的兼容性问题，会更不方便一些。
- 海光DCU等等GPU，早年AMD落魄的时候买下来Zen1和GPU的源码，因此海光是有CPU和GPU的，实际就是AMD初代产品换皮。类似的还有澜起，其实就是Intel CPU换皮，不过海光真有源码，但是澜起没有。
- Apple，封闭的GPU/NPU和软件栈，而且也没有服务器，一般没什么人在这上面搞HPC。
- Intel，Xe GPU，就是核显那一套爆改，最近出了个Xeon Max CPU，在CPU里添加了AMX指令集，同时添加了HBM内存。详细见：[Intel® Xeon® 可扩展处理器 Max 系列](https://www.intel.com/content/www/us/en/developer/articles/technical/xeon-scalable-processor-max-series.html)

GPU的主要参数主要是显存位宽/实际的带宽、显存容量、显存的类型、CU/SM单元数量、Tensor Core数量等等；一般来说datasheet会给出典型的算力，比如fp32单精度10Tflops，半精度fp1620Tflops等等。带宽越大越好，比如512bit就是128bit的4倍；显存容量越大，能跑的模型就越大，同时刀法精湛的皮衣黄买的价格可就不止翻倍了；显存一般来说HBM3>HBM2e>HBM2>GDDR6>GDDR5，HBM基本上都大于GDDR，代数更高的大于代数更低的，体现上就是带宽更高、频率更高。

显存的特点是超大带宽、超高延时；内存是低延时，低带宽(相对显存来说，其实带宽也不低了)。

下面附上一张很全面的GPU性能速查表：

[GPU 性能（数据表）快速参考 （2023） (arthurchiao.art)](https://arthurchiao.art/blog/gpu-data-sheets/)

*To be  continued：CU、Tensor core*

------

### NIC

[网卡 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/网卡)

NIC即网卡，一般是连接以太网或者高性能网络的。HPC一般有2种网络：千兆/万兆用来和Internet通信，IB网卡/RoCE网卡用来NFS或者计算的通信。

IB：[以太网卡、IB网卡的详细介绍以及区别分析_ib卡和网卡有什么区别-CSDN博客](https://blog.csdn.net/fiber_naddod/article/details/127575067)

RoCE：[RoCE、IB和TCP等网络的基本知识及差异对比 - 华为 (huawei.com)](https://support.huawei.com/enterprise/zh/doc/EDOC1100203347)

IB基本上被Mellonax(现在已经被NV收购)垄断，RoCE现在华为在主推。小型集群IB很好，但是多级网络的大型超算基本上都是RoCE。现在RoCE高端基本上是800G带宽。

*to be continued：具体的原理和通信过程*

------

## 一些相关网站的链接

- [about/Hardware/hardward.md at master · heptagonhust/about (github.com)](https://github.com/heptagonhust/about/blob/master/Hardware/hardward.md)
- [首页 | HPC知识分享 (hpclib.com)](https://hpclib.com/)

------

