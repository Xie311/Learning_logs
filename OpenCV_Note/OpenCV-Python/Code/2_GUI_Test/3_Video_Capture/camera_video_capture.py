import cv2
import numpy as np

cap = cv2.VideoCapture(0)

if cap.isOpened() == False:
    cap.open()

# 视频的基础设置
wide = cap.get(3)
height = cap.get(4)
bright = cap.set(10, 1)

# VideoWriter 对象创建
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('out.avi',fourcc,20.0,(640,480))
#创建一个 VideoWriter 对象，用于将帧写入到输出视频文件中
#指定了输出文件的名称为 "out.avi"，使用了上面定义的编解码器 'XVID'，帧率为 20.0 FPS，视频帧的大小为 640x480 像素

while (True):
    ret, frame = cap.read()
    if ret == True:
        frame = cv2.flip(frame, 0)  #这行代码将读取的帧水平翻转
        # gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)  将彩色图像转换为灰度图像
        
        cv2.imshow('video',frame)
        out.write(frame)  #这行代码将当前帧写入到输出视频文件中。
        print("%d,%d,%d" % (wide, height, bright))
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break

cap.release()    #释放摄像头对象
out.release()
cv2.destroyAllWindows()
