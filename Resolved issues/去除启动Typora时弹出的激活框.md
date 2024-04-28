## 无需破解去除启动Typora时弹出的激活框
在安装路径下找到license.html文件
`xx\Typora\resources\page-dist`     
(在浏览器中打开即为Typora界面）     
用vscode打开，使用快捷键格式化代码 `Shift + Alt + A`

在文件下方添加如下代码可以强制关闭弹出窗口：
```
<script>
    window.close()
</script>
```