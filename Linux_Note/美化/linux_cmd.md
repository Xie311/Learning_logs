## zsh配置

`https://blog.csdn.net/hxxjxw/article/details/121615631?app_version=6.3.0&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22121615631%22%2C%22source%22%3A%22Xie311_zip%22%7D&utm_source=app`

> git clone短暂地糹掉了，感谢博主的gitee下载地址

### 1.下载`zsh-autosuggestions`插件:

`git clone https://gitee.com/hailin_cool/zsh-autosuggestions.git $ZSH_CUSTOM/plugins/zsh-autosuggestions`

### 2.在配置文件中，添加插件
首先打开zshrc文件

`open ~/.zshrc`

然后在.zshrc里面找到plugins，在plugins里面添加`zsh-autosuggestions`

`plugins(zsh-autosuggestions)`

### 3.保存后退出执行如下命令：

`source ~/.zshrc`
