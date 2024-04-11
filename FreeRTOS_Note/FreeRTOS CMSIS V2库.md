# FreeRTOS CMSIS V2库

```c
#ifndef CMSIS_OS2_H_
#define CMSIS_OS2_H_

#ifdef  __cplusplus
extern "C" {
#endif

/// 线程的属性结构体
typedef struct {
  const char                   *name;       ///< 线程的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
  void                   *stack_mem;        ///< 栈内存
  uint32_t                stack_size;       ///< 栈内存大小
  osPriority_t              priority;       ///< 初始线程优先级 (默认: osPriorityNormal)
  TZ_ModuleId_t            tz_module;       ///< TrustZone 模块标识符
  uint32_t                  reserved;       ///< 保留字段 (必须为 0)
} osThreadAttr_t;

/// 定时器的属性结构体
typedef struct {
  const char                   *name;       ///< 定时器的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
} osTimerAttr_t;

/// 事件标志的属性结构体
typedef struct {
  const char                   *name;       ///< 事件标志的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
} osEventFlagsAttr_t;

/// 互斥量的属性结构体
typedef struct {
  const char                   *name;       ///< 互斥量的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
} osMutexAttr_t;

/// 信号量的属性结构体
typedef struct {
  const char                   *name;       ///< 信号量的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
} osSemaphoreAttr_t;

/// 内存池的属性结构体
typedef struct {
  const char                   *name;       ///< 内存池的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
  void                      *mp_mem;        ///< 数据存储内存
  uint32_t                   mp_size;       ///< 数据存储内存大小
} osMemoryPoolAttr_t;

/// 消息队列的属性结构体
typedef struct {
  const char                   *name;       ///< 消息队列的名称
  uint32_t                 attr_bits;       ///< 属性位
  void                      *cb_mem;        ///< 控制块内存
  uint32_t                   cb_size;       ///< 控制块内存大小
  void                      *mq_mem;        ///< 数据存储内存
  uint32_t                   mq_size;       ///< 数据存储内存大小
} osMessageQueueAttr_t;

//  ==== Kernel Management Functions ====

/// 初始化RTOS内核
/// \return 表示函数执行状态的状态码
osStatus_t osKernelInitialize (void);

/// 获取RTOS内核信息
/// \param[out]    version       指针用于获取版本信息
/// \param[out]    id_buf        指针用于获取内核标识字符串
/// \param[in]     id_size       内核标识字符串的缓冲区大小
/// \return 表示函数执行状态的状态码
osStatus_t osKernelGetInfo (osVersion_t *version, char *id_buf, uint32_t id_size);

/// 获取当前RTOS内核状态
/// \return 当前RTOS内核状态
osKernelState_t osKernelGetState (void);

/// 启动RTOS内核调度器
/// \return 表示函数执行状态的状态码
osStatus_t osKernelStart (void);

/// 锁定RTOS内核调度器
/// \return 之前的锁定状态 (1 - 锁定, 0 - 未锁定, 如果为负值则为错误码)
int32_t osKernelLock (void);

/// 解锁RTOS内核调度器
/// \return 之前的锁定状态 (1 - 锁定, 0 - 未锁定, 如果为负值则为错误码)
int32_t osKernelUnlock (void);

/// 恢复RTOS内核调度器的锁定状态
/// \param[in]     lock          由 \ref osKernelLock 或 \ref osKernelUnlock 获取的锁定状态
/// \return 新的锁定状态 (1 - 锁定, 0 - 未锁定, 如果为负值则为错误码)
int32_t osKernelRestoreLock (int32_t lock);

/// 挂起RTOS内核调度器
/// \return 睡眠或关机模式的时间刻度数
uint32_t osKernelSuspend (void);

/// 恢复RTOS内核调度器
/// \param[in]     sleep_ticks   系统处于睡眠或关机模式的时间刻度数
void osKernelResume (uint32_t sleep_ticks);

/// 获取RTOS内核的时间刻度计数
/// \return RTOS内核当前的时间刻度计数
uint32_t osKernelGetTickCount (void);

/// 获取RTOS内核的时间刻度频率
/// \return 时间刻度频率，即每秒的时间刻度数
uint32_t osKernelGetTickFreq (void);

/// 获取RTOS内核的系统定时器计数
/// \return RTOS内核当前系统定时器计数的32位值
uint32_t osKernelGetSysTimerCount (void);

/// 获取RTOS内核的系统定时器频率
/// \return 系统定时器的频率，即每秒的定时器滴答数
uint32_t osKernelGetSysTimerFreq (void);


//  ==== Thread Management Functions ====

/// 创建线程并将其添加到活动线程中
/// \param[in]     func          线程函数
/// \param[in]     argument      作为启动参数传递给线程函数的指针
/// \param[in]     attr          线程属性; NULL: 默认值
/// \return 线程ID以供其他函数引用，如果出错则返回NULL
osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);

/// 获取线程的名称
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return NULL结尾的名称字符串
const char *osThreadGetName (osThreadId_t thread_id);

/// 返回当前正在运行的线程的线程ID
/// \return 线程ID以供其他函数引用，如果出错则返回NULL
osThreadId_t osThreadGetId (void);

/// 获取线程的当前状态
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 指定线程的当前线程状态
osThreadState_t osThreadGetState (osThreadId_t thread_id);

/// 获取线程的堆栈大小
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 堆栈大小（以字节为单位）
uint32_t osThreadGetStackSize (osThreadId_t thread_id);

/// 基于执行期间堆栈水位标记记录，获取线程的可用堆栈空间
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 剩余的堆栈空间（以字节为单位）
uint32_t osThreadGetStackSpace (osThreadId_t thread_id);

/// 更改线程的优先级
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \param[in]     priority      线程函数的新优先级值
/// \return 表示函数执行状态的状态码
osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);

/// 获取线程的当前优先级
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 指定线程的当前优先级值
osPriority_t osThreadGetPriority (osThreadId_t thread_id);

/// 将控制传递给下一个处于状态 \b READY 的线程
/// \return 表示函数执行状态的状态码
osStatus_t osThreadYield (void);

/// 挂起线程的执行
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 表示函数执行状态的状态码
osStatus_t osThreadSuspend (osThreadId_t thread_id);

/// 恢复线程的执行
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 表示函数执行状态的状态码
osStatus_t osThreadResume (osThreadId_t thread_id);

/// 分离线程（线程存储可以在线程终止时回收）
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 表示函数执行状态的状态码
osStatus_t osThreadDetach (osThreadId_t thread_id);

/// 等待指定的线程终止
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 表示函数执行状态的状态码
osStatus_t osThreadJoin (osThreadId_t thread_id);

/// 终止当前正在运行的线程的执行
__NO_RETURN void osThreadExit (void);

/// 终止线程的执行
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \return 表示函数执行状态的状态码
osStatus_t osThreadTerminate (osThreadId_t thread_id);

/// 获取活动线程的数量
/// \return 活动线程的数量
uint32_t osThreadGetCount (void);

/// 枚举活动线程
/// \param[out]    thread_array  用于检索线程ID的数组指针
/// \param[in]     array_items   用于检索线程ID的数组中的最大项数
/// \return 枚举的线程数
uint32_t osThreadEnumerate (osThreadId_t *thread_array, uint32_t array_items);


//  ==== Thread Flags Functions ====

/// 设置线程的指定标志
/// \param[in]     thread_id     由 \ref osThreadNew 或 \ref osThreadGetId 获取的线程ID
/// \param[in]     flags         指定应设置的线程标志
/// \return 设置后的线程标志，如果最高位设置为错误码
uint32_t osThreadFlagsSet (osThreadId_t thread_id, uint32_t flags);

/// 清除当前运行线程的指定线程标志
/// \param[in]     flags         指定应清除的线程标志
/// \return 清除前的线程标志，如果最高位设置为错误码
uint32_t osThreadFlagsClear (uint32_t flags);

/// 获取当前运行线程的当前线程标志
/// \return 当前线程标志
uint32_t osThreadFlagsGet (void);

/// 等待当前运行线程的一个或多个线程标志变为信号状态
/// \param[in]     flags         等待的标志
/// \param[in]     options       指定标志选项（osFlagsXxxx）
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 清除前的线程标志，如果最高位设置为错误码
uint32_t osThreadFlagsWait (uint32_t flags, uint32_t options, uint32_t timeout);


//  ==== Generic Wait Functions ====

/// 等待超时（时间延迟）
/// \param[in]     ticks         \ref CMSIS_RTOS_TimeOutValue "时间刻度"值
/// \return 表示函数执行状态的状态码
osStatus_t osDelay (uint32_t ticks);

/// 等待直到指定的时间
/// \param[in]     ticks         以时间刻度为单位的绝对时间
/// \return 表示函数执行状态的状态码
osStatus_t osDelayUntil (uint32_t ticks);


//  ==== Timer Management Functions ====

/// 创建和初始化定时器
/// \param[in]     func          回调函数的函数指针
/// \param[in]     type          \ref osTimerOnce 表示单次定时器或 \ref osTimerPeriodic 表示周期性行为
/// \param[in]     argument      传递给定时器回调函数的参数
/// \param[in]     attr          定时器属性; NULL: 默认值
/// \return 定时器ID以供其他函数引用，如果出错则返回NULL
osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);

/// 启动或重启定时器
/// \param[in]     timer_id      由 \ref osTimerNew 获取的定时器ID
/// \param[in]     ticks         \ref CMSIS_RTOS_TimeOutValue "时间刻度"值
/// \return 表示函数执行状态的状态码
osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t ticks);

/// 停止定时器
/// \param[in]     timer_id      由 \ref osTimerNew 获取的定时器ID
/// \return 表示函数执行状态的状态码
osStatus_t osTimerStop (osTimerId_t timer_id);

/// 删除定时器
/// \param[in]     timer_id      由 \ref osTimerNew 获取的定时器ID
/// \return 表示函数执行状态的状态码
osStatus_t osTimerDelete (osTimerId_t timer_id);


//  ==== Event Flags Management Functions ====

/// 创建和初始化事件标志
/// \param[in]     attr          事件标志的属性; NULL: 默认值
/// \return 事件标志ID以供其他函数引用，如果出错则返回NULL
osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);

/// 获取事件标志的状态
/// \param[in]     ef_id         由 \ref osEventFlagsNew 获取的事件标志ID
/// \return 当前事件标志的状态（32位表示），如果出错则返回0xFFFFFFFF
uint32_t osEventFlagsGet (osEventFlagsId_t ef_id);

/// 设置事件标志的状态
/// \param[in]     ef_id         由 \ref osEventFlagsNew 获取的事件标志ID
/// \param[in]     flags         表示要设置的事件标志位
/// \return 表示函数执行状态的状态码
osStatus_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);

/// 清除事件标志的状态
/// \param[in]     ef_id         由 \ref osEventFlagsNew 获取的事件标志ID
/// \param[in]     flags         表示要清除的事件标志位
/// \return 表示函数执行状态的状态码
osStatus_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);

/// 等待指定的事件标志变为信号状态
/// \param[in]     ef_id         由 \ref osEventFlagsNew 获取的事件标志ID
/// \param[in]     flags         等待的标志
/// \param[in]     options       指定标志选项（osFlagsXxxx）
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 当事件标志为信号状态时返回等待的标志，否则返回错误码
uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);


//  ==== Mutex Management Functions ====

/// 创建和初始化互斥量
/// \param[in]     attr          互斥量的属性; NULL: 默认值
/// \return 互斥量ID以供其他函数引用，如果出错则返回NULL
osMutexId_t osMutexNew (const osMutexAttr_t *attr);

/// 获取互斥量的所有权
/// \param[in]     mutex_id      由 \ref osMutexNew 获取的互斥量ID
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 表示函数执行状态的状态码
osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);

/// 释放互斥量的所有权
/// \param[in]     mutex_id      由 \ref osMutexNew 获取的互斥量ID
/// \return 表示函数执行状态的状态码
osStatus_t osMutexRelease (osMutexId_t mutex_id);

/// 删除互斥量
/// \param[in]     mutex_id      由 \ref osMutexNew 获取的互斥量ID
/// \return 表示函数执行状态的状态码
osStatus_t osMutexDelete (osMutexId_t mutex_id);


//  ==== Semaphore Management Functions ====

/// 创建和初始化信号量
/// \param[in]     max_count     信号量计数的最大值
/// \param[in]     initial_count 初始信号量计数的值
/// \param[in]     attr          信号量的属性; NULL: 默认值
/// \return 信号量ID以供其他函数引用，如果出错则返回NULL
osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);

/// 获取信号量的所有权
/// \param[in]     semaphore_id  由 \ref osSemaphoreNew 获取的信号量ID
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 表示函数执行状态的状态码
osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);

/// 释放信号量的所有权
/// \param[in]     semaphore_id  由 \ref osSemaphoreNew 获取的信号量ID
/// \return 表示函数执行状态的状态码
osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);

/// 获取信号量的计数
/// \param[in]     semaphore_id  由 \ref osSemaphoreNew 获取的信号量ID
/// \return 信号量的当前计数值，如果出错则返回0xFFFFFFFF
uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);

/// 删除信号量
/// \param[in]     semaphore_id  由 \ref osSemaphoreNew 获取的信号量ID
/// \return 表示函数执行状态的状态码
osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);


//  ==== Memory Pool Management Functions ====

/// 创建和初始化内存池
/// \param[in]     block_count   内存块数量
/// \param[in]     block_size    内存块大小（以字节为单位）
/// \param[in]     attr          内存池的属性; NULL: 默认值
/// \return 内存池ID以供其他函数引用，如果出错则返回NULL
osMemoryPoolId_t osMemoryPoolNew (uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr);

/// 分配内存块
/// \param[in]     mp_id         由 \ref osMemoryPoolNew 获取的内存池ID
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 分配的内存块的指针，如果出错则返回NULL
void *osMemoryPoolAlloc (osMemoryPoolId_t mp_id, uint32_t timeout);

/// 释放内存块
/// \param[in]     mp_id         由 \ref osMemoryPoolNew 获取的内存池ID
/// \param[in]     block         要释放的内存块指针
/// \return 表示函数执行状态的状态码
osStatus_t osMemoryPoolFree (osMemoryPoolId_t mp_id, void *block);

/// 删除内存池
/// \param[in]     mp_id         由 \ref osMemoryPoolNew 获取的内存池ID
/// \return 表示函数执行状态的状态码
osStatus_t osMemoryPoolDelete (osMemoryPoolId_t mp_id);


//  ==== Message Queue Management Functions ====

/// 创建和初始化消息队列
/// \param[in]     msg_count     消息队列中的最大消息数量
/// \param[in]     msg_size      消息队列中的消息大小（以字节为单位）
/// \param[in]     attr          消息队列的属性; NULL: 默认值
/// \return 消息队列ID以供其他函数引用，如果出错则返回NULL
osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);

/// 发送消息到消息队列
/// \param[in]     mq_id         由 \ref osMessageQueueNew 获取的消息队列ID
/// \param[in]     msg_ptr       指向要发送的消息的指针
/// \param[in]     msg_prio      消息的优先级（0:最低..(osMessageQueueGetCapacity-1):最高）
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 表示函数执行状态的状态码
osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);

/// 从消息队列接收消息
/// \param[in]     mq_id         由 \ref osMessageQueueNew 获取的消息队列ID
/// \param[out]    msg_ptr       指向接收到的消息的缓冲区的指针
/// \param[out]    msg_prio      指向接收到的消息的缓冲区的优先级的指针
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue 或0表示无超时
/// \return 表示函数执行状态的状态码
osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);

/// 获取消息队列的消息数量
/// \param[in]     mq_id         由 \ref osMessageQueueNew 获取的消息队列ID
/// \return 消息队列的当前消息计数，如果出错则返回0xFFFFFFFF
uint32_t osMessageQueueGetCount (osMessageQueueId_t mq_id);

/// 获取消息队列的空闲消息数量
/// \param[in]     mq_id         由 \ref osMessageQueueNew 获取的消息队列ID
/// \return 消息队列的可用空间（以消息单位），如果出错则返回0xFFFFFFFF
uint32_t osMessageQueueGetSpace (osMessageQueueId_t mq_id);

/// 删除消息队列
/// \param[in]     mq_id         由 \ref osMessageQueueNew 获取的消息队列ID
/// \return 表示函数执行状态的状态码
osStatus_t osMessageQueueDelete (osMessageQueueId_t mq_id);

```

