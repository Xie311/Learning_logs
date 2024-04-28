# FreeRTOS听课笔记

## 0.0 OS与RTOS

### （1）操作系统（Operating System，`OS`）

协作计算机的各种硬件，以与用户进行交互的程序。       

操作系统一个非常重要的特点：**并发性**。也就是单个CPU运行多个线程的方法。
当有多个线程在操作时，如果系统只有一个CPU，则它根本不可能真正同时进行一个以上的线程，它只能把CPU运行时间划分成若干个时间段，再将时间段分配给各个线程执行，**在一个时间段的线程代码运行时，其它线程处于挂起状**。这种方式我们称之为并发。

### （2）实时操作系统（Real Time Operating System，`RTOS`）

当外界事件或数据产生时，能够接受并以足够快的速度予以处理，其处理的结果又能在规定的时间之内来控制生产过程或对处理系统做出快速响应，调度一切可利用的资源完成实时任务，并控制所有实时任务协调一致运行的操作系统。提供及时响应和高可靠性是其主要特点。

- `RTOS`具有OS的特点，是OS的一个子集。
- `FreeRTOS`是一个免费开源的嵌入式实时操作系统
- `FreeRTOS`可以在`CubeMX`中直接生成

## 0.1 FreeRTOS 介绍

![image-20240408170642340](FreeRTOS_assets\image-20240408170642340.png)

## 一、FreeRTOS重要概念

### 1.==任务（Task）、线程（Thread）==

在多任务系统中，根据功能的不同，把整个系统分割成一个个独立的且无法返回的函数，这个函数我们称为任务。系统中的每一任务都有多种运行状态。系统初始化完成后，创建的任务就可以在系统中竞争一定的资源，由内核进行调度。

### 2.事件（`Event`）

事件是一种实现任务之间通信的机制，主要用于实现多任务之间的同步
但事件通信只能是事件类型的通信无数据传输。可以实现一对多、多对多的同步
一个任务可以等待多个事件发生，可以是任何一个事件发生时唤醒任务进行事件处理，也可以是几个事件都发生后才唤醒任务进行事件处理

### 3.软件定时器（`Timer`）

软件定时器不需要额外使用硬件定时器，而且可以创建很多个。使用软件定时器时，我们是在创建软件定时器时指定软件定时器的回调函数，在回调函数中实现相应的功能。

### 4.==互斥锁==（`Mutex`）

互斥锁是一种同步机制，用于控制多个任务对共享资源的访问，以确保只有一个任务可以访问该资源，从而避免竞争条件和数据损坏。
> **互斥锁**：有数据不可被同时访问
>
> 例：任务一读取距离，任务二读取传感器的值修改距离
>
> 故引入互斥锁。当修改/读取距离时，获得互斥锁权限。将距离这个变量锁住。修改/读取后再将互斥锁释放掉。保护距离不被错误的读取/写入。

**跨线程读取/写入变量等 加互斥锁更安全**

> 中断保护：临界区


### 5.==信号量==（`Semaphores`）

信号量是操作系统中重要的一部分，信号量一般用来进行资源管理和任务同步，`FreeRTOS` 中信号量又分为二值信号量、计数型信号量、互斥信号量和递归互斥信号量。

### 6.队列（`Queue`）

可以在任务与任务、任务与中断之间传递消息，队列中可以存储有限的、大小固定的数据项目。任务与任务、任务与中断之间要交流的数据保存在队列中，叫做队列项目。队列所能保存的最大数据项目数量叫做队列的长度，创建队列的时候会指定数据项目的大小和队列的长度。由于队列用来传递消息的，所以也称为消息队列。

## 二、FreeRTOS-API查找

### 方法一、官网

`FreeRTOS`原生`API`可以从`FreeRTOS`官网中找到：`www.freertos.org`

`CMSIS-RTOSv2`的`API`可以从ARM官方文档中找到。

### 方法二、库文件中查找

使用Cube生成`FreeRTOS`项目后，可以从生成好的库文件中找到相关`API`的函数原型及其用法解释

`CMSIS-RTOSv2`的`API`可以从`Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2\cmsis_os2.h：283-end`行
中查找，`API`有详细注释，例如

![image-20240408171711351](FreeRTOS_assets\image-20240408171711351.png)

> `FreeRTOS`原生`API`可以从
> `Middlewares\Third_Party\FreeRTOS\Source\include`
> 下查找，但是很乱，不如官网

## 二、状态机

![image-20240408171824653](D:\Study_log\FreeRTOS_Note\FreeRTOS_assets\image-20240408171824653.png)

## 三、在`CubeMX`中生成`FreeRTOS`

> 以`STM32F427IIh6`进行示例

---

**使用FreeRTOS，在所有的线程中不能使用HAL_Delay（）**

> vTaskDelayUntil 等待 5个tick
>
> osDeakyUntil 等待 5ms

### 0.前期配置同普通工程

### 1.打开`Middleware ad Software Packs`

(1）选择`FREERTOS`

(2) 选择`CMAIM_V2`

### 2.更改时钟设置

`FREERTOS`默认占用`SysTick` 时钟，为避免发生冲突，修改系统时钟源

`sys`->`Timebase Source`  这里换成`TIM1`

### （相关配置）

`Mutexes`   互斥锁

`Tasks and Quenes`   任务 ，默认有一个`dafaultTask`

`Timers andSemaphores`   信号量

`Include parameters`  是否使能一些原生`API`

`Config parameters`   一些`API`设置

### 3.生成一个Task

点击Add即可。

将不希望被打断的任务优先级设置高

> 一般设置Normal

`Stack Size` ：为任务分配的空间  可以保持默认

`Entry Function` : 任务调用的函数

![image-20240408192012674](FreeRTOS_assets\image-20240408192012674.png)

> 可以在Code Generation Option 选择  As weak
>
> 在UserCode下再复写函数

### 4.Generate Code！
