import cv2
import numpy as np

# 初始化 VideoCapture 对象，使用外置摄像头
cap = cv2.VideoCapture(1)

while(True):
    ret,frame = cap.read(25)    #可以给空参数（一般设置为25ms）
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    cv2.imshow('frame',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
     #&0xFF 是为了确保只关心 ASCII 值的最后八位（在某些操作系统上，cv2.waitKey() 返回的值可能包含其他信息）
    
cap.release()    #释放摄像头对象
cv2.destroyAllWindows()