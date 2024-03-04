#if (STM32F427xx)
#include "wtr_can.h"

/**********************************CAN1 相关定义***************************************/
uint8_t can1_rxdata[8] = {0};
extern CAN_HandleTypeDef hcan1;
static uint32_t TxMailbox1;  //用于存储CAN消息发送的邮箱编号

CAN_TxHeaderTypeDef hcan1_tx; // CAN1 发送处理单元句柄
CAN_RxHeaderTypeDef hcan1_rx; // CAN1 接受处理单元句柄

CAN_HANDLER can1 = {
    .rx_MSG             = {0},
    .CAN_Start          = CAN1_Start,          // FDCAN1 开始方法
    .CAN_Rx_Filter_Init = CAN1_RX_Filter_Init, // FDCAN1 过滤器初始化方法
    .CAN_Interrupt_Init = CAN1_Interrupt_Init, // FDCAN1 中断初始化方法
    .CAN_Send_MSG       = CAN1_Send_Msg,       // FDCAN1 发送消息方法
};
/**********************************CAN2 相关定义***************************************/
#if (USE_CAN2 == 1)
uint8_t can2_rxdata[8] = {0};
extern CAN_HandleTypeDef hcan2;
static uint32_t TxMailbox2;

CAN_TxHeaderTypeDef hcan2_tx; // CAN1 发送处理单元句柄
CAN_RxHeaderTypeDef hcan2_rx; // CAN1 接受处理单元句柄

CAN_HANDLER can2 = {
    .rx_MSG             = {0},
    .CAN_Start          = CAN2_Start,          // FDCAN1 开始方法
    .CAN_Rx_Filter_Init = CAN2_RX_Filter_Init, // FDCAN1 过滤器初始化方法
    .CAN_Interrupt_Init = CAN2_Interrupt_Init, // FDCAN1 中断初始化方法
    .CAN_Send_MSG       = CAN2_Send_Msg,       // FDCAN1 发送消息方法
};
#endif
/**********************************CAN1 相关函数***************************************/
/**
 * @brief CAN过滤器配置函数
 */
