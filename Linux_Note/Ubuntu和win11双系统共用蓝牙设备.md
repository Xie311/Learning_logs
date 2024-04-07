# Ubuntu和win11双系统共用蓝牙设备

## 0.0双系统不能共用一个蓝牙设备的原因

假如当你从已经配对的 Windows 系统切换到 Ubuntu 系统时, Ubuntu系统此时没有配对验证文件，这时就要进行配对，这里要注意虽然两者是不同的系统，但却是同一个设备，所以在鼠标看来，它要做的不是连接一个新设备而是更新之前的配对信息。这就导致了当你回到 Windows 时，系统因配对验证文件过时而无法连接蓝牙设备。

## 0.1解决思路

1. 在 Windows 下进行配对， 用于产生配对信息
2. 在 Linux 下重新配对，用于产生配对文件
3. 将 Linux 下的配对信息修改为与 Windows 一致

## 具体实现

通过文章一中提到的dumphive工具读取Windows 注册表，它可以将Windows注册表转换成一个文本文件，方便查找蓝牙设备信息。

> 这里我遇到一个坑，就是我的蓝牙设备和新设备建立连接时会随机生成一个MAC地址？？？，后来我查资料发现BLE 协议新增了一种地址：随机设备地址，即设备地址不是固定分配的，而是在设备启动后随机生成的。所以我比上面文章多了一步就是把Linux下的蓝牙设备的MAC地址也改为与WIndows一致。

之后

```
systemctl restart bluetooth
```

成功建立连接！

---

参考文章：

`https://blog.csdn.net/weixin_44432386/article/details/107791689`

`https://blog.nanpuyue.com/2018/040.html`

`https://desktopi18n.wordpress.com/2018/02/02/bluetooth-mouse-in-dual-boot-of-windows-10-and-linux`