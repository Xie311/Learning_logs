#ifndef WTR_CAN_H
#define WTR_CAN_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "DJI.h"
#include "can.h"

    HAL_StatusTypeDef CANFilterInit(CAN_HandleTypeDef *hcan);

#ifdef __cplusplus
}
#endif

#endif

/**note
 * 这段代码是一段 C/C++ 混合语言代码，主要用于在 C++ 环境下调用 C 语言编写的函数。确保了在 C++ 环境和非 C++ 环境下的代码都能够正常编译和链接。

#ifdef __cplusplus 和 #endif：这是 C 预处理器的条件编译指令。
__cplusplus 是 C++ 环境下的预定义宏，如果当前编译环境是 C++，则 __cplusplus 会被定义。
因此，这两行代码用于检查当前编译环境是否为 C++ 环境，如果是，则执行 extern "C" 块中的代码，否则跳过。

extern "C" 块：这是 C++ 的语法，用于告诉编译器将其中的 C 语言函数使用 C 的调用约定来进行编译。
因为 C++ 和 C 在函数调用约定上有所不同，C++ 支持函数的重载和命名空间等特性，而 C 则不支持。  //C++ 环境下通常可以编译和运行 C 语言代码。这是因为 C++ 是 C 的超集.
在 C++ 中调用 C 语言编写的函数时，需要使用 extern "C" 来告诉编译器使用 C 的调用约定。       //但有些特定的 C 语言特性可能与 C++ 有所不同，需要进行一些调整。例如，C++ 中的关键字可能与 C 中的关键字略有不同，因此一些 C 代码可能需要稍作修改才能在 C++ 环境中正常工作。
在 C++ 环境中将函数声明为 C 风格的，即使用 extern "C" 块来告诉编译器将其中的函数按照 C 的调用约定进行编译。在这个块中，函数声明被包裹在 extern "C" 块中，以确保在 C++ 中正确调用与链接 C 语言函数。

#include "DJI.h" 和 #include "can.h"：这两行代码用于包含头文件，其中声明了一些函数和变量的原型。

HAL_StatusTypeDef CANFilterInit(CAN_HandleTypeDef *hcan);：这是一个函数声明，声明了一个名为 CANFilterInit 的函数，
该函数接受一个指向 CAN_HandleTypeDef 结构的指针作为参数，并返回一个 HAL_StatusTypeDef 类型的值。
这个函数可能用于初始化 CAN 滤波器，但具体的实现需要查看 can.h 头文件中的定义。


最后的 #endif：这是条件编译指令的结束标记，表示 #ifdef __cplusplus 块的结束。
这个块是对第一个 #ifdef __cplusplus 块的结束标记。在 C++ 环境中，这个块的作用是关闭 extern "C" 块，使得后续的代码（如果有）不再受其影响。

综上所述，这段代码的功能是在 C++ 环境下调用了一个名为 CANFilterInit 的 C 函数，
该函数可能用于初始化 CAN 滤波器。通过 extern "C" 块，告诉编译器将 CANFilterInit 函数按照 C 的调用约定进行编译。
*/