void CAN1_RX_Filter_Init(void)
{
    CAN_FilterTypeDef sFilterConfig;

    sFilterConfig.FilterBank           = 0;                     // 过滤器组号
    sFilterConfig.FilterMode           = CAN_FILTERMODE_IDMASK; // 过滤器模式
    sFilterConfig.FilterScale          = CAN_FILTERSCALE_32BIT; // 过滤器比特位长度
    sFilterConfig.FilterIdHigh         = 0x0000;                // 过滤器标识符高位
    sFilterConfig.FilterIdLow          = 0x0000;                // 过滤器标识符低位
    sFilterConfig.FilterMaskIdHigh     = 0x0000;                // 过滤器屏蔽标识符高位
    sFilterConfig.FilterMaskIdLow      = 0x0000;                // 过滤器屏蔽标识符低位
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;          // 过滤器与 FIFO 分配
    sFilterConfig.FilterActivation     = ENABLE;                // 过滤器激活
    sFilterConfig.SlaveStartFilterBank = 14;                    // 从过滤器开始组号

    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief  设置CAN1的中断
 */
void CAN1_Interrupt_Init(void)
{
    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief  CAN1启动
 */
void CAN1_Start(void)
{
    HAL_CAN_Start(&hcan1);
}

/**
 * @brief       CAN1发送数据
 * @param       msg  发送数据结构体  
 * @note        只允许报文的长度是0 ~ 8,不支持大于8的报文
 *
 */
uint8_t CAN1_Send_Msg(CAN_MSG *msg)  /*msg 是指向要发送的 CAN 消息的指针*/
{
    /*选择数据的长度:在 CAN 协议中，DLC 表示数据长度代码（Data Length Code）。这个字段指示了数据帧中实际包含的数据字节数*/
    switch (msg->len) {
        case 0:
            hcan1_tx.DLC = 0; /* 数据长度:0 */
            break;
        case 1:
            hcan1_tx.DLC = 1; /* 数据长度:0 */
            break;
        case 2:
            hcan1_tx.DLC = 2; /* 数据长度:0 */
            break;
        case 3:
            hcan1_tx.DLC = 3; /* 数据长度:0 */
            break;
        case 4:
            hcan1_tx.DLC = 4; /* 数据长度:0 */
            break;
        case 5:
            hcan1_tx.DLC = 5; /* 数据长度:0 */
            break;
        case 6:
            hcan1_tx.DLC = 6; /* 数据长度:0 */
            break;
        case 7:
            hcan1_tx.DLC = 7; /* 数据长度:0 */
            break;
        case 8:
            hcan1_tx.DLC = 8; /* 数据长度:0 */
            break;
        default:
            return 0;
    }
    if (REMOTE_FRAME == msg->rtr)
        hcan1_tx.RTR = CAN_RTR_REMOTE; // 远程帧
    else
        hcan1_tx.RTR = CAN_RTR_DATA; // 数据帧


    hcan1_tx.IDE = msg->ide;   // 数据帧类型
    if (msg->ide == CAN_ID_STD) {
        hcan1_tx.StdId = msg->id;   // 标准帧ID
    } else if (msg->ide == CAN_ID_EXT) {
        hcan1_tx.StdId = 0x00;      // 标准帧ID清零
        hcan1_tx.ExtId = msg->id;   // 扩展帧ID
    }

    while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0)  // 等待直到发送邮箱可用
        ; 

    if (HAL_CAN_AddTxMessage(&hcan1, &hcan1_tx, (uint8_t *)msg->buffer, &TxMailbox1) != HAL_OK) {
        Error_Handler(); // 如果CAN信息发送失败则进入死循环
    }

}
#if (USE_CAN2 == 1)
/**********************************CAN2 相关函数***************************************/
/**
 * @brief CAN过滤器配置函数
 */
void CAN2_RX_Filter_Init(void)
{
    CAN_FilterTypeDef sFilterConfig;

    sFilterConfig.FilterBank           = 14;                           // 过滤器编号
    sFilterConfig.FilterMode           = CAN_FILTERMODE_IDMASK;        // 过滤模式为标识符掩码模式
    sFilterConfig.FilterScale          = CAN_FILTERSCALE_32BIT;        // 过滤器位宽为32位
    sFilterConfig.FilterIdHigh         = 0x0000;                       // 标识符高位
    sFilterConfig.FilterIdLow          = 0x0000;                       // 标识符低位
    sFilterConfig.FilterMaskIdHigh     = 0x0000;                       // 掩码高位
    sFilterConfig.FilterMaskIdLow      = 0x0000;                       // 掩码低位
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;                 // 过滤器FIFO分配为FIFO0
    sFilterConfig.FilterActivation     = ENABLE;                       // 启用过滤器
    sFilterConfig.SlaveStartFilterBank = 14;                           // 从第14个过滤器开始

    if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK) {     // 配置CAN2的过滤器
        Error_Handler();                                               // 配置失败时的错误处理
    }
}


/**
 * @brief  设置CAN2的中断
 */
void CAN2_Interrupt_Init(void)
{
    if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief  CAN2启动
 */
void CAN2_Start(void)
{
    HAL_CAN_Start(&hcan2);
}

/**
 * @brief       CAN2发送数据
 * @param       msg  发送数据结构体
 * @note        只允许报文的长度是0 ~ 8,不支持大于8的报文
 *
 */
uint8_t CAN2_Send_Msg(CAN_MSG *msg)
{
    /*选择数据的长度:在 CAN 协议中，DLC 表示数据长度代码（Data Length Code）。这个字段指示了数据帧中实际包含的数据字节数*/
    switch (msg->len) {
        case 0:
            hcan2_tx.DLC = 0; /* 数据长度:0 */
            break;
        case 1:
            hcan2_tx.DLC = 1; /* 数据长度:0 */
            break;
        case 2:
            hcan2_tx.DLC = 2; /* 数据长度:0 */
            break;
        case 3:
            hcan2_tx.DLC = 3; /* 数据长度:0 */
            break;
        case 4:
            hcan2_tx.DLC = 4; /* 数据长度:0 */
            break;
        case 5:
            hcan2_tx.DLC = 5; /* 数据长度:0 */
            break;
        case 6:
            hcan2_tx.DLC = 6; /* 数据长度:0 */
            break;
        case 7:
            hcan2_tx.DLC = 7; /* 数据长度:0 */
            break;
        case 8:
            hcan2_tx.DLC = 8; /* 数据长度:0 */
            break;
        default:
            return 0;
    }
    if (REMOTE_FRAME == msg->rtr)
        hcan2_tx.RTR = CAN_RTR_REMOTE; // 远程帧
    else
        hcan2_tx.RTR = CAN_RTR_DATA; // 数据帧

    hcan2_tx.StdId = msg->id;      // 设置标准帧的标识符
    hcan2_tx.IDE   = CAN_ID_STD;   // 设置消息的帧类型为标准帧

    while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) == 0)  // 等待直到发送邮箱可用
        ;
    if (HAL_CAN_AddTxMessage(&hcan2, &hcan2_tx, (uint8_t *)msg->buffer, &TxMailbox2) != HAL_OK) {
        Error_Handler(); // 如果CAN信息发送失败则进入死循环
    }
}
#endif

