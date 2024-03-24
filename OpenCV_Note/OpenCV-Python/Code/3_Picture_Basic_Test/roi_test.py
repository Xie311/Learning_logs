import cv2
import numpy as np

# cap = cv2.VideoCapture(0)
# cap.set(10,1)

# while cap.isOpened() == True:
#     ret,frame = cap.read()
#     if ret == True:
#         roi = frame[100:200,100:200]
#         cv2.imshow('img',roi)
#         key = cv2.waitKey(1)
#         if key == 27:
#             break
#     else:
#         break
    
# cv2.destroyAllWindows()
# cap.release()

cv2.namedWindow('img1')
img=cv2.imread("winter.jpg",1)
roi1=img[0:300,10:300]

cv2.imshow('img1',roi1)
key=cv2.waitKey(0)
if key&0xff==27:
    cv2.destroyAllWindows()
    