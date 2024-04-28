# CubeMonitor

## 一、CubeMonitor介绍

将STM32开发板通过ST-LINK连接到本地电脑，STM32CubeMonitor可以在本地电脑（Host PC）上运行，同时也可以在其他的电脑，平板或手机上通过浏览器访问host PC的IP地址（端口号1880）打开STM32CubeMonitor的界面，进行编辑或者查看Dashboard(需要在同一个局域网）。

---

STM32CubeMonitor变量监测及可视化工具，支持通过ST-LINK的SWD或者JTAG接口连接到目标MCU，可以在程序全速运行不被打断的情况下，读取需要检测的变量值。非常适合那些需要在程序全速运行下进行调试的情况，是对传统的通过设置断点进行调试的方式的补充。

STM32CubeMonitor可以通过非侵入式的方式（Direct模式）检测程序变量，对采集的数据实时分析，协助程序诊断。除了Direct模式以外，Snapshot模式下通过往应用程序添加特定采样代码，可以提供更精确的采样。变量可以根据可执行文件导入，也可以直接根据变量地址进行手动添加，还可以对采集的变量进行各种后处理运算，设置采样触发条件等。

STM32CubeMonitor可以通过**非侵入式的方式（Direct模式）**检测程序变量，对采集的数据实时分析，协助程序诊断。除了Direct模式以外，**Snapshot模式下通过往应用程序添加特定采样代码，可以提供更精确的采样**。变量可以根据可执行文件导入，也可以直接根据变量地址进行手动添加，还可以对采集的变量进行各种后处理运算，设置采样触发条件等。

---

STM32CubeMonitor有两种工作模式：设计模式和Dashboard模式。设计模式即是编辑模式，打开STM32CubeMonitor默认就是处在这个模式。设计模式下，最左边一栏列出了所有当前可用的节点，我们可以通过拖拽不同的节点来创建或者编辑不同的逻辑数据流（Flow），来实现想要的功能。比如将要检测的变量通过点线图进行实时显示，或者通过一个按钮来控制某个GPIO口的状态等。设计模式下最右边一栏可以看到当前选中节点的使用说明和程序运行的调试信息等内容。

待所有的节点都编辑完成并部署运行后，可通过右上方的DASHBOARD按钮进入Dashboard模式。在Dashboard模式下，我们可以看到在设计模式下编辑的“流”运行的结果，看到我们之前设计的界面，通过这个界面去检测或者控制变量的值。

---

STM32CubeMonitor基于Node-RED，Node-RED是一个基于“流（Flow）”的开发工具。那么何为“流”?Node-RED提供了很多功能节点，这些节点可以分为输入节点，输出节点和功能节点。把这些节点连接起来就是一个”流”。多个“流”的组合，我们也把它叫做“流”。比如在设计模式下的标签页面我们也称作“流”，它里面实际会包含多个不同功能的单个“流”。

---

STM32CubeMonitor技术文档:`[Category:STM32CubeMonitor - stm32mcu](https://wiki.st.com/stm32mcu/wiki/Category:STM32CubeMonitor)`

## 二、基本数据采集

在Library下，有两类流可以选择：BasicFlow和AdvancedFlow。你可以把它理解成STM32CubeMonitor已经做好的两个流模板，方便大家上手。

**BasicFlow**只有一个标签页，里面已经预先实现了**启动/停止采样，并将结果显示在点线图上的基本功能**。只需要将其中节点的参数更新一下即可。**AdvancedFlow**包括两个标签页：一个标签页里是和STM32节点相关的流（比如设置变量地址，读取变量值并处理，输出到图表等）；另一个标签页里放的是用户界面按键。两个标签页的节点通过Link in和Link out节点连接。在AdvancedFlow中还可以同时连接两个ST-LINK，同时检测两个STM32开发板的运行。

我们再回到BasicFlow，从图中可以看到整个BasicFlow流由两个流组成：上面的流由两个button节点（Start， Stop），一个variables节点和一个acq_out节点组成。这个流完成的功能是：设置要检测的变量地址，在Dashboard上添加两个按键（Start,Stop）来启动和停止采样。下面的流由acq_in节点，processing节点，一个button节点和一个chart节点组成。acq_in节点接收ST-LINK发来的数据，processing节点接收acq_in的消息，将所选择的变量数据发送到chart节点进行显示。Clear button用来清除chart图表的显示。

---

**示例程序**

![img](https://pic4.zhimg.com/80/v2-1c3c2794e6d3bc41686d84eded8e6797_720w.webp)

很容易看出来，这个程序由上下两部分组成：

- 上面的四个blocks用于获取数据
- 下面的四个blocks用于处理数据

上半部分的前两个浅青色模块相当于两个按钮，START Acquisition用于启动数据获取过程，另一个STOP Acquision用于停止数据获取。中间的蓝色模块用于配置我们想要监控的程序变量

---

### 1.配置myProbe_Out和myProbe_In

**（1）myProbe_Out——acq_out**：定义或者选择一个ST-LINK配置（通信协议，频率等），打开或者关闭连接，向选择的ST-LINK发送命令等。

**（2）myProbe_In——acq_in**：定义或者选择一个ST-LINK配置，并接收ST-LINK发来的数据。

> 在开始配置前，我们会发现在这两个节点的右上方分别有一个红色的三角形和蓝色的圆点。红色的三角形表示：该节点还未配置，蓝色的圆点表示：该节点更新后还未部署。

在配置这两个节点前，先连接ST-link到PC。然后按照图中的步骤进行配置：

- 1.双击节点，打开编辑窗口，点击“ProbeConfig”编辑按钮

- 2.在下拉菜单中选择可用的ST-LINK（如果没有连接任何st-link，就会看到“No results found”）

- 3.点击Add，添加ST-Link

- 4.点击Done，完成配置，编辑窗口自动关闭

> 这时节点右上方的红色三角形消失，蓝色圆点还在，表示当前节点已经配置，但还没有部署。

### 2.配置variables节点，添加要监测的变量

**只能监测全局变量**

---

- 1.点击编辑按钮

- 2.添加可执行文件所在目录（直接将路径拷贝过来）

![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/163554d0h4a41hxn3v4dou.png)

![image-20240425133838752](C:/Users/86188/AppData/Roaming/Typora/typora-user-images/image-20240425133838752.png)

> .elf文件在"\build\Debug\"路径下

- 3.在File项的下拉菜单中选择可执行文件，CubeMonitor会自动分析并导入所有全局变量的列表



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/163616jd11h177zdp1pd1h.png)



- 4.在变量列表中列出的变量很多，可以用过滤器通过关键字将要监测的变量过滤出来。比如我们输入var，这时列表中就只剩下我们想要要监测的这三个变量了

- 5.点击变量前面的方框，选中这三个变量

- 6.为当前的配置取一个名字，这个名字代表的就是当前选择的变量组合。在所有的variables节点中都可以通过这个名字选择配置好的变量组合。

- 7.点击Add添加变量

- 8.为当前的variables组命名，之后在processing节点中就可以通过该名称来选择某个变量组了（见后续介绍）

- 9.添加好变量后，还需要配置变量采样的参数（采样模式和采样速度，以及是否有采样触发）。采样速度一般我们选择“sequential loop”，该配置下CubeMonitor会以最快的速度进行采样。或者你也可以自己设定采样频率。采样模式有Direct和snapshot两种。Direct模式属于非侵入式，通过JTAG或者SWD协议读取存储器的值，不需要添加任何代码到MCU程序。Snapshot模式，需要向MCU程序添加特定的代码，由MCU定时采样，将结果保存在MCU的内存中，再由CubeMonitor定期读出。Snapshot模式可以提供更精确的采样。在当前的例子中，我们使用direct模式就可以了。关于snapshot模式，我们会在第二个例子中做进一步介绍。

- 10.最后点击Done完成配置

### 3.Processing节点

Processing节点的输入连接到acq_in节点，接收从ST-link发来的数据，按不同的变量对数据进行组合，每50ms输出一次。

> 比如要检测的是三个变量，那么processing节点就会每50ms输出三条消息，里面包含了这三个变量在这段时间内的采样数据，可能是一个，也可能是多个，跟设置的采样速度有关。processing节点的输出直接连接到chart节点就可以显示了。

这个节点的配置比较简单，只需要**在GroupName的下拉列表中选择要处理的变量组**就可以了（也就是在variables节点配置的第8步设置的变量组名）。

#### 4.采集数据

现在所有的节点都已经配置完毕，点击右上方的DEPLOY按键，部署并运行编辑好的”流“。部署后所有节点上的蓝色小圆点都消失了。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/163803oljxx7xuoclj4llw.png)



