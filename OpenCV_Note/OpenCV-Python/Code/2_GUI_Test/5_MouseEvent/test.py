import cv2 
import numpy as np

# # 左键按下时变为True
# drawing = False
# # 模式选择
# mode = False
# ix,iy = -1,-1

# #鼠标事件回调函数
# def draw(event,x,y,flags,param):
#     global drawing,mode,ix,iy
#     if event == cv2.EVENT_LBUTTONDOWN:
#         drawing = True
#         ix,iy = x,y
#     # event 检测鼠标移动，flags 检测鼠标左键是否按下
#     elif event == cv2.EVENT_MOUSEMOVE and flags == cv2.EVENT_FLAG_LBUTTON:
#         if drawing:
#             if mode:
#                 cv2.circle(frame, (x, y), 10, (0, 255, 0), -1, cv2.LINE_AA)
#             else:
#                 cv2.rectangle(frame, (x-10, y-10), (x, y), (0, 0, 255), -1, cv2.LINE_AA)
#     elif event == cv2.EVENT_LBUTTONUP:
#         drawing = False

def draw_circle(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDBLCLK:
        cv2.circle(param,(x,y),100,(255,0,0),1,cv2.LINE_AA)

cap=cv2.VideoCapture(0)
cv2.namedWindow('img',cv2.WINDOW_NORMAL)
frame = np.zeros((512, 512, 3), np.uint8)  # 定义一个空的图像
cv2.setMouseCallback('img',draw_circle,param=frame)

while(1):
    ret,frame=cap.read()
    if ret:
        cv2.imshow('img',frame)

    key = cv2.waitKey(1) & 0xFF
    if key == 27:
        break
    # elif key == ord('m'):
    #     mode = not mode

cap.release()
cv2.destroyAllWindows()

