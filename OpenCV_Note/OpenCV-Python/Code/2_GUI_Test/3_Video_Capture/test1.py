import cv2

# 打开笔记本电脑摄像头
cap = cv2.VideoCapture(0)

# 检查摄像头是否成功打开
if not cap.isOpened():
    print("无法打开摄像头")
    exit()

# 不断循环，捕捉图像并显示
while True:
    # 从摄像头读取一帧图像
    ret, frame = cap.read()

    # 检查图像是否成功读取
    if not ret:
        print("无法从摄像头读取图像")
        break

    # 显示图像
    cv2.imshow('Camera', frame)


    # 检查用户是否按下了 'q' 键，如果是则退出循环
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 释放摄像头对象并关闭所有窗口
cap.release()
cv2.destroyAllWindows()
