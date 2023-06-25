/**
  ******************************************************************************
  * @file           : Stack.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/6
  ******************************************************************************
  */

#ifndef HOMEWORK4_STACK_H
#define HOMEWORK4_STACK_H

#define ElementType int

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};
/**
* @brief 指向栈的指针
*/
typedef struct StackRecord *Stack;

Stack CreateStack(ElementType MaxElements);
void Push(ElementType X,Stack S);
int TopAndPop(Stack S);
int Top(Stack S);

#endif //HOMEWORK4_STACK_H
