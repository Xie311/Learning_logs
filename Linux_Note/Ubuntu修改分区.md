# Ubuntu修改分区

参考`https://zhuanlan.zhihu.com/p/484175635`

**启动并进入Live CD或USB系统**

UTFI进入bios，在configuration内将U盘移到最上

点击确认，选择进入Ubuntu

### 1.将根分区挂载到`/mnt/root`

```
 sudo mkdir /mnt/root
 mount XX /mnt/root
```

### 2.. 将`home`分区挂载到`/mnt/oldhome`

   ``` 
   sudo mkdir /mnt/oldhome
   mount XX /mnt/oldhome
   ```

### 3. 使用`rsync`来同步数据

```bash
sudo rsync -avz --hard-links --numeric-ids /mnt/oldhome/ /mnt/root/home
```

### 4. 打开文件`/mnt/root/etc/fstab`,并从中删掉用于挂载`home`分区的条目

```
vi /mnt/root/etc/fstab
```

### 5. 卸载根分区和home分区，重启。

```bash
umount /mnt/root
umount /mnt/oldhome
```

如果一些都正常的话，你可以回到你原来的系统，然后

1. 打开`Gparted` （可能需要自己安装，或者使用其它工具）
2. 删除旧的`home`分区，扩容根分区。

如果`Gparted`里边显示你的硬盘未挂载，并且有rpool之类的卷标，那么你可以通过如下命令清除掉`zfs`文件系统的魔法字符串，从而让`Gparted`正确识别你的硬盘分区[[2\]](https://zhuanlan.zhihu.com/p/484175635#ref_2)。

```text
# 如果没有zpool命令，请根据提示安装相应软件包。
zpool labelclear -f <pool-name>/<device-name>
```