/**
 * @brief CAN RX0接收中断回调函数
 */
__weak void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    ;
}
#endif

#if (STM32H723xx)
#include "wtr_can.h"
#if (USE_FDCAN1 == 1)
extern FDCAN_HandleTypeDef hfdcan1;
static FDCAN_FilterTypeDef hfdcan1_rx_filter0; // FDCAN1 滤波器0 句柄
FDCAN_RxHeaderTypeDef hfdcan1_rx;              // FDCAN1 接受处理单元句柄
FDCAN_TxHeaderTypeDef hfdcan1_tx;              // FDCAN1 发送处理单元句柄
uint8_t fdcan1_rxdata[8] = {0};
#endif
#if (USE_FDCAN2 == 1)
extern FDCAN_HandleTypeDef hfdcan2;
static FDCAN_FilterTypeDef hfdcan2_rx_filter0; // FDCAN2 滤波器0 句柄
FDCAN_RxHeaderTypeDef hfdcan2_rx;              // FDCAN2 接受处理单元句柄
FDCAN_TxHeaderTypeDef hfdcan2_tx;              // FDCAN2 发送处理单元句柄
uint8_t fdcan2_rxdata[8] = {0};
#endif
#if (USE_FDCAN3 == 1)
extern FDCAN_HandleTypeDef hfdcan3;
static FDCAN_FilterTypeDef hfdcan3_rx_filter0; // FDCAN3 滤波器0 句柄
FDCAN_RxHeaderTypeDef hfdcan3_rx;              // FDCAN3 接受处理单元句柄
FDCAN_TxHeaderTypeDef hfdcan3_tx;              // FDCAN3 发送处理单元句柄
uint8_t fdcan3_rxdata[8] = {0};
#endif

