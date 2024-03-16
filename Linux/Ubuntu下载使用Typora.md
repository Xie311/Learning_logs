## Ubuntu下下载使用Typora

### 一、下载

链接: https://pan.baidu.com/s/1a7xIoVAhooGD3NGYVDJgbA 提取码: wew7

## 二、安装
```python
tar xzvf Typora-linux-x64.tar.gz 
cd bin
sudo cp -ar Typora-linux-x64 /opt
cd /opt/Typora-linux-x64/
##启动
./Typora
```
## 三、配置

#### 1.为了在任意位置启动设置下环境变量

`sudo vim ~/.bashrc`

打开.bashrc配置文件，添加：

```#Typora环境变量
export PATH=$PATH:/opt/Typora-linux-x64
```

source一下，让配置生效

`source ~/.bashrc`

#### 2.添加桌面标
```
cd /usr/share/applications
sudo vim typora.desktop
```

添加以下内容
```
[Desktop Entry]
Name=Typora
Comment=Typora
Exec=/opt/Typora-linux-x64/Typora
Icon=/opt/Typora-linux-x64/resources/app/asserts/icon/icon_256x256.png
Terminal=false
Type=Application
Categories=Developer;
```

重启电脑就ok了

#### 3.右键打开

`gedit ~/.config/mimeapps.list`

添加`text/markdown=typora.desktop;`到`[Added Associations]`