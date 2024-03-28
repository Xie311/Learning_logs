# STM32使用MAVlink^_^

## 一、Python环境下安装MAVlink

![image-20240324224045837](Marvlink_assets\图片26.png)



![image-20240324224252895](Marvlink_assets\图片27.png)

> 检查python和git的安装

` git clone https://github.com/mavlink/mavlink.git`

![image-20240324224403700](D:\Study_log\Mavlink\Marvlink_assets\图片28.png)

`pip install -r pymavlink/requirements.txt`

启动MAVlink：

` python .\mavgenerate.py`

## 二、搭配串口食用

参考：

`[R1_Upper/Mavlink 位于 main - R1_Upper - 你好，世界](http://10.249.19.53:3000/CYT/R1_Upper/src/branch/main/UserCode/Lib/Mavlink)`

`[MirTITH/WTR-Mavlink-Library: 移植到 stm32 平台的 mavlink (github.com)](https://github.com/MirTITH/WTR-Mavlink-Library?tab=readme-ov-file)`

### 1.编写xml文件

可以仿照以下文件编写 `.xml`：

[wtr_mavlink_demo.xml](https://github.com/MirTITH/WTR-Mavlink-Library/blob/main/examples/stm32f103cbt6/UserCode/mavlink/wtr_mavlink_demo.xml)

[test.xml](https://github.com/MirTITH/WTR-Mavlink-Library/blob/main/mavlink_1.0.12/message_definitions/v1.0/test.xml)

[mavlink/v1.0 位于 master - mavlink - 你好，世界](http://10.249.19.53:3000/ControlFamily/mavlink/src/branch/master/message_definitions/v1.0)

---

 MavLink 官方关于如何选取消息 id 的建议：

> 对于 MAVLink 1:
>
> - 有效数字介于 0 到 255。
> - ID 0-149 和 230-255 为common.xml保留。 语支可以使用180-229 用于自定义消息 (除非这些信息没有被其他包括语支使用)。
>
> 对于 MAVLink 2 :
>
> - 有效数字介于0-1677215。
> - 255以下所有值都被认为是保留的，除非报文也打算用于 MAVLink 1。 **注意** ID 在 MAVLink 1 中很宝贵！

> mavlink 官方有一些预定义好的消息（放在这里 [mavlink_1.0.12/message_definitions/v1.0](https://github.com/MirTITH/WTR-Mavlink-Library/blob/main/mavlink_1.0.12/message_definitions/v1.0)）。这些消息是官方预设的无人机通信消息，如果不玩无人机就基本上用不到。

详细语法见官方文档:

https://mavlink.io/zh/guide/xml_schema.html

https://mavlink.io/zh/guide/define_xml_element.html

### 2.根据 xml 文件生成库文件

（1）打开

```python
mavlink/mavgenerate.py
```

- XML 选择你刚刚编写的 XML 文件
- Out 选择你想要存放库文件的目录
- Language 选择 C
- Protocol 选择 1.0 或 2.0（看你需求，版本区别官网上有说明）

（2）Generate

### 3.移植到 stm32

1. 将生成的库文件添加到你的 stm32 工程中

2. 将 `src/wtr_mavlink.c` 和 `src/wtr_mavlink.h` 添加到你的 stm32 工程中

3. 对于 MDK，可能要开启 GNU 拓展

4. 根据实际需要，修改 `wtr_mavlink.h` 中的以下内容

   ```c
   // 系统 ID 和 组件 ID
   static mavlink_system_t mavlink_system = {
       1, // System ID (1-255)
       1  // Component ID (1-255)
   };
   
   // MavLink 能使用的最大通道数
   #define MAVLINK_COMM_NUM_BUFFERS 4
   ```

   MAVLink 支持多个系统互相通信。系统可以是上位机、机器人、遥控器、无人机等。一般建议为每个系统分配唯一的 `System ID`。如果一个系统上有多个单片机，建议为每个单片机分配唯一的 `Component ID`。

   > 这两个 ID 只是为了让接收方知道消息是谁发过来的。 MAVLink 原本设想的是为系统上的每个组件（比如说各种传感器）分配一个 `Component ID`，但这里的 mavlink_system 是全局变量，一个单片机不方便设置多个 `Component ID`，所以只能每个单片机分配一个 `Component ID` 了。

   > `MAVLINK_COMM_NUM_BUFFERS` 是 MAVLink 最大可用的通道数。通常一个通道对应一个串口。请根据需要分配。设置得越大会占用越多内存。MAVLink 默认为单片机分配 4 个通道。

### 4.使用 WTR Mavlink Library

使用 mavlink 相关函数前，需要 `#include "wtr_mavlink.h"`

> 只需要包含 `wtr_mavlink.h` 这一个文件就行了，不用包含 mavlink 的其他头文件

#### （1）绑定通道和串口

> mavlink 支持多通道收发，使用 mavlink 的通道前需要先绑定串口，之后对这个通道的发送和接收操作就相当于对绑定的串口的操作（串口要在 CubeMX 里先配置好）

> 一般一个通道对应一个串口，一个通道可以同时收发，通道的数量取决于你在`wtr_mavlink.h`中定义的 `MAVLINK_COMM_NUM_BUFFERS`

使用 `wtrMavlink_BindChannel()` 函数绑定

examples:

```c
wtrMavlink_BindChannel(&huart1, MAVLINK_COMM_0);
wtrMavlink_BindChannel(&huart2, MAVLINK_COMM_1);
```

#### （2）发送消息

mavlink 将你自定义的消息都封装在了结构体里，一个消息对应一个结构体

如名字为 `speed` 的消息在 `mavlink_speed_t` 中

本库采用阻塞式发送，使用如下函数发送结构体（记得绑定通道和串口）：

```c
// 向通道X发送结构体，（X要改为对应的数字）
mavlink_msg_xxx_send_struct(MAVLINK_COMM_X, &StructToBeSend);
```

> xxx 为要发送的消息名称

 （3）接收消息

本库采用中断接收模式，因此如果需要接收消息，必须在 CubeMX 里使能串口全局中断

接收消息需要如下操作：

1. 确保已经绑定通道和串口

2. 在代码中调用：

   ```c
   // 启动通道X对应串口的中断接收
   wtrMavlink_StartReceiveIT(MAVLINK_COMM_X);
   ```

3. 在中断回调函数中调用`wtrMavlink_UARTRxCpltCallback()`

   例如:

   ```c
   void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
   {
       // 接收通道X的消息
       wtrMavlink_UARTRxCpltCallback(huart, MAVLINK_COMM_X);
   }
   ```

4. 在你喜欢的位置（如 main.c）定义如下函数：

   ```c
   /**
    * @brief 接收到完整消息且校验通过后会调用这个函数。在这个函数里调用解码函数就可以向结构体写入收到的消息
    *
    * @param msg 接收到的消息
    * @return
    */
   void wtrMavlink_MsgRxCpltCallback(mavlink_message_t *msg)
   {
       switch (msg->msgid) {
           case 1:
               // id = 1 的消息对应的解码函数(mavlink_msg_xxx_decode)
               mavlink_msg_xxx_decode(msg, &StructReceived);
               break;
           case 2:
               // id = 2 的消息对应的解码函数(mavlink_msg_xxx_decode)
               break;
           // ......
           default:
               break;
       }
   }
   ```

   > 以上代码通过 `msg->msgid` 判断是哪个消息，还可以通过 `msg->sysid` 和 `msg->compid` 判断消息是从哪里来的

## 三、性能测试

stm32f103 在 arm-none-eabi-gcc-10.3.1 编译器下：

开启 O3 优化：2M 波特率成功收发，2.5M 波特率接收失败

不开优化：1M 波特率接收失败，115200 (0.1M) 波特率接收成功