#if (USE_FDCAN1 == 1)
FDCAN_HANDLER fdcan1 = {
    .rx_MSG                     = {0},
    .FDCAN_Start                = FDCAN1_Start,                // FDCAN1 开始方法
    .FDCAN_Rx_Filter_Init       = FDCAN1_RX_Filter_Init,       // FDCAN1 过滤器初始化方法
    .FDCAN_Interrupt_Init       = FDCAN1_Interrupt_Init,       // FDCAN1 中断初始化方法
    .FDCAN_Send_MSG             = FDCAN1_Send_Msg,             // FDCAN1 发送消息方法
    .FDCAN_Update_RXFIFO_Status = FDCAN1_Update_RXFIFO_Status, // FDCAN1 更新接收FIFO状态方法
};
#endif
#if (USE_FDCAN2 == 1)
FDCAN_HANDLER fdcan2 = {
    .rx_MSG                     = {0},
    .FDCAN_Start                = FDCAN2_Start,                // FDCAN2 开始方法
    .FDCAN_Rx_Filter_Init       = FDCAN2_RX_Filter_Init,       // FDCAN2 过滤器初始化方法
    .FDCAN_Interrupt_Init       = FDCAN2_Interrupt_Init,       // FDCAN2 中断初始化方法
    .FDCAN_Send_MSG             = FDCAN2_Send_Msg,             // FDCAN2 发送消息方法
    .FDCAN_Update_RXFIFO_Status = FDCAN2_Update_RXFIFO_Status, // FDCAN2 更新接收FIFO状态方法
};
#endif
#if (USE_FDCAN3 == 1)
FDCAN_HANDLER fdcan3 = {
    .rx_MSG                     = {0},
    .FDCAN_Start                = FDCAN3_Start,                // FDCAN3 开始方法
    .FDCAN_Rx_Filter_Init       = FDCAN3_RX_Filter_Init,       // FDCAN3 过滤器初始化方法
    .FDCAN_Interrupt_Init       = FDCAN3_Interrupt_Init,       // FDCAN3 中断初始化方法
    .FDCAN_Send_MSG             = FDCAN3_Send_Msg,             // FDCAN3 发送消息方法
    .FDCAN_Update_RXFIFO_Status = FDCAN3_Update_RXFIFO_Status, // FDCAN3 更新接收FIFO状态方法
};
#endif
/*************************************用户函数**************************************/
#if (USE_FDCAN1 == 1)
/**
 * @brief  设置并初始化FDCAN1滤波器                                                               //RxFifo0ElmtsNbr是用来设置RX FIFO0的元素数量的成员。
 * @note   1. FDCAN_HandleTypeDef 对象句柄的成员 RxFifo0 Elmts Nbr设置大于0时，表示启用 RXFIFO0;   //当RxFifo0ElmtsNbr设置为大于0时，表示启用了RX FIFO0。
 * @note   2. 如果启用 RXFIFO0 ,那么滤波器必须关联到 RXFIFO0, 即 FilterConfig 必须赋值 FDCAN_FILTER_TO_RXFIFO0;
 * 
 * @note   在FDCAN_HandleTypeDef 这个结构体中，RxFifo0ElmtsNbr是用来设置RX FIFO0的元素数量的成员。当RxFifo0ElmtsNbr设置为大于0时，表示启用了RX FIFO0。
           RX FIFO0是FDCAN的接收缓冲区之一，用于存储接收到的CAN帧。启用RX FIFO0可以使得接收到的CAN帧按照一定的优先级进行存储，便于后续处理。
           通常情况下，RX FIFO0用于存储高优先级的CAN帧，而另外的RX FIFO1则用于存储低优先级的CAN帧。

           配置FDCAN的RX FIFO0可以通过以下步骤实现：
           1.初始化FDCAN模块，包括时钟配置、引脚配置等。
           2.配置FDCAN的工作模式，包括初始化CAN控制器。
           3.配置FDCAN的接收器，包括设置过滤器、使能接收中断等。
           4.配置FDCAN的RX FIFO0，包括设置RX FIFO0的元素数量，使其大于0以启用RX FIFO0。
           //RX FIFO0 的元素数量表示该 FIFO 中可以存储的 CAN 帧的数量。每个 CAN 帧作为一个元素存储在 FIFO 中.这个数量决定了接收缓冲区的大小
 */
void FDCAN1_RX_Filter_Init(void)
{
    hfdcan1_rx_filter0.IdType       = FDCAN_STANDARD_ID;       // 只接收标准帧ID
    hfdcan1_rx_filter0.FilterIndex  = 0;                       // 滤波器索引0
    hfdcan1_rx_filter0.FilterType   = FDCAN_FILTER_MASK;       // 滤波器类型
    hfdcan1_rx_filter0.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // 滤波器关联到RXFIFO0
    hfdcan1_rx_filter0.FilterID1    = 0x00;                    // 滤波ID1 0x00
    hfdcan1_rx_filter0.FilterID2    = 0x00;                    // 滤波ID2 0x00

    // 设置失败进入死循环
    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &hfdcan1_rx_filter0) != HAL_OK) {
        while (1) {
            ;
        }
    }

    /**
     * @note    设置滤波器全局配置
     *          设置标准帧ID，接收的报文ID没有匹配上滤波器时，选择拒绝接收(没有匹配上时,可以选择放入FIFO0或者FIFO1)。
     *          设置拓展帧ID，接收的报文ID没有匹配上滤波器时，选择拒绝接收。
     *          设置是否拒绝远程标准帧，ENABLE代表拒绝接收。  //这两个参数用于启用或禁用滤波器。这里设置为DISABLE，表示禁用全局滤波器。
     *          设置是否拒绝远程拓展帧，ENABLE代表拒绝接收。
     */
    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE) != HAL_OK) /* 设置FDCAN1滤波器0全局配置  */
    {
        while (1) {
            ;
        }
    }
}

