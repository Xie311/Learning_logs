# 使用Python MAVLink库(GPT翻译官网)

## 一、概述

pymavlink包含方言特定的生成模块，提供编码和解码消息以及应用和检查签名的低级功能。

一般来说，大多数开发者会使用mavutil模块来设置和管理通信通道，因为它使得入门非常容易。该模块提供了简单的机制来建立连接、发送和接收消息，并查询一些基本的自动驾驶仪属性，例如当前活动的飞行模式等。它通过一个属性（mav）提供对用于编码、解码和签名消息的方言模块的访问。

在使用mavutil时有几个主要注意事项：

- 该链接无法正确处理在同一端口上运行的多个系统。如果您需要一个多飞行器网络，请参阅源系统过滤。

- 该模块针对ArduPilot进行了优化，某些功能在其他自动驾驶仪上可能无法正常工作。

- mavutil仍然是一个相对低级别的MAVLink API。它甚至对最常见的MAVLink微服务的支持也很有限。

  ---

  \dialects\v20\* 和 \dialects\v10\*：对应于每个MAVLink v2和v1的源XML消息定义的方言模块。每个方言模块包含以下内容：

- XML文件中定义的所有枚举和枚举值的常量。
- 一组消息标识符的常量。
- 为XML文件中定义的每种类型的MAVLink消息的类。
- 一个MAVLink类，用于发送和接收消息：
  - 每种消息类型都有 _send 和 _decode 函数。
  - 有用于检查和应用签名的方法。
  - 有用于打包和解析数据的较低级别方法。
- mavutil：用于设置通信链路、接收和解码消息、运行周期任务等的MAVLink实用函数。
  - mavutil.mavlink_connection(device, baud, ...) 用于设置（最初）在通道上侦听消息或发送消息的链接（例如，udp、串行等）。它返回一个表示连接的对象。您可以使用：
    - themav 属性来访问所选的方言/协议模块以编码和发送消息
    - setup_signing() 来设置签名
    - recv_match() 来捕获具有特定名称或字段值的消息
    该连接允许您执行许多其他有用的工作：获取所有自动驾驶仪参数、访问每种接收到的消息的最后一条消息、获取自动驾驶仪遥测数据，包括当前的飞行模式或武装状态等。
- mavwp：加载/保存航点、地理围栏、集结点。
- mavparm：加载/保存MAVLink参数集。
- mavextra：用于转换值和消息的实用函数（例如，米/秒到千米/小时、从四元数到弧度的欧拉角等）。
- mavexpression（内部）：MAVLink表达式评估函数。

## 二、选择方言/MAVLink版本

选择方言/MAVLink版本取决于您是使用mavutil进行链接管理还是直接使用方言文件。

默认情况下，mavutil设置链接以使用MAVLink 1 ardupilotmega方言进行发送/接收。您可以通过设置环境变量来更改此设置：

- MAVLINK_DIALECT：设置为方言文件的字符串名称（不带XML扩展名）。
- MAVLINK20：设置为1（如果未设置，则默认为MAVLink 1）。
- MDEF：消息定义库的位置。

在设置连接时，您还可以通过将其名称传递给mavutil.mavlink_connection()来更改方言。

如果您不使用mavutil，则可以直接导入要使用的方言文件：

```python
# 导入用于MAVLink 1的ardupilotmega模块
from pymavlink.dialects.v10 import ardupilotmega as mavlink1

# 导入用于MAVLink 2的common模块
from pymavlink.dialects.v20 import common as mavlink2
```

## 三、建立连接

**mavutil模块提供了mavlink_connection()方法，用于在串行端口、tcp或udp通道上建立与MAVLink系统的通信链接。**它还可以连接到文件对象，这在处理遥测日志时非常有用。

该方法返回一个表示单个系统的对象，但将从链接上的多个系统收集消息。这对于两个系统网络来说是可以接受的，但是如果您需要在多车辆IP网络上连接，请参见源系统过滤。

> 在这里，"两个系统网络"指的是一个通信链路上存在两个或多个MAVLink系统的情况。通常情况下，每个MAVLink系统都具有唯一的系统ID（System ID），用于在通信链路上进行识别。当有多个MAVLink系统通过相同的通信链路进行通信时，需要确保消息能够准确地路由到目标系统，而不会被误认为是其他系统发送的。
>
> 在这种情况下，"源系统过滤"是指根据消息的源系统ID来过滤和区分接收到的消息。通过源系统过滤，可以确保每个系统只接收来自特定系统的消息，而忽略其他系统的消息，从而实现对多个系统的区分和管理。
>
> 因此，在建立多车辆IP网络时，需要考虑源系统过滤的实现，以确保消息能够正确地路由到目标系统，并避免混淆或冲突。

