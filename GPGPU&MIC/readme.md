# GPGPU
这个文件夹里有一些ppt，可以看看，但是有的过于老了，现在特性可能不一样

如果不幸遇上了CUDA的题目，建议先看看推荐的这本书，（章节5，初学可以看看），章节6（共享内存，缓存），章节9
```
CUDA 并行程序设计：GPU 编程指南 （图书馆有，可以在学校借，编号 TP 391.41.6029 ）（CUDA programming : a developer's guide to parallel computing with GPUS）
```
cuda编程的东西很多，出的题目涉及的都不难，可以现学的。

可以调节的参数(以后的同学逐渐完善)
```
关于 thread 数量，需要注意 thread 过多，对 cache & register 的影响，一般都需要让 register够用，不要 split
configurable bank size, which can be set using cudaDeviceSetSharedMemConfig() to either four bytes (cudaSharedMemBankSizeFourByte, the default) or eight bytes (cudaSharedMemBankSizeEightByte). Setting the bank size to eight bytes can help avoid shared memory bank conflicts when accessing double precision data.
```
```
    cudaDeviceSetCacheConfig(cudaFuncCachePreferL1/...);

```

cuda 有一定的编译选项，一般程序的makefile会自己进行选择，但如果没有，应手工修改，设到设备对应的最高的既可。
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

每次不同 kernel launch 会导致cache清空，注意这点会导致的可避免的 cache miss（优化方法看上面推荐的书）

https://stackoverflow.com/a/11286781/8428146



#### Pinned Host Memory – How to use it?

 Using POSIX functions like mlock is not sufficient, because the CUDA
driver needs to know that the memory is pinned

 Two ways to get pinned host memory

■ Using cudaMallocHost/cudaFreeHost to allocate new
memory

■  Using cudaHostRegister/cudaHostUnregister to pin
memory after allocation

 cudaMemcpy makes automatic use of it

 cudaMemcpyAsync can be used to issue asynchronous memory
copies

 Can be directly accessed from Kernels (zero-copy) – use
cudaHostGetDevicePointer

GPUProgramming with CUDA @ JSC, 24. - 26. April 2017



#### MULTI-PROCESS SERVICE (MPS)

 Background:
```
— Each process has a unique context.
— Only a single context can be active on a device at a time.
— Multiple processes (e.g. MPI) on a single GPU could not
```
operate concurrently

 MPS: Software layer that sits between the driver and your
application.
```
— Routes all CUDA calls through a single context
— Multiple processes can execute concurrently
```
