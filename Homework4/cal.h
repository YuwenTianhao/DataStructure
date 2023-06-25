/**
  ******************************************************************************
  * @file           : cal.h
  * @author         : YuwenTianhao
  * @brief          : “3. 计算器（表达式计算-后缀表达式实现，结果为浮点）”
  * @attention      : None
  * @date           : 2023/4/11
  ******************************************************************************
  */

#ifndef HOMEWORK4_CAL_H
#define HOMEWORK4_CAL_H

#define ElementType union sym
// 计算符号的枚举
enum oper
{
    EPT, ADD, MIN, MUL, DIV, LEFT, RIGHT
};
// 符号优先级排序：使用方式 priority[enum oper]
int priority[] = {-1, 0, 0, 1, 1, 2, 2};
/**
* @brief 数据栈和符号栈的联合：{double num; enum oper op;}
*/
union sym
{
    double num;
    enum oper op;
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

#endif //HOMEWORK4_CAL_H