点击右上方的DASHBOARD按键，打开dashboard就可以看到我们编辑的界面了。点击START ACQUISITION键开始采集数据，就可以看到监测的三个变量的实时变化情况了。

### 5.实时修改变量的值

**需要添加图中红框中的inject，variables和write panel节点**

**(1)Write panel节点**会在Dashboard里添加一个输入框，而且Write panel节点与myProbe_Out节点相连，所以每次输入的值都会通过myProbe_Out发送到ST-LINK。

**(2)Variables节点**里设置需要修改的变量的地址。

**(3)Inject节点**的作用是可以手动或按照设定的时间间隔自动向“流”注入消息，这里我们利用它在程序启动时触发一次消息发送，把Variables设定的变量地址发送给ST-LINK。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164450fo17i18byiqqybq9.png)



Variables节点的设置跟前面一样。这里我们只需要将要修改的var_max, var_min这两个变量添加进来就可以了。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164510cssz5bt2fz87b53t.png)



配置Write panel节点，选择放在“Home”标签页，并设置尺寸大小。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164528igi5g0io0rnrniow.png)



Inject节点里可以配置输出的消息负载类型（时间戳，数字，字符串等），设定消息的topic和消息发送的方式（一次性还是周期性的）。在这个例子中，我们主要是利用inject节点在程序启动时触发一次消息发送，所以Payload选择timestamp即可，repeat选项设置为none，然后勾选图中红框标出的选项（程序启动后触发一次消息发送）。设置完成后，inject节点显示的名字就会变成“timestamp”，并且右上方有一个数字1，表示只触发一次。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164551i39mcfeznxezmeaf.png)