/**
 * @brief  设置FDCAN1的中断
 * @note   1. 设置收到新的数据就产生中断。
 * @note   2. 配置水印中断防止FIFO溢出（水印中断：当FIFO中的消息数量达到预设的水印值时，触发中断）
 * @note   3. 配置FIFO溢出中断，防止FIFO溢出导致丢失报文。
 */
void FDCAN1_Interrupt_Init(void)
{
    // 使能接受新数据中断 
    /*激活FDCAN1的接收FIFO0新消息中断通知，并检查激活过程是否成功。如果激活过程失败，则进入一个无限循环，使程序停留在这里，防止后续代码执行
    第三个参数为0表示在激活之前先清除任何挂起的中断*/
    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
    // 设置FIFO0溢出中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_FULL, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
    // 设置水印中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_WATERMARK, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
}

/**
 * @brief   更新FDCAN接收FIFO的状态寄存器
 * @param   hfdcan  FDCAN句柄
 * @param   fdcan   CAN对象结构体
 * @note    FDCAN控制器必须配置RX FIFO后才能使用
 */
void FDCAN1_Update_RXFIFO_Status(FDCAN_HandleTypeDef *hfdcan, FDCAN_HANDLER *fdcan)
{
    if (fdcan == &fdcan1) { // 检查FDCAN对象是否为FDCAN1
        fdcan->RXFxS = hfdcan->Instance->RXF0S; // 更新FDCAN1接收FIFO状态到FDCAN对象结构体
    }
    /**
     * note：
    fdcan->RXFxS是FDCAN控制器中RX FIFO的状态寄存器。
    在这个寄存器中，包含了与 RX FIFO 相关的状态信息，例如已接收到的帧数量、溢出状态等。

    hfdcan->Instance->RXF0S：hfdcan 是 FDCAN 控制器的句柄，Instance 是指向 FDCAN 寄存器组的指针。
    RXF0S 则是 FDCAN 控制器中 RX FIFO 0 的状态寄存器。通过 hfdcan->Instance->RXF0S，可以访问到 RX FIFO 0 的状态寄存器。

    这行代码的作用是将 RX FIFO 0 的状态寄存器中的值复制给了 FDCAN 控制器中 RX FIFO 的状态寄存器。
    这样可以使得 fdcan->RXFxS 中保存的状态信息与 RX FIFO 0 的状态信息一致，以便后续进行状态监测和处理。
    */

    // 解析FDCAN1接收FIFO状态中的信息
    fdcan->FxGI = (fdcan->RXFxS >> 8) & 0x1F; // 获取FIFO0读指针
    fdcan->FxPI = (fdcan->RXFxS >> 16) & 0x1F; // 获取FIFO0写指针
    fdcan->FxFL = fdcan->RXFxS & 0x3F; // 获取FIFO0接收到的消息数量
}

/**
 * @brief       FDCAN1发送数据
 * @param       msg  发送数据结构体
 * @note        只允许报文的长度是0 ~ 8,不支持大于8的报文
 *
 */
uint8_t FDCAN1_Send_Msg(CAN_MSG *msg)
{
    // 选择数据的长度
    switch (msg->len) {
        case 0:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_0; /* 数据长度:0 */
            break;
        case 1:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_1; /* 数据长度:1 */
            break;
        case 2:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_2; /* 数据长度:2 */
            break;
        case 3:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_3; /* 数据长度:3 */
            break;
        case 4:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_4; /* 数据长度:4 */
            break;
        case 5:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_5; /* 数据长度:5 */
            break;
        case 6:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_6; /* 数据长度:6 */
            break;
        case 7:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_7; /* 数据长度:7 */
            break;
        case 8:
            hfdcan1_tx.DataLength = FDCAN_DLC_BYTES_8; /* 数据长度:8 */
            break;
        default:
            return 0;
    }

    hfdcan1_tx.Identifier          = msg->id;            // 32位ID
    hfdcan1_tx.IdType              = FDCAN_STANDARD_ID;  // 标准ID
    hfdcan1_tx.TxFrameType         = FDCAN_DATA_FRAME;   // 数据帧
    hfdcan1_tx.ErrorStateIndicator = FDCAN_ESI_ACTIVE;   // ESI位
    hfdcan1_tx.BitRateSwitch       = FDCAN_BRS_OFF;      // 关闭速率转换
    hfdcan1_tx.FDFormat            = FDCAN_CLASSIC_CAN;  // 标准CAN模式
    hfdcan1_tx.TxEventFifoControl  = FDCAN_NO_TX_EVENTS; // 无发送事件
    hfdcan1_tx.MessageMarker       = 0;

    if (REMOTE_FRAME == msg->rtr)
        hfdcan1_tx.TxFrameType = FDCAN_REMOTE_FRAME; // 远程帧
    else
        hfdcan1_tx.TxFrameType = FDCAN_DATA_FRAME; // 数据帧

    // 将需要发送的数据压入到TX FIFO
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &hfdcan1_tx, (uint8_t *)msg->buffer) == HAL_OK) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief  FDCAN1启动
 */
