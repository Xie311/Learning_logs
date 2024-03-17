## can

### can1相关定义

```c
uint8_t can1_rxdata[8] = {0};
extern CAN_HandleTypeDef hcan1;
static uint32_t TxMailbox1;  //用于存储CAN消息发送的邮箱编号

CAN_TxHeaderTypeDef hcan1_tx; // CAN1 发送处理单元句柄
CAN_RxHeaderTypeDef hcan1_rx; // CAN1 接受处理单元句柄
```



### can1相关函数

**wtr_can.c**

`CAN1_RX_Filter_Init(void)`   CAN过滤器配置函数

`CAN1_Interrupt_Init(void)  `  设置CAN1的中断

 `CAN1_Start(void)`  CAN1启动

---

`uint8_t CAN1_Send_Msg(CAN_MSG *msg)`  CAN1发送数据

*msg 是指向要发送的 CAN 消息的指针*

---

`weak void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)`CAN RX0接收中断回调函数



**DJI.c**

`DJI_Init()`DJI电机初始化函数

`HAL_StatusTypeDef DJI_CanMsgDecode(uint8_t can_code, uint32_t Stdid, uint8_t *fdbData)`DJI电调数据解码函数

{ `DJI_Update(DJI_t *motor, uint8_t *fdbData)`DJI电机数据更新函数

`get_dji_offset(DJI_t *motor, uint8_t *fdbData)`DJI储存偏差函数

}

 `CanTransmit_DJI_1234(CAN_HANDLER can, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq)`DJI电机CAN发送函数，电机ID 1/2/3/4

` HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)`



 can2代码配置：

  使用以下代码进行初始化

```c
can1.CAN_Rx_Filter_Init();

 can1.CAN_Start();

can1.CAN_Interrupt_Init();
```

如果使用CAN2，注意：

> 将宏定义   USE_CAN2   设置为1;
>
> CAN2 和 CAN1 共用过滤器（但基本不会产生影响），先使能CAN1再使能CAN2（CAN2打开时必须打开CAN1）