**mavlink_connection()方法接受一个连接字符串，该字符串定义了通道，并接受一些可选参数，用于设置链接的波特率和其他属性（连接字符串的格式会自动设置和可能覆盖一些可选参数）。**

例如，要连接到标准的MAVLink模拟器UDP端口，并等待HEARTBEAT消息：

```python
from pymavlink import mavutil

# 在UDP端口上启动一个连接
the_connection = mavutil.mavlink_connection('udpin:localhost:14540')

# 等待第一个心跳
#   这将为链接设置远程系统的系统和组件ID
the_connection.wait_heartbeat()
print("来自系统的心跳（系统 %u 组件 %u）" % (the_connection.target_system, the_connection.target_component))

# 连接后，使用'the_connection'获取和发送消息
```

上面使用的udpin前缀会创建一个套接字以侦听指定端口上的UDP连接。这是连接自动驾驶仪模拟器的正常方式。相应的udpout前缀创建一个套接字，用于启动IP连接。

一般情况下，API会为连接类型选择一个合理的波特率。您可能希望更改的其他mavlink_connection()参数包括：source_system（默认为255）、source_component（默认为0）和方言（默认为ArduPilot）。

**连接字符串**

mavutil.mavlink_connection()连接字符串的格式如下：

[protocol:]address[:port]

其中：

---

**protocol（可选）**：IP协议。如果未指定，则pymavlink将尝试确定地址是串行端口（例如USB）还是文件，如果没有，则默认为UDP地址。
tcp：在指定的地址和端口上启动TCP连接。
tcpin：在指定的地址和端口上监听TCP连接。
udpin：在指定的地址和端口上监听UDP连接。
udpout：在指定的地址和端口上启动TCP连接。
udp：默认情况下，与udpin相同。设置mavlink_connection参数input=False可使其与udpout相同。
udpcast：广播UDP地址和端口。这与udp相同，只是使用mavlink_connection()参数input=False和broadcast=True。

---

**address**：IP地址、串行端口名称或文件名

---

**port**：IP端口（仅当地址为IP地址时）
以下是可用于不同类型连接的一些字符串示例。

---

连接类型	连接字符串
Linux计算机通过USB连接到车辆	/dev/ttyUSB0
通过串行端口连接到车辆的Linux计算机（树莓派示例）	/dev/ttyAMA0（还要设置baud=57600）
MAVLink API监听SITL连接的UDP	udpin:localhost:14540（或udp:localhost:14540、127.0.0.1:14540等）
MAVLink API通过UDP启动与SITL的连接	udpout:localhost:14540（或udpout:127.0.0.1:14540）
通过UDP连接到车辆的GCS	127.0.0.1:14550或udp:localhost:14550
通过TCP连接到车辆的SITL	tcp:127.0.0.1:5760（仅适用于ArduPilot，PX4不支持TCP）
通过USB连接到车辆的OSX计算机	dev/cu.usbmodem1
通过USB连接到车辆的Windows计算机（在此示例中为COM14）	com14
使用COM14上的3DR遥测电台将Windows计算机连接到车辆	com14（还要设置baud=57600）
尽管MAVLink没有定义用于不同目的的UDP端口，但有一个事实上的标准，即MAVLink API应该在UDP端口14540上监听SITL连接，而GCS应该在UDP 14550上监听连接。

## 四、发送消息

MAVLink是主要的协议处理类。它在每个方言模块中定义，并包括方言消息定义中的所有消息的<message_name>_send()方法。

消息字段值作为参数传递给函数。对于所有消息相同的字段在类中定义，例如源系统、源组件。即使是自动生成的，每个消息也在方言源代码中进行了记录。

例如，以下示例演示了如何使用system_time_send()函数发送SYSTEM_TIME消息：

```python
def system_time_send(self, time_unix_usec, time_boot_ms, force_mavlink1=False):
    '''
    The system time is the time of the master clock, typically the
    computer clock of the main onboard computer.

    time_unix_usec    : Timestamp (UNIX epoch time). (uint64_t)
    time_boot_ms      : Timestamp (time since system boot). (uint32_t)
    '''
```

如果您使用mavutil进行链接管理，则mav属性提供了对已配置的MAVLink类对象的访问，您可以使用该对象发送消息。例如，要使用名为the_connection的链接发送SYSTEM_TIME消息：

```python
the_connection.mav.system_time_send(time_unix_usec, time_boot_ms)
```

其他示例可以在下面的发布心跳和请求特定消息中看到。

如果您不使用mavutil，则需要自己创建和设置MAVLink对象，以便它知道应该使用哪个通道来发送消息，该通道由文件属性表示。

