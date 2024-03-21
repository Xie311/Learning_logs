## 解决Ubuntu下无法正常git clone的问题

###  一、重置 http.proxy
`git config --global http.proxy http://127.0.0.1:1080`

` git config --global https.proxy https://127.0.0.1:1080`

`git config --global --unset http.proxy`

`git config --global --unset https.proxy`

`git clone git://github.com/tom-wong168/knowledge-system.git`

---


设置 `http.sslVerify` 为 false
` git config --global http.sslVerify "false"`

 `git config --global https.sslVerify "false"`

### 二、使用`https：//`方式访问

> fatal: 无法连接到 github.com：
> github.com[0: 127.0.0.1]: errno=连接被拒绝

这种错误一般是使用 `git://***` 下载出现，改成使用 `https://` 方式访问即可。

### 三、修改git.config文件

### 1、执行以下命令：
`vim ~/.gitconfig`

或`vim ~/.git/config`
### 2、输入以下内容：
 `[url "git@github.com:"]
 pushInsteadOf = git://github.com/
 pushInsteadOf = https://github.com/`
3、保存修改：
`:wq`