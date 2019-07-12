# GPGPU
cuda 有一定的编译选项，一般的程序的makefile会自己进行选择，但是如果没有，可以考虑手工修改。
直接设到设备对应的最高的既可。
```
GEN_SM75 = -gencode=arch=compute_75,code=\"sm_75,compute_75\" # Turing RTX20XX
GEN_SM70 = -gencode=arch=compute_70,code=\"sm_70,compute_70\" # Volta V100
GEN_SM61 = -gencode=arch=compute_61,code=\"sm_61,compute_61\" # Pascal GTX10XX
GEN_SM60 = -gencode=arch=compute_60,code=\"sm_60,compute_60\" # Pascal P100
GEN_SM52 = -gencode=arch=compute_52,code=\"sm_52,compute_52\" # Maxwell M40, M60, GTX9XX
GEN_SM50 = -gencode=arch=compute_50,code=\"sm_50,compute_50\" # Maxwell M10
GEN_SM37 = -gencode=arch=compute_37,code=\"sm_37,compute_37\" # Kepler K80
GEN_SM35 = -gencode=arch=compute_35,code=\"sm_35,compute_35\" # Kepler K20, K40
GEN_SM30 = -gencode=arch=compute_30,code=\"sm_30,compute_30\" # Kepler K10

```

https://stackoverflow.com/questions/35656294/cuda-how-to-use-arch-and-code-and-sm-vs-compute

https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html#gpu-compilation

如果不幸遇上了CUDA的题目，建议先看看推荐的这本书，章节（5，初学可以看看），6（共享内存，缓存），9
```
CUDA 并行程序设计：GPU 编程指南 （图书馆有，可以在学校借，编号 TP 391.41.6029 ）（CUDA programming : a developer's guide to parallel computing with GPUS）
```
然后可以调节的参数
```
configurable bank size, which can be set using cudaDeviceSetSharedMemConfig() to either four bytes (cudaSharedMemBankSizeFourByte, the default) or eight bytes (cudaSharedMemBankSizeEightByte). Setting the bank size to eight bytes can help avoid shared memory bank conflicts when accessing double precision data.
```
```
    cudaDeviceSetCacheConfig(cudaFuncCachePreferL1/...);

```
