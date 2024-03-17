## Ubuntu卸载安装包

### 1.使用Synaptic软件包管理器进行卸载
打开软件包管理器。Ubuntu自带了一个GUI（Graphical User Interface，图形化用户界面）软件包管理器，它可 以让你在一个可视化窗口中卸载程序。如果你不习惯使用命令行，这一工具将非常有用。

点击系统，然后选择管理。在管理菜单中，选择Synaptic软件包管理器。
某些较新版本的Ubuntu没有预装`Synaptic`。要安装它，打开终端并输入：`sudo apt-get install synaptic`
如果你使用Unity，可以打开`dashboard`并搜索“Synaptic”


找出你希望卸载的程序。在左边的窗格中，你可以按照类别对程序进行排序列表。已安装的程序（软件包）将在列表显示在Synaptic上方的窗格内。

程序经常以它们的缩写名称显示。例如，Media Player常被显示为“mplayer”。如果你不能通过程序的缩写名称确定它是否是你需要删除的程序，请在删除它前在线搜索有关信息确认清楚。

右击你需要协助的软件包。在菜单中选择标记为移除。你可以选择为多个需要卸载的软件包重复该操作。

你还可以选择标记为完全移除，以便可以删除配置文件和程序文件。

### 2.使用软件中心进行卸载


打开软件中心。软件中心是一个可以安装和卸载Linux软件的GUI软件包管理器。

### 3.使用终端进行卸载
打开终端：`Ctrl+Alt+T`

你将使用“apt-get”命令，这是用于管理已安装程序的通用命令。在卸载程序时，你可能需要输入管理员密码。

当你输入密码时，密码将不会被显示。完成输入后按回车即可。

浏览已安装的程序。要查看已安装的软件包列表，请输入以下命令。请注意你希望卸载的软件包的名称。输入命令：dpkg --list

卸载程序和所有配置文件。在终端中输入以下命令，把替换成你希望完全移除的程序：
`sudo apt-get --purge remove <programname>`

例如：`sudo apt-get --purge remove 0ad-data-common`

只卸载程序。如果你移除程序但保留配置文件，请输入以下命令：
`sudo apt-get remove <programname>`

### 附：解决 apt-get remove和dpkg删除出现 `E: 无法定位软件包 XXXX`

#### 第一步：更新软件源

可能的一个原因是因为安装过后没有更新软件源，试试用

`sudo apt-get update `
命令更新一下软件源。在尝试删除命令，如果不行在走第二步

 #### 第二步：通过关键词找出安装软件

linux系统部分安装包安装后会自动命名，用

`sudo dpkg -l | grep qq`
这里以qq为例，输入命令后找到qq名称为linuxqq

 #### 第三步：根据找到的软件名执行删除操作

`sudo apt-get --purge remove linuxqq`
或者`sudo dpkg -P linuxqq`