## 五、接收消息

如果您只想同步访问接收到的特定类型的最后一条消息及其接收时间，可以使用连接的mavutil.messages字典。例如，如果您使用名为the_connection的mavutil链接，则可以执行以下操作：

```python
try: 
    altitude = the_connection.messages['GPS_RAW_INT'].alt  # 注意，您可以将消息字段视为属性！
    timestamp = the_connection.time_since('GPS_RAW_INT')
except:
    print('未收到GPS_RAW_INT消息')
```

或者，您可以使用mavutil recv_match()方法等待并拦截消息的到达：

```python
def recv_match(self, condition=None, type=None, blocking=False, timeout=None):
    '''接收下一个与给定类型和条件匹配的MAVLink消息
    type:        消息名称（作为字符串或字符串列表）- 例如 'SYS_STATUS'
    condition:   基于消息值的条件 - 例如 'SYS_STATUS.mode==2 and SYS_STATUS.nav_mode==4'
    blocking:    设置为在消息到达之前等待方法完成。
    timeout:     超时时间
    '''
```

例如，使用之前设置的the_connection，您可以等待任何消息，如下所示：

```python
msg = the_connection.recv_match(blocking=True)
```

如果您希望只获取具有特定属性值的特定消息，您可能会这样做：

```python
# 等待带有指定值的'SYS_STATUS'消息。
msg = the_connection.recv_match(type='SYS_STATUS', condition='SYS_STATUS.mode==2 and SYS_STATUS.nav_mode==4', blocking=True)
```

在尝试使用消息之前，您还应该检查消息是否有效：

```python
msg = m.recv_match(type='SYS_STATUS',blocking=True)
if not msg:
    return
if msg.get_type() == "BAD_DATA":
    if mavutil.all_printable(msg.data):
        sys.stdout.write(msg.data)
        sys.stdout.flush()
else:
    #Message is valid
    # Use the attribute
    print('Mode: %s' % msg.mode)
```

返回的对象是特定消息的MAVLink_message子类。您可以像上面的代码片段中的模式一样访问消息字段作为类属性。如果需要，您可以查询MAVLink_message以获取有关签名、CRC和其他头信息的信息。

## 六、请求特定消息

远程系统通常会向连接的GCS、摄像头或其他系统流式传输一组默认的消息。这个默认集合可能是硬编码的，并且必须受限以减少信道上的流量。

通常，系统还可以通过发送REQUEST_DATA_STREAM消息来请求提供其他信息，指定所需的流（MAV_DATA_STREAM）和速率。

使用request_data_stream_send()发送消息（下面的arg.rate将是所需的传输速率）

```
pythonCopy code# 请求所有数据流
the_connection.mav.request_data_stream_send(the_connection.target_system, the_connection.target_component,
                                        mavutil.mavlink.MAV_DATA_STREAM_ALL, args.rate, 1)
```

## 七、发布心跳 

所有的MAVLink组件都应定期广播HEARTBEAT消息，并监听来自其他系统的心跳。只要系统定期收到来自另一个系统的HEARTBEAT消息，它就会认为自己与该系统连接着。

发送消息解释了消息是如何发送的。

可以使用生成的Python方言文件中的MAVLink.heartbeat_send()消息发送HEARTBEAT消息。以下是方法定义：

```
pythonCopy codedef heartbeat_send(self, type, autopilot, base_mode, custom_mode, system_status, mavlink_version=3, force_mavlink1=False):
    '''
    心跳消息显示系统存在并正在响应。
    MAV的类型和自动驾驶硬件允许接收系统适当地处理来自该系统的后续消息
    （例如，通过基于自动驾驶的用户界面布局）。

    type              : MAV的类型（四轴飞行器、直升机等。）（type:uint8_t, values:MAV_TYPE）
    autopilot         : 自动驾驶类型/类别。（type:uint8_t, values:MAV_AUTOPILOT）
    base_mode         : 系统模式位图。（type:uint8_t, values:MAV_MODE_FLAG）
    custom_mode       : 用于自动驾驶的位字段的标志（type:uint32_t）
    system_status     : 系统状态标志。（type:uint8_t, values:MAV_STATE）
    mavlink_version   : MAVLink版本，用户不可写，由于魔术数据类型而被协议添加：uint8_t_mavlink_version（type:uint8_t）
    '''
```

假设您正在使用名为the_connection的mavutil链接，该链接由mavutil.mavlink_connection()返回，您可以按如下方式发送心跳：

