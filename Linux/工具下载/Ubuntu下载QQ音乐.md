## Ubuntu下载QQ音乐

### 一、官网下载

`https://y.qq.com/download/download.html`

选择linux版本

### 二、安装

`sudo dpkg -i qqmusic_1.1.5_amd64.deb`

### 三、解决无法打开的问题

#### 1.打开启动项文件

`sudo vim /usr/share/applications/qqmusic.desktop`

#### 2.使用vim命令将代码替换为

```
[Desktop Entry]
Name=QQMusic
Exec=/opt/qqmusic/qqmusic %U --no-sandbox
Terminal=false
Type=Application
Icon=qqmusic
StartupWMClass=qqmusic
Comment=Tencent QQMusic
Categories=AudioVideo;Audio;Player;
MimeType=application/x-ogg;application/ogg;audio/x-vorbis+ogg;audio/vorbis;audio/x-vorbis;audio/x-scpls;audio/x-mp3;audio/x-mpeg;audio/mpeg;audio/x-mpegurl;audio/x-flac;audio/mp4;audio/x-it;audio/x-mod;audio/x-s3m;audio/x-stm;audio/x-xm;
Keywords=Audio;Song;MP3;CD;Podcast;MTP;iPod;Playlist;Last.fm;UPnP;DLNA;Radio;
```

