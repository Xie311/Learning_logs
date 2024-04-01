#include "main.h"
#include "wtr_mavlink.h"
#include "stdio.h"

mavlink_SPEED_t SPEEDStructToBeSend,SPEEEStructReceived;

void user_main(void)
{
    wtrMavlink_BindChannel(&huart1, MAVLINK_COMM_0);
    wtrMavlink_BindChannel(&huart2, MAVLINK_COMM_1);

    // 开启通道0的接收中断
    wtrMavlink_StartReceiveIT(MAVLINK_COMM_0);

    for(;;)
    {
         // 模拟变化量
        SPEEDStructToBeSend.vx += 1;
        SPEEDStructToBeSend.vy += 2;
        SPEEDStructToBeSend.vz += -2;
       
        mavlink_msg_SPEED_send_struct(MAVLINK_COMM_0, &SPEEDStructToBeSend);
        HAL_UART_Transmit(&huart1,&SPEEDStructReceived,10,0xff);
        HAL_Delay(100);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // 接收通道0的消息
    wtrMavlink_UARTRxCpltCallback(huart, MAVLINK_COMM_0);
}


/**
 * @brief 接收到完整消息且校验通过后会调用这个函数。在这个函数里调用解码函数就可以向结构体写入收到的消息
 *
 * @param msg 接收到的消息
 * @return
 * @note 以上代码通过 msg->msgid 判断是哪个消息，还可以通过 msg->sysid 和 msg->compid 判断消息是从哪里来的
 */
void wtrMavlink_MsgRxCpltCallback(mavlink_message_t *msg)
{
    switch (msg->msgid) {
        case 1:
            // id = 1 的消息对应的解码函数(mavlink_msg_xxx_decode)
            mavlink_msg_SPEED_decode(msg, &SPEEDStructReceived);
            break;
        default:
            break;
    }
}
 