void FDCAN1_Start(void)
{
    HAL_FDCAN_Start(&hfdcan1);
}

#endif
#if (USE_FDCAN2 == 1)
/**
 * @brief  设置并初始化FDCAN2滤波器
 * @note   1. FDCAN_HandleTypeDef 对象句柄的成员 RxFifo0 Elmts Nbr设置大于0时，表示启用 RXFIFO0;
 * @note   2. 如果启用 RXFIFO0 ,那么滤波器必须关联到 RXFIFO0, 即 FilterConfig 必须赋值 FDCAN_FILTER_TO_RXFIFO0;
 */
void FDCAN2_RX_Filter_Init(void)
{
    hfdcan2_rx_filter0.IdType       = FDCAN_STANDARD_ID;       // 只接收标准帧ID
    hfdcan2_rx_filter0.FilterIndex  = 0;                       // 滤波器索引0
    hfdcan2_rx_filter0.FilterType   = FDCAN_FILTER_MASK;       // 滤波器类型
    hfdcan2_rx_filter0.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // 滤波器关联到RXFIFO0
    hfdcan2_rx_filter0.FilterID1    = 0x00;                    // 滤波ID1 0x00
    hfdcan2_rx_filter0.FilterID2    = 0x00;                    // 滤波ID2 0x00

    // 设置失败进入死循环
    if (HAL_FDCAN_ConfigFilter(&hfdcan2, &hfdcan2_rx_filter0) != HAL_OK) {
        while (1) {
            ;
        }
    }

    /**
     * @note    设置滤波器全局配置
     *          设置标准帧ID，接收的报文ID没有匹配上滤波器时，选择拒绝接收(没有匹配上时,可以选择放入FIFO0或者FIFO1)。
     *          设置拓展帧ID，接收的报文ID没有匹配上滤波器时，选择拒绝接收。
     *          设置是否拒绝远程标准帧，ENABLE代表拒绝接收。
     *          设置是否拒绝远程拓展帧，ENABLE代表拒绝接收。
     */
    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE) != HAL_OK) /* 设置FDCAN2滤波器0全局配置  */
    {
        while (1) {
            ;
        }
    }
}

/**
 * @brief  设置FDCAN2的中断
 * @note   1. 设置收到新的数据就产生中断。
 * @note   2. 配置水印中断防止FIFO溢出。
 * @note   3. 配置FIFO溢出中断，防止FIFO溢出导致丢失报文。
 */
void FDCAN2_Interrupt_Init(void)
{
    // 使能接受新数据中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
    // 设置FIFO0溢出中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_FULL, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
    // 设置水印中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_WATERMARK, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
}

/**
 * @brief   更新FDCAN接收FIFO的状态寄存器
 * @param   hfdcan  FDCAN句柄
 * @param   fdcan   CAN对象结构体
 * @note    FDCAN控制器必须配置RX FIFO后才能使用
 */
void FDCAN2_Update_RXFIFO_Status(FDCAN_HandleTypeDef *hfdcan, FDCAN_HANDLER *fdcan)
{
    if (fdcan == &fdcan2) {
        fdcan->RXFxS = hfdcan->Instance->RXF0S;
    }
    fdcan->FxGI = (fdcan->RXFxS >> 8) & 0x1F;
    fdcan->FxPI = (fdcan->RXFxS >> 16) & 0x1F;
    fdcan->FxFL = fdcan->RXFxS & 0x3F;
}

