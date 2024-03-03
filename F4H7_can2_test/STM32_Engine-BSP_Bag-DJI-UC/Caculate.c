#include "Caculate.h"
#include "math.h"

/**
 * @brief	增量式PID算法
 * @param	PID PID结构体
 */
void PID_Calc(PID_t *pid)
{
    // 当前误差
    pid->cur_error = pid->ref - pid->fdb;
    // 计算PID输出
    pid->output += pid->KP * (pid->cur_error - pid->error[1]) + pid->KI * pid->cur_error + pid->KD * (pid->cur_error - 2 * pid->error[1] + pid->error[0]);
    // 更新误差历史记录
    pid->error[0] = pid->error[1];
    pid->error[1] = pid->ref - pid->fdb;
    /*设定输出上限*/
    // 对输出进行限幅
    if (pid->output > pid->outputMax)
        pid->output = pid->outputMax;
    if (pid->output < -pid->outputMax)
        pid->output = -pid->outputMax;
}

/**
 * @brief	比例P算法
 * @param	PID PID结构体
 */
void P_Calc(PID_t *pid)
{
    // 当前误差
    pid->cur_error = pid->ref - pid->fdb;
    // 计算PID输出
    pid->output = pid->KP * pid->cur_error;
    /*设定输出上限*/
    // 对输出进行限幅
    if (pid->output > pid->outputMax)
        pid->output = pid->outputMax;
    if (pid->output < -pid->outputMax)
        pid->output = -pid->outputMax;

    // 如果输出的绝对值小于最小输出值，则输出置零
    if (fabs(pid->output) < pid->outputMin)
        pid->output = 0;
}

/**
 * @brief	位置伺服函数
 * @param	ref	 	目标位置
 * @param	motor	电机句柄
 * @note	指定的角度为输出轴角度，单位为角度
 */
void positionServo(float ref, DJI_t *motor)
{
    // 设置目标位置
    motor->posPID.ref = ref;
    // 获取当前位置反馈值
    motor->posPID.fdb = motor->AxisData.AxisAngle_inDegree;
    // 计算位置PID控制输出
    PID_Calc(&motor->posPID);

    // 设置速度PID的参考输入为位置PID的输出
    motor->speedPID.ref = motor->posPID.output;
    // 获取当前速度反馈值
    motor->speedPID.fdb = motor->FdbData.rpm;
    // 计算速度PID控制输出
    PID_Calc(&motor->speedPID);
}

/**
 * @brief	速度伺服函数
 * @param	ref	 	目标速度
 * @param	motor	电机句柄
 * @note	指定的速度为减速前速度，单位为rpm，发送到电机时应指定为速度PID输出
 */
void speedServo(float ref, DJI_t *motor)
{
    // 设置目标速度
    motor->speedPID.ref = ref;
    // 获取当前速度反馈值
    motor->speedPID.fdb = motor->FdbData.rpm;
    // 计算速度PID控制输出
    PID_Calc(&motor->speedPID);
}