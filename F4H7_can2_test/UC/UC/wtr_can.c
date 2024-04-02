/*过滤器配置，can的fifo0接收*/

#include "wtr_can.h"

uint8_t CanReceiveData[8];

/**
 * @brief CAN过滤器配置函数
*/
HAL_StatusTypeDef CANFilterInit(CAN_HandleTypeDef *hcan)
{
  CAN_FilterTypeDef sFilterConfig;

// 设置CAN过滤器配置
sFilterConfig.FilterBank = 0;                            // 过滤器组编号
sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;        // 过滤器模式为标识符掩码模式
sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;       // 过滤器比例为32位
sFilterConfig.FilterIdHigh = 0x0000;                     // 过滤器标识符高位
sFilterConfig.FilterIdLow = 0x0000;                      // 过滤器标识符低位
sFilterConfig.FilterMaskIdHigh = 0x0000;                 // 过滤器掩码标识符高位
sFilterConfig.FilterMaskIdLow = 0x0000;                  // 过滤器掩码标识符低位
sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;       // 过滤器分配到接收FIFO0
sFilterConfig.FilterActivation = ENABLE;                 // 启用过滤器
sFilterConfig.SlaveStartFilterBank = 14;                 // 从第14个过滤器组开始配置

  if (HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_CAN_Start(hcan) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    Error_Handler();
  }

  return HAL_OK;
}

/**
 * @brief CAN消息解码函数
*/
void CanDataDecode(CAN_RxHeaderTypeDef RxHeader)
{
  /* CAN消息解码 */
  // 如果消息使用标准CAN ID
  if (RxHeader.IDE == CAN_ID_STD)
  {
    // 使用标准CAN ID解码消息
    DJI_CanMsgDecode(RxHeader.StdId, CanReceiveData);
  }
  // 如果消息使用扩展CAN ID
  if (RxHeader.IDE == CAN_ID_EXT)
  {
    // 当消息使用扩展CAN ID时，此处可能接收到来自VESC（Vedder Electronic Speed Controller，一种电动车电调器）的反馈消息
    //因为在某些系统中，VESC 可能会使用扩展CAN ID 来发送其状态或者反馈信息。
    // 如果不需要处理VESC反馈消息，可以将其留空或者注释掉
    ;
    ;
  }
}


/**
 * @brief CAN RX0接收中断回调函数
*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef RxHeader;
  // 如果接收到了来自 CAN 控制器 hcan1 的消息
  if (hcan->Instance == hcan1.Instance)
  {
    // 从 FIFO0 中获取接收到的消息
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, CanReceiveData) != HAL_OK)
    {
      // 如果获取消息失败，则调用错误处理函数
      Error_Handler();
    }
    // 对接收到的消息进行解码和处理
    CanDataDecode(RxHeader);
  }
}

