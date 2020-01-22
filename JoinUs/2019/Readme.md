## 题目描述
题目代码出自PHENGLEI流体力学计算程序

该题目实现了一个类似Fortran数组的数据结构FYArray，其中，数组的维度不定。在main函数中，使用该数据结构进行了数组的加减乘除运算。你的目标是，修改该数据结构的部分代码，使得该数组表达式运算部分能够并行化。

你需要修改的是位于`FYOps.hxx` 420行的函数`evaluateWithStackTraversalN`, 该函数实现了多维数组表达式的运算。你需要想办法将该串行代码并行化。

你可以使用openmp, openmpi, pthread来完成任务。

- 要求:
    - 请不要修改src/main.cpp中的运算和计时代码
    main函数代码仅为模拟数组运算代码，没有太大数学意义，请不要修改。

    - 你的首要目标是修改`evaluateWithStackTraversalN` 函数, 你可以针对某些维度的数组进行并行化，但请保证该函数对于其他维数的数组正确性。

    - 请记录你在完成该题目中所查询的资料和学到的知识。

    - 建议使用Linux

- 提示:
    - 该数据结构的模拟了Fortran的数组，你可以通过网上教程，如[Fortran数组](https://www.yiibai.com/fortran/fortran_arrays.html)了解Fortran数组的基本使用。

    - 实际上，你只需要专注修改`evaluateWithStackTraversalN`函数就好
    重点关注该函数的实现目的和该函数所使用到的FYArray的API

    - 阅读这些源文件将会有帮助
        - `FYExpr.h`
        - `FYFastArrayIterator.h`
        - `FYOps.h`
        - `FYOps.hxx`

        其余源文件可以不去理解它的具体意思，而把它们当为一个黑盒使用。

    - 也许你无法成功完成该题目，但没有关系，请做好在完成该题目中遇到的问题，解决方案和查询资料的记录，我们会做相应的参考。所以请尽可能地尝试。

    - 如果你成功并行化了该函数，你可以更进一步优化该程序的瓶颈。

## Checkpoints:

- 成功编译该代码
- 成功运行该串行代码，并得到串行代码的结果文件check.txt
- 了解该函数的基本原理
- 将该函数`evaluateWithStackTraversalN`并行化
- 成功编译修改后的并行代码
- 成功运行并通过精度检查
- 下载Intel Parallel Xe Studio并使用Vtune寻找热点和瓶颈，进一步优化

## 编译
该程序使用make工具进行编译，你可以修改Makefile来满足自己的编译需求。

## 运行
编译完成后，在目录下会生成FYArray程序，直接运行即可。

在main函数中，提供了两个函数 `preccheck` 和`resultprint`

其中`preccheck`用来进行精度检测，而`resultprint`用来输出结果文件。你可以修改makefile，在CFLAGS中加入-DPRINT_RESULT来使得该程序的串行版本生成结果文件。并在并行版本中使用该结果文件进行精度检测。

阅读main.cpp会有所帮助。

运行该程序会打印出运行时间。

## 提交代码
解题记录格式: pdf,md,docx等
压缩包格式: zip,tar.gz,7z...(除rar)

请将你的完整代码和你的解题记录打包成压缩包发送到邮箱`hustasc2019@163.com`中，不需要发送结果文件。

截止时间11月11日00:01分(星期一凌晨12点01分)

