/**
  ******************************************************************************
  * @file           : edit.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/16
  ******************************************************************************
  */

#ifndef HOMEWORK4_EDIT_H
#define HOMEWORK4_EDIT_H

#define ElementType struct Operation

typedef enum
{
    EXIT = -1, INSERT = 1, DELETE = 2, UNDO = 3
} oper;

struct Operation
{
    oper op; // 只有 INSERT = 1, DELETE = 2 会被保存下来
    int pos;
    char *str;
    int length; // 用于存储”0时刻以后，操作2“的长度
};

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

Stack CreateStack(int MaxElements);

void Push(ElementType X, Stack S);

ElementType TopAndPop(Stack S);

ElementType Top(Stack S);


#endif //HOMEWORK4_EDIT_H
