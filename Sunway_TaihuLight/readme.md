太湖上面的那个计算卡用好很难，注意多读官网的用户手册
http://www.nsccwx.cn/process.php?word=process&i=54

可以看看这个文件夹里的pdf上面优化计算和访存的那个文章 。P21

（请张立琛同学在这里总结一下今年的CPC国产CPU）

## CPC2019体验

我们看 bbs上的课件入门
http://bbs.nsccwx.cn/assets/uploads/files/1528120200586-cpc%E5%9F%B9%E8%AE%AD_%E7%A5%9E%E5%A8%81%E5%A4%AA%E6%B9%96%E4%B9%8B%E5%85%89%E5%B9%B6%E8%A1%8C%E7%BC%96%E7%A8%8B%E4%B8%8E%E4%B8%8A%E6%9C%BA%E5%AE%9E%E8%B7%B5.pdf
http://bbs.nsccwx.cn/assets/uploads/files/1529047771770-%E7%A5%9E%E5%A8%81%E5%A4%AA%E6%B9%96%E4%B9%8B%E5%85%89%E9%AB%98%E7%BA%A7%E8%BF%9B%E9%98%B6.pdf

然后 去阅读官网的用户手册， 里面有的命令是错的，出错可以去bbs逛逛
http://bbs.nsccwx.cn/categories

2019初赛题目是7点27点模板计算，程序比较简单，主要工作就是写从核函数与优化通信。

2019复赛题目是宇宙天体物理数值模拟，题目改编自photoNs-2.0，理解代码有点难且枯燥（，主要工作同初赛，比谁更有耐心（笑。

额外发现， cmath 中的某些数学函数 会用到很多的常量，所以在从核中调用这些数学函数，会造成冲突，变慢。解决方法重写函数（主办方说在手册中里有为从核专门写的替代函数，但我们没找到）
