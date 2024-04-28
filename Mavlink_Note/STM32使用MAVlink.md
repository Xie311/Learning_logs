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

### MAVLink XML 文件的基本结构

```c
<?xml version="1.0"?>
<mavlink>
  <version>3</version>
  <dialect>0</dialect>
  <enums>
  	<enum name="aaaa">
  	</enum>
  	<enum name="bbbb">
  	</enum>
  </enums>
  <messages>
  	<message id='1' name="somename">
  	</message>
  	<message id="2" name="anothername">
  	</message>
  </messages>
</mavlink>

```

xml 结构主要可以分为版本信息块、enums包括的枚举数据定义块以及messages 消息定义块。版本信息块如下

```c
<version>3</version>
<dialect>0</dialect>
```

enums 枚举数据定义块是`<enums></enums> `标签包括的内容，其中包括了很多通过`<enum></enum>`标签定义的数据。
messages 消息定义块是`<messages></messages> `标签包括的内容，其中包括了很多通过`<message></message> `定义的数据。

对于`<enum></enum>`和`<message></message>`内部的具体结构在 `mavschema.xsd` 中有定义。这里我们专注于 `common.xml `的剖析，跳过`mavschema.xsd` 并不会影响我们对 `common.xml` 的理解。
下面分别分析 `<enum></enum> `的结构和`<message></message> `的结构。由于 `<message></message>` 包含了`<enum></enum> `中的内容所以，这里先分析`<message></message>` 。

#### (1) message
这里我们摘取名为SYS_STATUS 的 message 进行分析

```c
<message id="1" name="SYS_STATUS">
  <description>The general system state. If the system is following the MAVLink standard, the system state is mainly defined by three orthogonal states/modes: The system mode, which is either LOCKED (motors shut down and locked), MANUAL (system under RC control), GUIDED (system with autonomous position control, position setpoint controlled manually) or AUTO (system guided by path/waypoint planner). The NAV_MODE defined the current flight state: LIFTOFF (often an open-loop maneuver), LANDING, WAYPOINTS or VECTOR. This represents the internal navigation state machine. The system status shows whether the system is currently active or not and if an emergency occurred. During the CRITICAL and EMERGENCY states the MAV is still considered to be active, but should start emergency procedures autonomously. After a failure occurred it should first move from active to critical to allow manual intervention and then move to emergency after a certain timeout.</description>
  <field type="uint32_t" name="onboard_control_sensors_present" enum="MAV_SYS_STATUS_SENSOR" display="bitmask" print_format="0x%04x">Bitmap showing which onboard controllers and sensors are present. Value of 0: not present. Value of 1: present.</field>
  <field type="uint32_t" name="onboard_control_sensors_enabled" enum="MAV_SYS_STATUS_SENSOR" display="bitmask" print_format="0x%04x">Bitmap showing which onboard controllers and sensors are enabled:  Value of 0: not enabled. Value of 1: enabled.</field>
  <field type="uint32_t" name="onboard_control_sensors_health" enum="MAV_SYS_STATUS_SENSOR" display="bitmask" print_format="0x%04x">Bitmap showing which onboard controllers and sensors have an error (or are operational). Value of 0: error. Value of 1: healthy.</field>
  <field type="uint16_t" name="load" units="d%">Maximum usage in percent of the mainloop time. Values: [0-1000] - should always be below 1000</field>
  <field type="uint16_t" name="voltage_battery" units="mV">Battery voltage, UINT16_MAX: Voltage not sent by autopilot</field>
  <field type="int16_t" name="current_battery" units="cA">Battery current, -1: Current not sent by autopilot</field>
  <field type="int8_t" name="battery_remaining" units="%">Battery energy remaining, -1: Battery remaining energy not sent by autopilot</field>
  <field type="uint16_t" name="drop_rate_comm" units="c%">Communication drop rate, (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)</field>
  <field type="uint16_t" name="errors_comm">Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)</field>
  <field type="uint16_t" name="errors_count1">Autopilot-specific errors</field>
  <field type="uint16_t" name="errors_count2">Autopilot-specific errors</field>
  <field type="uint16_t" name="errors_count3">Autopilot-specific errors</field>
  <field type="uint16_t" name="errors_count4">Autopilot-specific errors</field>
</message>
```

可以看到 message 的结构比较简单，主要由`<description> `段和`<field>` 组成。`<description>`是对这个消息的描述，`<field>`是消息中所包含数据的每个域的具体说明，包含域的数据类型（type），域的数据名称（name)，及对该域数据的描述(嵌入在`<field></field>`标签中的文本)。可以看到`<field>` 中还有enum 、display、print_format 和 units等其他属性。enum属性的内容即上面通过`<enum></enum>` 标签定义的枚举数据类型，例如`onboard_control_sensors_present `中引用的名称是`MAV_SYS_STATUS_SENSOR` 枚举数据类型。display 定义这个域主要是用来显示给用户的，print_format 则指定了打印格式。这个message 实际上就是传输中的数据的具体结构，message中定义的每个field 在数据中一定存在，且大小按其type 域指定的数据类型相一致。