/**
 * @brief       FDCAN2发送数据
 * @param       msg  发送数据结构体
 * @note        只允许报文的长度是0 ~ 8,不支持大于8的报文
 *
 */
uint8_t FDCAN2_Send_Msg(CAN_MSG *msg)
{
    // 选择数据的长度
    switch (msg->len) {
        case 0:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_0; /* 数据长度:0 */
            break;
        case 1:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_1; /* 数据长度:1 */
            break;
        case 2:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_2; /* 数据长度:2 */
            break;
        case 3:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_3; /* 数据长度:3 */
            break;
        case 4:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_4; /* 数据长度:4 */
            break;
        case 5:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_5; /* 数据长度:5 */
            break;
        case 6:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_6; /* 数据长度:6 */
            break;
        case 7:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_7; /* 数据长度:7 */
            break;
        case 8:
            hfdcan2_tx.DataLength = FDCAN_DLC_BYTES_8; /* 数据长度:8 */
            break;
        default:
            return 0;
    }

    hfdcan2_tx.Identifier          = msg->id;            // 32位ID
    hfdcan2_tx.IdType              = FDCAN_STANDARD_ID;  // 标准ID
    hfdcan2_tx.TxFrameType         = FDCAN_DATA_FRAME;   // 数据帧
    hfdcan2_tx.ErrorStateIndicator = FDCAN_ESI_ACTIVE;   // ESI位
    hfdcan2_tx.BitRateSwitch       = FDCAN_BRS_OFF;      // 关闭速率转换
    hfdcan2_tx.FDFormat            = FDCAN_CLASSIC_CAN;  // 标准CAN模式
    hfdcan2_tx.TxEventFifoControl  = FDCAN_NO_TX_EVENTS; // 无发送事件
    hfdcan2_tx.MessageMarker       = 0;

    if (REMOTE_FRAME == msg->rtr)
        hfdcan2_tx.TxFrameType = FDCAN_REMOTE_FRAME; // 远程帧
    else
        hfdcan2_tx.TxFrameType = FDCAN_DATA_FRAME; // 数据帧

    // 将需要发送的数据压入到TX FIFO
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &hfdcan2_tx, (uint8_t *)msg->buffer) == HAL_OK) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief  FDCAN2启动
 */
void FDCAN2_Start(void)
{
    HAL_FDCAN_Start(&hfdcan2);
}

#endif
#if (USE_FDCAN3 == 1)
/**
 * @brief  设置并初始化FDCAN3滤波器
 * @note   1. FDCAN_HandleTypeDef 对象句柄的成员 RxFifo0 Elmts Nbr设置大于0时，表示启用 RXFIFO0;
 * @note   2. 如果启用 RXFIFO0 ,那么滤波器必须关联到 RXFIFO0, 即 FilterConfig 必须赋值 FDCAN_FILTER_TO_RXFIFO0;
 */
void FDCAN3_RX_Filter_Init(void)
{
    hfdcan3_rx_filter0.IdType       = FDCAN_STANDARD_ID;       // 只接收标准帧ID
    hfdcan3_rx_filter0.FilterIndex  = 0;                       // 滤波器索引0
    hfdcan3_rx_filter0.FilterType   = FDCAN_FILTER_MASK;       // 滤波器类型
    hfdcan3_rx_filter0.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // 滤波器关联到RXFIFO0
    hfdcan3_rx_filter0.FilterID1    = 0x00;                    // 滤波ID1 0x00
    hfdcan3_rx_filter0.FilterID2    = 0x00;                    // 滤波ID2 0x00

    // 设置失败进入死循环
    if (HAL_FDCAN_ConfigFilter(&hfdcan3, &hfdcan3_rx_filter0) != HAL_OK) {
        while (1) {
            ;
        }
    }

    /**
     * @note    设置滤波器全局配置
     *          设置标准帧ID，接收的报文ID没有匹配上滤波器时，选择拒绝接收(没有匹配上时,可以选择放入FIFO0或者FIFO1)。
     *          设置拓展帧ID，接收的报文ID没有匹配上滤波器时，选择拒绝接收。
     *          设置是否拒绝远程标准帧，ENABLE代表拒绝接收。
     *          设置是否拒绝远程拓展帧，ENABLE代表拒绝接收。
     */
    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE) != HAL_OK) /* 设置FDCAN3滤波器0全局配置  */
    {
        while (1) {
            ;
        }
    }
}

