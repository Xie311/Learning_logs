## 如何使用root用户

>  前言：默认情况下，Ubuntu 禁用了 root 账户。，必须使用 `sudo` 命令来执行任何需要 root 权限的任务。
>
> [在桌面 Linux 系统中以 root 登录是不可取的。请遵守规范，远离这种（错误的）冒险。]

### 一、启用root账户

你想以 root 身份登录。但默认情况下，root 账户是禁用的。第一步是启用它。

改变 root 账户的密码，这将为你启用 root 账户：

```text
sudo passwd root
```

### 二、改变 GDM 配置

> 本教程的这一部分只对 GNOME 有效。请 [检查你的桌面环境](https://link.zhihu.com/?target=https%3A//itsfoss.com/find-desktop-environment/) 并确保它是 GNOME。

Ubuntu 默认使用 GNOME，GNOME 使用 GDM 显示管理器。

为了允许以 root 身份登录到 GNOME，你需要对位于 `/etc/gdm3/custom.conf` 的 GDM 配置文件做一些修改。

对该配置文件做一个备份：

```text
cp /etc/gdm3/custom.conf /etc/gdm3/custom.conf~
```

在最坏的情况下，如果你以某种方式把事情搞砸了，备份的文件可以用来从 TTY 上替换现有文件。

现在，用以下命令打开 GDM 文件：

```text
sudo nano /etc/gdm3/custom.conf
```

并添加以下一行，允许 root 用户登录：

```text
AllowRoot=true
```

按 `Ctrl+X` 退出 Nano，同时保存它。

## 三、配置 PAM 认证

现在，你必须配置 PAM 认证守护进程文件，它可以通过以下命令打开：

```text
sudo nano /etc/pam.d/gdm-password
```

在这个文件中，你必须注释掉以下带有 `#` 号的一行，该符号拒绝 GUI 中的 root 访问：

```text
auth   required        pam_succeed_if.so user != root quiet_success
```

[保存修改并退出 nano](https://link.zhihu.com/?target=https%3A//linuxhandbook.com/nano-save-exit/) 文本编辑器。

### 四、以 root 身份登录

现在，重启你的系统：

```text
reboot
```

在登录界面，选择 `Not listed` 选项，在用户名中输入 `root`，并输入你在本指南开头配置的密码：

当你登录后，它就会通知你，**“logged in as a privileged user”**

这就完成了! 现在，你正在以 root 身份运行你的 Ubuntu 系统。