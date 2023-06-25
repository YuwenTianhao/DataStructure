/**
  ******************************************************************************
  * @file           : Stack.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/3/15
  ******************************************************************************
  */

// 栈 Stack
// 栈ADT
// 栈是一种表，它限制插入和删除只能在一个位置进行，该位置是表的末端，叫做栈的顶（Top）
// 基本对栈的操作有：Push, Pop 也几乎是全部操作了
// 栈顶的元素是唯一的可见元素

// 虽然同样是表，由于严格限制了栈的操作，因此，用数组的实现可能会更加简易、并且避免指针。
// 但用数组的最大危害是：需要声明数组的大小，并且带来了数组越界的风险。

// 用数组实现栈 （本质是结构体）
// 对于TopOfStack， 初始化为 -1
// Push ： Stack[ TopOfStack ] = X; TopOfStack ++；
// Pop ： 返回值为 Stack[ TopOfStack ] ，然后 TopOfStack --;
// 尽量不要使用全局变量和固定名字来表示一个栈，因为栈一般不会只有一个

// 栈的优点
// 1、构造极其简单，是仅次于数组利用最多的数据结构，也是最成功的之一
// 2、栈的所有操作都是以常数时间运行，因此极快，尤其是有些寄存器还有自增、自减寻址功能，可以真正将栈的指令变成一次可执行的机器指令
// 3、栈能与硬件对应起来

// 栈的缺点
// 1、栈需要错误检测吗？ 栈的错误检测极其耗费时间（相比于执行他的指令），如果用链表描述栈则不太容易出现问题，但是数组会
// 2、由于数组最常用，错误检测除非在重要场合，否则不检测。也因此，堆爆栈是常有的事情
// 书本上强烈建议加入错误检测

#include "Stack.h"
#include "stdio.h"
#include "stdlib.h"

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    int *Array;
};

Stack CreateStack(int MaxElements)
{
    Stack S;
    S = malloc(sizeof( struct StackRecord ) );
//    if(S == NULL)
//    {
//        printf("Out of space!");
//        return NULL;
//    }
    S->Array = malloc(sizeof(int) * MaxElements);
//    if( S->Array == NULL )
//    {
//        printf("Out of space!");
//        return NULL;
//    }
    S->Capacity = MaxElements;
    S->TopOfStack = -1; // Empty Stack
    return S;
}

void Push(int X,Stack S)
{
//    if(S->TopOfStack == S->Capacity - 1)
//    {
//        printf("Out of space!");
//        return;
//    }
    S->Array [ ++S->TopOfStack ] = X;
}

int TopAndPop(Stack S)
{
//    if(S->TopOfStack == -1)
//    {
//        printf("Out of space!");
//        return 0;
//    }
    return S->Array[ S->TopOfStack -- ];
}