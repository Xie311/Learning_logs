## Anaconda配置OpenCV环境

（前情提要：window下python环境无法正常在Vscode终端下安装OpenCV环境）

##   一、下载OpenCV环境

  首先进入Anaconda Prompt找到自己安装anaconda/Scripts>目录下。

![img](https://img-blog.csdnimg.cn/379f647fac774891ba89c2778f798545.png)

1. `pip install -i https://pypi.tuna.tsinghua.edu.cn/simple opencv-python==3.4.1.15`

2. `pip install -i https://pypi.tuna.tsinghua.edu.cn/simple opencv-contrib-python==3.4.1.15`

   ## 二、在当前Scripts目录下使用命令：pip list查看是否安装成功![img](https://img-blog.csdnimg.cn/db648ba89bca4e88b23011307190d6f2.png)

   ## 三、查看opencv环境是否安装成功。

   在cmd命令中输入python

   在输入下面两个命令

   1. `import cv2`
   2. `cv2.__version_`
          

   ![img](https://img-blog.csdnimg.cn/1c7b8911336e4fbe806729638e04c008.png)

##   四、VSCODE内选择相应python解释器

  `fn+f1`选择python解释器

测试：

```python
import numpy as np
import cv2

img = cv2.imread('test.jpg', cv2.IMREAD_UNCHANGED)
cv2.namedWindow('img', cv2.WINDOW_AUTOSIZE)
cv2.imshow('img', img)
cv2.waitKey(0)
```



