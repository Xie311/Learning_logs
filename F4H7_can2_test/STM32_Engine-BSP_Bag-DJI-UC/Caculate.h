#ifndef _CACULATE_H__  // 如果未定义过 "_CACULATE_H__"，则进入条件编译
#define _CACULATE_H__  // 定义 "_CACULATE_H__"

#ifdef __cplusplus  // 如果是 C++ 环境，则进行 extern "C" 处理
extern "C"
{
#endif

#include "DJI.h"  // 包含 DJI.h 头文件

    // 位置伺服函数声明，用于控制电机位置
    void positionServo(float ref, DJI_t *motor);

    // 速度伺服函数声明，用于控制电机速度
    void speedServo(float ref, DJI_t *motor);

#ifdef __cplusplus  // 如果是 C++ 环境，则结束 extern "C" 处理
}
#endif

#endif  // 结束条件编译，防止重复包含