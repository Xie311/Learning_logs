import numpy as np
import cv2

'''
img = cv2.imread('test.jpg',0)
cv2.imshow('image',img)
key = cv2.waitKey(0)
if key==27:                                 # ESC键
    cv2.destroyAllWindows()
elif key == ord('s'):                       # waitKey 函数可以返回键值，通过返回的键值(ord()方法)进行下一步操作
    cv2.imwrite('test.jpg',img)
    cv2.destroyAllWindows()
'''

img1 = cv2.imread('winter.jpg',1)
#cv2.imshow('image',img1)

# 创建一个可以手动调整大小的窗口
cv2.namedWindow('image1', cv2.WINDOW_NORMAL)

# 在窗口中显示图像
cv2.imshow('image1', img1)

key =cv2.waitKey(0)
if key ==27:
    cv2.destroyAllWindows()
elif key == ord('s'):
    cv2.imwrite('winter1.jpg',img1)
    cv2.destroyAllWindows()