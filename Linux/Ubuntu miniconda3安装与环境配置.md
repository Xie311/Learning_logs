# Ubuntu miniconda3安装与OpenCV环境配置

### 一、下载

`https://www.jianshu.com/p/914edc1de634`

or清华源下载

`wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-latest-Linux-x86_64.sh`

### 二、安装

#### 1.运行miniconda3安装脚本
赋予执行权限

`chmod +x Miniconda3-latest-Linux-x86_64.sh `
执行：

`sudo ./Miniconda3-latest-Linux-x86_64.sh `
按Enter继续，接着会出现很多信息，这时按空格翻页，输入yes同意协议。

这是询问安装位置，加sudo则默认root用户下，不加sudo则默认当前用户下。软件包一般安装到/opt下，故进行设置。

> /opt/miniconda3

询问是否在[shell](https://so.csdn.net/so/search?q=shell&spm=1001.2101.3001.7020)中将miniconda初始化。由于还要安装ros2，所以选择“no”，避免第三方哭的冲突。

#### 2.修改配置文件

打开配置文件（一般位于用户目录下）

`vim ~/.zsh.rc`

将下行添加在文件末

`export PATH="/opt/miniconda3/bin:$PATH"`

#### 3.激活配置

`source ~/.zshrc`

#### 4.测试

`conda --version`

### 三、激活及下载OpenCV环境

使用` source activate `命令或 `conda activate `激活虚拟环境

`source activate base`
`conda activate base`

取消自动进入base环境指令

`conda config --set auto_activate_base false`
如果希望自动进入，输入指令如下

`conda config --set auto_activate_base true`
镜像源安装opencv

`pip install opencv-python -i https://pypi.tuna.tsinghua.edu.cn/simple`

`pip install opencv-contrib-python -i https://pypi.tuna.tsinghua.edu.cn/simple`
