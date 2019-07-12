# 用于收集编译器相关的经验
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#

总结的一些参数
http://blog.qzwlecr.com/2018/01/30/ICC%E4%BC%98%E5%8C%96%E5%8F%82%E6%95%B0%E7%AC%94%E8%AE%B0/#more

MKL的链接
https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor/ (有人说用这个不好？)


static link for icc/ifort
As per the documentation, while -static-intel is the default, compiling with -dynamic links in the Intel dynamic libraries when creating the shared library. I confirmed that and also confirmed when adding -static-intel that it links in the Intel static libraries when creating the shared library. You can verify the Intel static libraries are linked in by adding -# and inspecting the actual ld command line, or use ldd.
https://software.intel.com/zh-cn/node/297975

```
-ipo
‐align array64byte 这个可以让array按照64位对齐，考虑到是64位浮点数，这样方便访存
-fprotect-parens 指定了括号的地方，不做数学上计算顺序的优化
-fimf-precision=high 控制mkl（svml）的精度到high （.aka.最后一位bit可能不准确）
-fp-model double ... 按照double ... 精度来计算浮点数 
 -fp-model fast=1 浮点数相关的具体请看我在这个目录下放的一个pdf
-mveclibabi=svml -lsvml 尝试使用svml

-no-prec-div
https://software.intel.com/en-us/cpp-compiler-developer-guide-and-reference-prec-div-qprec-div


这个只在极端条件下会很有用，一般用不到
Profile-Guided Optimization (PGO)

.. Instrument the program: build the program using the compiler flag -prof-gen or /Qprof-gen
.. Run the instrumented executable to gather profiling data with various input data or workloads
.. Re-build the program with the profiling data using flag -prof-use or /Qprof-use
https://software.intel.com/en-us/code-samples/intel-compiler/intel-compiler-features/ProfileGuidedOptimization
```
