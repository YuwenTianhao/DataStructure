/**
  ******************************************************************************
  * @file           : Stack.h
  * @author         : YuwenTianhao
  * @brief          : 栈的学习，主要通过逆波兰表达式的转化和计算，例题在"Homework1"-"example1c.c"
  * @attention      : None
  * @date           : 2023/3/15
  ******************************************************************************
  */

#ifndef HOMEWORK2_STACK_H
#define HOMEWORK2_STACK_H

struct StackRecord;
typedef struct StackRecord *Stack;

Stack CreateStack(int MaxElements);
void Push(int X,Stack S);
int TopAndPop(Stack S);

#endif //HOMEWORK2_STACK_H
