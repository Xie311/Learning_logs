## Ubuntu使用Steam

> 前言：当我还是小*（n）白时，下好虚拟机的第一件事是下载图片换壁纸，两个多月过去了，现在我下好双系统的第一件事是安装steam使用wallpaper换更好看的壁纸^_^)

### 一、安装steam

Ubuntu软件商店直接搜索

> 两个steam软件都可以，这里选择Installer

### 二、安装steam++

#### 1.去https://steampp.net/下载选择linux版本

![img](https://img-blog.csdnimg.cn/direct/9fd9a491d1704f879ce823cd111f83c6.png)

#### 2.下载linux版本

##### (1）下载Steam++

`wget https://gitee.com/rmbgame/SteamTools/releases/download/3.0.0-rc.3/Steam%20%20_v3.0.0-rc.3_linux_x64.tgz`

解压到/opt/steam++

    sudo mkdir /opt/steam++
    sudo chown yeqiang:yeqiang /opt/steam++/
    tar -xvf Steam\ \ _v3.0.0-rc.3_linux_x64.tgz  -C /opt/steam++/

##### （2）启动Steam++

    cd /opt/steam++
    ./Steam++.sh

点击一键加速，弹出提示,同时弹出文件浏览器

执行脚本

`bash environment_check.sh`

再次点击意见加速，报错 没有权限,同时弹出浏览器，提示操作方法

参考Linux版本修改

`sudo chomod a+w /etc/hosts`

`sudo chomod a+r /etc/hosts`

> 若显示`the SSL connection could not be established`，不用管，测试可用即可。

### 三、开启Steam Player

在Linux下使用某些只适配Windows的Steam游戏

在`Setting->Compatlbility`中选择`Enable Steam Play for all titles`

> 重启后卡在logging in.....