/**
 * @brief  设置FDCAN3的中断
 * @note   1. 设置收到新的数据就产生中断。
 * @note   2. 配置水印中断防止FIFO溢出。
 * @note   3. 配置FIFO溢出中断，防止FIFO溢出导致丢失报文。
 */
void FDCAN3_Interrupt_Init(void)
{
    // 使能接受新数据中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
    // 设置FIFO0溢出中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_FULL, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
    // 设置水印中断
    if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_WATERMARK, 0) != HAL_OK) {
        while (1) {
            ;
        }
    }
}

/**
 * @brief   更新FDCAN接收FIFO的状态寄存器
 * @param   hfdcan  FDCAN句柄
 * @param   fdcan   CAN对象结构体
 * @note    FDCAN控制器必须配置RX FIFO后才能使用
 */
void FDCAN3_Update_RXFIFO_Status(FDCAN_HandleTypeDef *hfdcan, FDCAN_HANDLER *fdcan)
{
    if (fdcan == &fdcan3) {
        fdcan->RXFxS = hfdcan->Instance->RXF0S;
    }
    fdcan->FxGI = (fdcan->RXFxS >> 8) & 0x1F;
    fdcan->FxPI = (fdcan->RXFxS >> 16) & 0x1F;
    fdcan->FxFL = fdcan->RXFxS & 0x3F;
}

/**
 * @brief       FDCAN3发送数据
 * @param       msg  发送数据结构体
 * @note        只允许报文的长度是0 ~ 8,不支持大于8的报文
 *
 */
uint8_t FDCAN3_Send_Msg(CAN_MSG *msg)
{
    // 选择数据的长度
    switch (msg->len) {
        case 0:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_0; /* 数据长度:0 */
            break;
        case 1:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_1; /* 数据长度:1 */
            break;
        case 2:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_2; /* 数据长度:2 */
            break;
        case 3:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_3; /* 数据长度:3 */
            break;
        case 4:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_4; /* 数据长度:4 */
            break;
        case 5:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_5; /* 数据长度:5 */
            break;
        case 6:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_6; /* 数据长度:6 */
            break;
        case 7:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_7; /* 数据长度:7 */
            break;
        case 8:
            hfdcan3_tx.DataLength = FDCAN_DLC_BYTES_8; /* 数据长度:8 */
            break;
        default:
            return 0;
    }

    hfdcan3_tx.Identifier          = msg->id;            // 32位ID
    hfdcan3_tx.IdType              = FDCAN_STANDARD_ID;  // 标准ID
    hfdcan3_tx.TxFrameType         = FDCAN_DATA_FRAME;   // 数据帧
    hfdcan3_tx.ErrorStateIndicator = FDCAN_ESI_ACTIVE;   // ESI位
    hfdcan3_tx.BitRateSwitch       = FDCAN_BRS_OFF;      // 关闭速率转换
    hfdcan3_tx.FDFormat            = FDCAN_CLASSIC_CAN;  // 标准CAN模式
    hfdcan3_tx.TxEventFifoControl  = FDCAN_NO_TX_EVENTS; // 无发送事件
    hfdcan3_tx.MessageMarker       = 0;

    if (REMOTE_FRAME == msg->rtr)
        hfdcan3_tx.TxFrameType = FDCAN_REMOTE_FRAME; // 远程帧
    else
        hfdcan3_tx.TxFrameType = FDCAN_DATA_FRAME; // 数据帧

    // 将需要发送的数据压入到TX FIFO
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &hfdcan3_tx, (uint8_t *)msg->buffer) == HAL_OK) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief  FDCAN3启动
 */
void FDCAN3_Start(void)
{
    HAL_FDCAN_Start(&hfdcan3);
}

#endif
/**
 * @brief FIFO0接收中断回调函数
 */
__weak void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    ;
}

#endif