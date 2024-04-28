# PID参数整定方法

## 一、经验法

> 参数整定找最佳，从小到大顺序查
> 先是比例后积分，最后再把微分加
> 曲线振荡很频繁，比例度盘要放大
> 曲线漂浮绕大湾，比例度盘往小扳
> 曲线偏离回复慢，积分时间往下降
> 曲线波动周期长，积分时间再加长
> 曲线振荡频率快，先把微分降下来
> 动差大来波动慢。微分时间应加长
> 理想曲线两个波，前高后低4比1
> 一看二调多分析，调节质量不会低

---

>若要反应增快，增大P减小I;
>若要反应减慢，减小P增大I；
>如果比例太大，会引起系统振荡
>如果积分太大，会引起系统迟钝

## 二、Cubemonitor/Matlab调试PID

参考：`[【STM32】高效开发工具CubeMonitor快速上手_stm32cubemonitor-CSDN博客](https://blog.csdn.net/weixin_45015121/article/details/132281109?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1-132281109-blog-108846043.235^v43^pc_blog_bottom_relevance_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1-132281109-blog-108846043.235^v43^pc_blog_bottom_relevance_base3&utm_relevant_index=2)`

---

`[STM32CubeMonitor 介绍（一）基本介绍 & 例程一：基本的数据采... (stmicroelectronics.cn)](https://shequ.stmicroelectronics.cn/forum.php?mod=viewthread&tid=626119)`

---

STM32CubeMonitor变量监测及可视化工具，支持通过ST-LINK的SWD或者JTAG接口连接到目标MCU，可以在程序全速运行不被打断的情况下，读取需要检测的变量值。非常适合那些需要在程序全速运行下进行调试的情况，是对传统的通过设置断点进行调试的方式的补充。

STM32CubeMonitor可以通过非侵入式的方式（Direct模式）检测程序变量，对采集的数据实时分析，协助程序诊断。除了Direct模式以外，Snapshot模式下通过往应用程序添加特定采样代码，可以提供更精确的采样。变量可以根据可执行文件导入，也可以直接根据变量地址进行手动添加，还可以对采集的变量进行各种后处理运算，设置采样触发条件等。

STM32CubeMonitor可以通过**非侵入式的方式（Direct模式）**检测程序变量，对采集的数据实时分析，协助程序诊断。除了Direct模式以外，**Snapshot模式下通过往应用程序添加特定采样代码，可以提供更精确的采样**。变量可以根据可执行文件导入，也可以直接根据变量地址进行手动添加，还可以对采集的变量进行各种后处理运算，设置采样触发条件等。

详见`Cubemonitor使用`

## 三、仿真调参

### （1）调节Kp

![img](PID参数整定.assets/图片1)

![img](PID参数整定.assets/图片2)

![img](PID参数整定.assets/图片·3)

![img](PID参数整定.assets/图片4)

### （2）调节KI

![img](PID参数整定.assets/图片5)

![img](PID参数整定.assets/图片7)

![img](PID参数整定.assets/图片6)

### （3）调节KD

![img](PID参数整定.assets/图片8)

![img](PID参数整定.assets/图片9)

![img](PID参数整定.assets/图片10)

![img](PID参数整定.assets/图片11)



### 异常情况：

1.检测端异常

> 不论怎么调整，输出要么一直偏高要么一直偏低

![在这里插入图片描述](PID参数整定.assets/图片12)

2.输出端异常

> 不论怎么调整，输出一直振荡着有缓慢上升趋势或下降趋势，这时候就要检测是否是输出端有问题。
>
> eg：假如控制到100，那么100就是保持信号，101就是当前还没达到设定值，加大输出信号，同理99就是减小输出信号。如果在线调试，99成了加，或者101成了减，那么就会出现上面的情况。

![img](PID参数整定.assets/图片13)

---

**参考**：`[PID控制参数整定（调节方法）原理+图示+MATLAB调试_pid控制一阶段系统和二级系统-CSDN博客](https://blog.csdn.net/viafcccy/article/details/107988093)`

---

`[PID控制参数整定（调节方法）原理+图示+MATLAB调试_恒温控制pid matlab-CSDN博客](https://blog.csdn.net/m0_46577050/article/details/134892062?spm=1001.2101.3001.6650.8&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-8-134892062-blog-88616630.235^v43^pc_blog_bottom_relevance_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-8-134892062-blog-88616630.235^v43^pc_blog_bottom_relevance_base3&utm_relevant_index=15)`

---

`[matlab实现pid仿真-百度经验 (baidu.com)](https://jingyan.baidu.com/article/22fe7cedecd6db3002617f8d.html)`

---

`[【STM32】高效开发工具CubeMonitor快速上手_stm32cubemonitor-CSDN博客](https://blog.csdn.net/weixin_45015121/article/details/132281109?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1-132281109-blog-108846043.235^v43^pc_blog_bottom_relevance_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1-132281109-blog-108846043.235^v43^pc_blog_bottom_relevance_base3&utm_relevant_index=2)`