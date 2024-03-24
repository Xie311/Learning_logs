import cv2
import numpy as np


cap = cv2.VideoCapture(0)
cap.set(10, 1)

lower = np.array([0,0,0])
upper = np.array([0,0,0])
low = np.array([0,0,0])
up = np.array([0,0,0])

# 阈值窗口回调函数
def Trackbar_callback_Hmin(value):
    lower[0] = value

def Trackbar_callback_Hmax(value):
    upper[0] = value
    
def Trackbar_callback_Smin(value):
    lower[1] = value

def Trackbar_callback_Smax(value):
    upper[1] = value

def Trackbar_callback_Vmin(value):
    lower[2] = value

def Trackbar_callback_Vmax(value):
    upper[2] = value

# 窗口滑动条建立
cv2.namedWindow('image')
cv2.createTrackbar('H min', 'image', 0, 179, Trackbar_callback_Hmin)
cv2.createTrackbar('H max', 'image', 0, 179, Trackbar_callback_Hmax)
cv2.createTrackbar('S min', 'image', 0, 255, Trackbar_callback_Smin)
cv2.createTrackbar('S max', 'image', 0, 255, Trackbar_callback_Smax)
cv2.createTrackbar('V min', 'image', 0, 255, Trackbar_callback_Vmin)
cv2.createTrackbar('V max', 'image', 0, 255, Trackbar_callback_Vmax)


while cap.isOpened() == True:
    ret, frame = cap.read()

    if ret == True:
        cv2.imshow('frame', frame)
        mask = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        # 掩膜建立
        mask = cv2.inRange(mask, lower, upper)  
        #lower 和 upper 是一个含有三个值的列表或数组
        #分别对应 HSV 颜色空间中的 H（色相）、S（饱和度）和 V（明度/亮度）通道的阈值

        # 窗口创建
        cv2.imshow('mask', mask)
        
        key = cv2.waitKey(1)
        if key == 27:
            break
    else:
        break

cv2.destroyAllWindows()
cap.release()