重新部署运行，进入Dashboard界面，可以看到下方多出了var_max, var_min这两个变量值的输入框和一个“WRITE”按钮。在输入框中写入新的变量值，点击WRITE按钮，从上面的点线图中就可以看到，对应的变量立刻发生变化了。

到这里，我们已经完成了所有的流编程内容。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164616jmybom8mslly7an8.png)



通过菜单下的Export可以将整个流保存成json文件，操作步骤见上图。在保存的时候，可以选择只保存选中的几个节点（selectednodes），还是当前选中的标签页的整个流（current flow），也可以保存所有打开的标签页下的流（all flows）。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164633rl8e7i09stu0wuus.png)



保存好的json文件，通过import菜单可以再次导入。见上图操作步骤。



![st-img](https://shequ.stmicroelectronics.cn/data/attachment/forum/202007/27/164654t2ykwysjj5s56o92.png)



在这个例子的最后，我们来了解一下节点之间传递消息的数据结构和debug节点。

将一个节点的输出连接到另一个节点的输入后，这两个节点就可以传递消息了。CubeMonitor节点之间的消息采用json格式，包括payload，topic，msgid等字段。在每一个节点的说明中可以看到它的输入消息和输出消息的字段定义，除了前面提到的这三个字段，各个节点根据所实现的功能不同，消息中包含的字段也有所不同。大部分节点都会用到payload和topic字段中的一个或者两个都用。在调试时我们一般关注的也是payload和topic这两个字段。

debug节点是一个非常好用的调试工具，它可以连接到任何节点的输出，来观察实际运行时消息传递的情况。在debug窗口（点击右边的小爬虫图标）可以看到所有Debug节点的输出，系统的出错信息也会输出在这里。

现在我们用两个debug节点分别连接到START按键和myVariables节点的输出。Debug节点配置成输出完整的消息内容。重新部署运行，然后在debug窗口就可以看到这两个节点的输出信息了。按下START按键，此时START节点输出了一个topic为“start”的消息来通知ST-LINK开始采样。START节点的输出消息先经过myVariables节点，再送到myProbe_out节点。

myVariables节点输出的消息包含：所有需要监测的变量的名称，地址，类型以及设定的采样参数等，并将topic设置为接受到的START节点消息中的topic内容。所有这些信息都可以通过debug节点看得清清楚楚。ST-LINK接收到消息就知道应该对哪些变量启动采样了。