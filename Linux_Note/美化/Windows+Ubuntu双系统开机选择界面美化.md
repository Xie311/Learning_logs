## Windows+Ubuntu双系统开机选择界面美化

### 一、前期配置

#### 1.安装`gnome-tweaks`

`sudo apt install gnome-tweaks`

安装完成后可以通过命令打开，也可以通过图标“优化”打开

`gnome-tweaks`

#### 2.安装浏览器插件

地址:`https://extensions.gnome.org/`

`sudo apt install chrome-gnome-shell`

下载后解压

(好像不硬需，因为我没下载^_^)

### 二、下载grub主题

下载网址:`https://www.gnome-look.org/browse?cat=109&page=4&ord=rating`

在`GRUB Themes`内选择主题，点击`Download`或`Files`下载到本地

### 三、安装grub主题

> 安装时请使用root用户进行操作

#### 1.下载完成后，执行命令：

`sudo chmod a+x install.sh`

`sudo ./install .sh`

#### 2.修改默认配置

`sudo vim /etc/default/grub`

打开该文件后，看如下属性：
```
GRUB_DEFAULT=0
GRUB_TIMEOUT_STYLE=hidden
GRUB_TIMEOUT=10
```
GRUB_DEFAULT：默认启动项：这个编号是开机时看到的若干个启动项从上到下的依次编号(0开始)。
> eg.如果默认想启动高级选项下的第三个，就需要改为“1> 2”，引号必须加，>和2之间有空格。这样系统开机以后就会默认进入这个内核。

 GRUB_TIMEOUT_STYLE：是否显示倒计时，hidden的属性表示不会显示倒计时，改为menu会显示菜单。
>GRUB_TIMEOUT：等待时间，单位是秒。

#### 3.最后更新配置，使修改生效

按`ESC`键 跳到命令模式，然后输入`:q`（不保存）或者`:wq`（保存） 退出。

`$ sudo update-grub`

`reboot`重启即可看到效果。