#### (2) enum
下面来剖析enum 节点，这里以上一节提到的MAV_SYS_STATUS_SENSOR为例来说明。

```c
<enum name="MAV_SYS_STATUS_SENSOR">
     <description>These encode the sensors whose status is sent as part of the SYS_STATUS message.</description>
     <entry value="1" name="MAV_SYS_STATUS_SENSOR_3D_GYRO">
       <description>0x01 3D gyro</description>
     </entry>
     <entry value="2" name="MAV_SYS_STATUS_SENSOR_3D_ACCEL">
       <description>0x02 3D accelerometer</description>
     </entry>
     <entry value="4" name="MAV_SYS_STATUS_SENSOR_3D_MAG">
       <description>0x04 3D magnetometer</description>
     </entry>
     <entry value="8" name="MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE">
       <description>0x08 absolute pressure</description>
     </entry>
     <entry value="16" name="MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE">
       <description>0x10 differential pressure</description>
     </entry>
     <entry value="32" name="MAV_SYS_STATUS_SENSOR_GPS">
       <description>0x20 GPS</description>
     </entry>
     <entry value="64" name="MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW">
       <description>0x40 optical flow</description>
     </entry>
     <entry value="128" name="MAV_SYS_STATUS_SENSOR_VISION_POSITION">
       <description>0x80 computer vision position</description>
     </entry>
     <entry value="256" name="MAV_SYS_STATUS_SENSOR_LASER_POSITION">
       <description>0x100 laser based position</description>
     </entry>
     <entry value="512" name="MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH">
       <description>0x200 external ground truth (Vicon or Leica)</description>
     </entry>
     <entry value="1024" name="MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL">
       <description>0x400 3D angular rate control</description>
     </entry>
     <entry value="2048" name="MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION">
       <description>0x800 attitude stabilization</description>
     </entry>
     <entry value="4096" name="MAV_SYS_STATUS_SENSOR_YAW_POSITION">
       <description>0x1000 yaw position</description>
     </entry>
     <entry value="8192" name="MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL">
       <description>0x2000 z/altitude control</description>
     </entry>
     <entry value="16384" name="MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL">
       <description>0x4000 x/y position control</description>
     </entry>
     <entry value="32768" name="MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS">
       <description>0x8000 motor outputs / control</description>
     </entry>
     <entry value="65536" name="MAV_SYS_STATUS_SENSOR_RC_RECEIVER">
       <description>0x10000 rc receiver</description>
     </entry>
     <entry value="131072" name="MAV_SYS_STATUS_SENSOR_3D_GYRO2">
       <description>0x20000 2nd 3D gyro</description>
     </entry>
     <entry value="262144" name="MAV_SYS_STATUS_SENSOR_3D_ACCEL2">
       <description>0x40000 2nd 3D accelerometer</description>
     </entry>
     <entry value="524288" name="MAV_SYS_STATUS_SENSOR_3D_MAG2">
       <description>0x80000 2nd 3D magnetometer</description>
     </entry>
     <entry value="1048576" name="MAV_SYS_STATUS_GEOFENCE">
       <description>0x100000 geofence</description>
     </entry>
     <entry value="2097152" name="MAV_SYS_STATUS_AHRS">
       <description>0x200000 AHRS subsystem health</description>
     </entry>
     <entry value="4194304" name="MAV_SYS_STATUS_TERRAIN">
       <description>0x400000 Terrain subsystem health</description>
     </entry>
     <entry value="8388608" name="MAV_SYS_STATUS_REVERSE_MOTOR">
       <description>0x800000 Motors are reversed</description>
     </entry>
     <entry value="16777216" name="MAV_SYS_STATUS_LOGGING">
       <description>0x1000000 Logging</description>
     </entry>
     <entry value="33554432" name="MAV_SYS_STATUS_SENSOR_BATTERY">
       <description>0x2000000 Battery</description>
     </entry>
     <entry value="67108864" name="MAV_SYS_STATUS_SENSOR_PROXIMITY">
       <description>0x4000000 Proximity</description>
     </entry>
     <entry value="134217728" name="MAV_SYS_STATUS_SENSOR_SATCOM">
       <description>0x8000000 Satellite Communication </description>
     </entry>
     <entry value="268435456" name="MAV_SYS_STATUS_PREARM_CHECK">
       <description>0x10000000 pre-arm check status. Always healthy when armed</description>
     </entry>
     <entry value="536870912" name="MAV_SYS_STATUS_OBSTACLE_AVOIDANCE">
       <description>0x20000000 Avoidance/collision prevention</description>
     </entry>
   </enum>
```