```
pythonCopy code# 从GCS发送心跳（类型在方言文件中定义为枚举）。 
the_connection.mav.heartbeat_send(mavutil.mavlink.MAV_TYPE_GCS,
                                                mavutil.mavlink.MAV_AUTOPILOT_INVALID, 0, 0, 0)

# 从MAVLink应用程序发送心跳。 
the_connection.mav.heartbeat_send(mavutil.mavlink.MAV_TYPE_ONBOARD_CONTROLLER,
                                                mavutil.mavlink.MAV_AUTOPILOT_INVALID, 0, 0, 0)
```

上面使用的各种类型来自方言文件中的枚举。

心跳应该以什么频率发送取决于信道，但通常为1Hz。

通常应该从与所有其他消息相同的线程发送。这是为了确保仅在线程健康时才发布心跳。

## 八、消息签名 

在使用MAVLink 2时，Pymavlink支持消息签名（认证）。

Pymavlink库已经实现了几乎所有签署消息所期望的行为。您需要做的就是提供一个秘密密钥和初始时间戳，可选择地指定是否应该签署传出消息，一个链接ID以及一个回调来确定将接受哪些未签名消息（如果有的话）。

您所做的方式取决于您是使用mavutil来管理连接还是直接使用MAVLink对象。

虽然此主题没有涵盖，但您还应该编写代码来：从永久存储中保存和加载密钥和上次时间戳实现一个创建和共享密钥的机制。有关更多信息，请参见消息签名 > 秘密密钥管理。

使用MAVLink Class进行签名 如果您直接使用MAVLink类，则可以使用MAVLink.signing属性访问MAVLinkSigning对象并设置所需的属性。

示例/mavtest.py脚本显示了如何使用任意秘密密钥：

```
pythonCopy code# 创建MAVLink实例（在此示例中为文件对象"f"）
mav = mavlink.MAVLink(f)

if signing:
    mav.signing.secret_key = chr(42)*32
    mav.signing.link_id = 0
    mav.signing.timestamp = 0
    mav.signing.sign_outgoing = True
```

MAVLink类不会确保您的link_id或初始时间戳是否适当。初始时间戳应基于当前系统时间。有关更多信息，请参见消息签名。

使用mavutil进行签名 如果您使用mavutil来管理连接，那么您可以使用下面显示的方法来设置/禁用签名：

```
pythonCopy code#设置签名
def setup_signing(self, secret_key, sign_outgoing=True, allow_unsigned_callback=None, initial_timestamp=None, link_id=None)

#禁用签名（清除秘密密钥和使用setup_signing指定的所有其他设置）
def disable_signing(self):
```

setup_signing()方法设置了由连接拥有的MAVLink对象，并提供了一些额外的代码：

如果未指定link_id，则在内部迭代该值。 如果未设置initial_timestamp，则从底层操作系统中获取当前时间的适当值。 使用allow_unsigned_callback 消息签名 > 接受未签名的数据包和接受错误签名的数据包指定了消息签名实现应该提供机制，以便库用户可以选择有条件地接受未签名或错误签名的数据包。

Pymavlink提供了可选的allow_unsigned_callback()回调来实现此目的。这个函数的原型是：

```
python
Copy code
bool allow_unsigned_callback(self, msg
```

如果作为签名配置的一部分设置了此函数，则该函数将在任何未签名的数据包（包括所有MAVLink 1数据包）或签名不正确的数据包上调用。如果函数返回False，则消息将被丢弃（否则将被处理为已签名）。

未签名数据包应接受哪些规则是特定于实现的，但建议实现始终接受用于来自3DR无线电的反馈的RADIO_STATUS数据包（这些无线电不支持签名）。

例如：

```python
# 假设您已经建立了一个连接
the_connection = mavutil.mavlink_connection(...)

# 创建一个回调来指定要接受的消息
def my_allow_unsigned_callback(self,msgId):
    # 允许无线电状态消息
    if msgId==mavutil.mavlink.MAVLINK_MSG_ID_RADIO_STATUS:
        return True
    return False

# 将回调传递给连接（这里我们还传递了一个任意的秘密密钥）
secret_key = chr(42)*32
the_connection.setup_signing(secret_key, sign_outgoing=True, allow_unsigned_callback=my_allow_unsigned_callback)
```

##  九、示例
有许多基于pymavlink的有用示例和完整系统：

pymavlink子模块包含许多简单的示例。
MAVProxy是一个面向命令行和控制台的基于MAVLink的无人机地面站软件包。
它演示了使用MAVLink模块的大部分功能。
源代码可以在这里找到：https://github.com/ArduPilot/MAVProxy
DroneKit-Python是基于Pymavlink的开发人员API。
它实现了一个更简单的高级API，用于访问飞行器信息，还实现了一些MAVLink子协议/微服务的实现（例如任务协议）。
源代码可以在这里找到：https://github.com/dronekit/dronekit-python