可以看出每个`<enum></enum>`中包括了很多的`<entry></entry>` ，每条`<entry></entry>`可以看作枚举的一个值，value 属性对应于值的具体大小，name 则可以看成是值的别名。
可以看出enum 类型不过是普通的数据型数据，那为什么要把这些数据类型单独拿出来定义呢。一个原因是，每个值都有确定的含义，假想两个系统之间进行通讯，虽然采用同样的协议，但是如果对值的约定不一样，这边用1 代表四旋翼,那边用1代表固定翼这样显然不匹配。另一个原因是，协议要自洽，尽量在协议文档里把协议的内容都包括进来，避免模糊和歧义。所以关于数值含义的约定也是协议的重要部分，单独列出来可以让协议结构更清晰明确。

以下代码为在XML文件中心跳消息的定义，来自`mavlink/message_definitions/common.xml`

```C
<message id="0" name="HEARTBEAT">
  <description>The heartbeat message shows that a system is present and responding. The type of the MAV and Autopilot hardware allow the receiving system to treat further messages from this system appropriate (e.g. by laying out the user interface based on the autopilot).</description>
  <field type="uint8_t" name="type">Type of the MAV (quadrotor, helicopter, etc., up to 15 types, defined in MAV_TYPE ENUM)</field>
  <field type="uint8_t" name="autopilot">Autopilot type / class. defined in MAV_CLASS ENUM</field>
  <field type="uint8_t" name="base_mode">System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h</field>
  <field type="uint32_t" name="custom_mode">Navigation mode bitfield, see MAV_AUTOPILOT_CUSTOM_MODE ENUM for some examples. This field is autopilot-specific.</field>
  <field type="uint8_t" name="system_status">System status flag, see MAV_STATUS ENUM</field>
  <field type="uint8_t_mavlink_version" name="mavlink_version">MAVLink version</field>
</message>
```

**代码解读：**

每条消息都是在`<message></message>`之间定义的
`id="0"`表示这条消息的ID或索引是数字0。**消息ID的有效数字是从0~255，其中150~240是预留给用户来自定义消息的。**
`name="HEARTBEAT"是一个易读的消息名称`，只用在定义代码中，**消息传输时不会发送这个名字，消息本身只依赖于消息ID**。
定义中的`<description></description>`**表示消息的描述**，消息的描述很重要，但不是必须的。消息的描述可以让用户明确该消息的含义和用途。
定义中的`<field></field>`表示消息的字段，**类似于C中结构体的变量**。消息的字段可以是有无符号的8位、16位、32位、64位的整型，也可以是单双精度的IEEE754浮点型。
`type="uint8_t"`表示该字段为无符号的8位整型。如果你想定义一个数组可以这样定义：`type="uint8_t[5]"` ，`uint8_t_mavlink_version`是一个特殊的类型，它是一个无符号的8位整型，用来表示当前使用的mavlink协议的版本号，该字段是只读的，当消息发送时会自动被填充。

---

如果你想建立一个单独的消息定义文件，就像`commn.xml`或其它位于`message_definitions`文件夹下的XML文件一样。你可以像下面代码一样定义，注意一定要包含版本号;

**如果这个XML文件和`commn.xml`位于同一个路径下，那么最终生成的MAVLINK代码中会包含`commn.xml`的内容。**

```c
<?xml version="2.0"?>
<mavlink>
        <include>common.xml</include>
        <!-- NOTE: If the included file already contains a version tag, remove the version tag here, else uncomment to enable. -->
    <!--<version>3</version>-->
    <enums>
    </enums>
    <messages>
        <message id="150" name="RUDDER_RAW">
            <description>This message encodes all of the raw rudder sensor data from the USV.</description>
            <field type="uint16_t" name="position">The raw data from the position sensor, generally a potentiometer.</field>
            <field type="uint8_t" name="port_limit">Status of the rudder limit sensor, port side. 0 indicates off and 1 indicates that the limit is hit. If this sensor is inactive set to 0xFF.</field>
            <field type="uint8_t" name="center_limit">Status of the rudder limit sensor, port side. 0 indicates off and 1 indicates that the limit is hit. If this sensor is inactive set to 0xFF.</field>
            <field type="uint8_t" name="starboard_limit">Status of the rudder limit sensor, starboard side. 0 indicates off and 1 indicates that the limit is hit. If this sensor is inactive set to 0xFF.</field>
        </message>
    </messages>
</mavlink>
```

### 3.移植到 stm32

（1）打开

```python
d:
cd Program Files/MAVlink/mavlink
python mavgenerate.py
```

- XML 选择你刚刚编写的 XML 文件
- Out 选择你想要存放库文件的目录
- Language 选择 C
- Protocol 选择 1.0 或 2.0（看你需求，版本区别官网上有说明）

（2）Generate

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