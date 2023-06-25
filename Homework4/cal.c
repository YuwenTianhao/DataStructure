/**
  ******************************************************************************
  * @file           : cal.c
  * @author         : YuwenTianhao
  * @brief          : “3. 计算器（表达式计算-后缀表达式实现，结果为浮点）”
  * @attention      : None
  * @date           : 2023/4/11
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "cal.h"

#define CAPACITY 256
#define MAX_LEN_EXPR 256

/**
 * @brief 计算函数（底层，被调用）
 * @note 注意 A 和 B 的顺序（减法和除法），在函数参数里，默认先 Pop B参数，再 Pop 出A参数
 * @param union sym A：, union sym B, enum oper C, Stack number_stack
 * @return None
 */
void computeFuction(union sym A, union sym B, enum oper C, Stack number_stack)
{
    union sym tem;
    tem.num = 0;
    switch (C)
    {
        case ADD:
            tem.num = A.num + B.num;
            break;
        case MIN:
            tem.num = A.num - B.num;
            break;
        case MUL:
            tem.num = A.num * B.num;
            break;
        case DIV:
            tem.num = A.num / B.num;
            break;
    }
    Push(tem, number_stack);
}

/**
 * @brief 中缀表达式的直接计算
 * @note 直接读取中缀表达式，并存于两个不同的数据栈、符号栈当中（共享栈的操作函数）
 * @param char *infix_expr：中缀表达式
 * @return None
 * @retval None
 */
void infix_compute(char *infix_expr)
{
    Stack operator_stack; // 运算符栈
    Stack number_stack; // 数据栈
    operator_stack = CreateStack(CAPACITY);
    number_stack = CreateStack(CAPACITY);
    for (int i = 0; infix_expr[i] != '\0'; i++)
    {
        // 对数字的处理
        if (isdigit(infix_expr[i]))
        {
            union sym tem;
            tem.num = atoi(&infix_expr[i]); // 调用 atio() ，字符串转int（如果需要在输入时就直接调用浮点，使用atof()）
            Push(tem, number_stack); // 入栈
            while (isdigit(infix_expr[++i])); // 跳过已经被读入的字符
            if (!isdigit(infix_expr[i])) i--; // 如果执行了while，势必多输入一位，需要退回
            continue;
        }
        else if (infix_expr[i] == ' ' || infix_expr[i] == '+' || infix_expr[i] == '-' || infix_expr[i] == '*' ||
                 infix_expr[i] == '/' || infix_expr[i] == '(' || infix_expr[i] == ')')
        {
            switch (infix_expr[i])
            {
                case ' ':
                    break;
                case '+': // 以加法为例
                {
                    while (operator_stack->TopOfStack > -1 &&
                           priority[ADD] <= priority[Top(operator_stack).op]) // 注意条件：非空栈 && 栈的最顶层优先级“大于等于”目前入栈项
                    {
                        if (Top(operator_stack).op == LEFT) // 左括号的话直接入栈不管
                            break;
                        computeFuction(TopAndPop(number_stack), TopAndPop(number_stack), TopAndPop(operator_stack).op,
                                       number_stack); // 否则符号出栈计算，注意computeFunction的先后顺序
                    }
                    union sym tem;
                    tem.op = ADD;
                    Push(tem, operator_stack); // 入栈，使用联合表示一个栈的缺点就是入栈需要定义一个新的联合来表示，写起来很啰嗦
                }
                    break;
                case '-':
                {
                    while (operator_stack->TopOfStack > -1 &&
                           priority[MIN] <= priority[Top(operator_stack).op])
                    {
                        if (Top(operator_stack).op == LEFT)
                            break;
                        computeFuction(TopAndPop(number_stack), TopAndPop(number_stack), TopAndPop(operator_stack).op,
                                       number_stack);
                    }
                    union sym tem;
                    tem.op = MIN;
                    Push(tem, operator_stack);
                }
                    break;
                case '*':
                {
                    while (operator_stack->TopOfStack > -1 &&
                           priority[MUL] <= priority[Top(operator_stack).op])
                    {
                        if (Top(operator_stack).op == LEFT)
                            break;
                        computeFuction(TopAndPop(number_stack), TopAndPop(number_stack), TopAndPop(operator_stack).op,
                                       number_stack);
                    }
                    union sym tem;
                    tem.op = MUL;
                    Push(tem, operator_stack);
                }
                    break;
                case '/':
                {
                    while (operator_stack->TopOfStack > -1 &&
                           priority[DIV] <= priority[Top(operator_stack).op])
                    {
                        if (Top(operator_stack).op == LEFT)
                            break;
                        computeFuction(TopAndPop(number_stack), TopAndPop(number_stack), TopAndPop(operator_stack).op,
                                       number_stack);
                    }
                    union sym tem;
                    tem.op = DIV;
                    Push(tem, operator_stack);
                }
                    break;
                case '(':
                {
                    union sym tem;
                    tem.op = LEFT;
                    Push(tem, operator_stack);
                }
                    break;
                case ')':
                {
                    while (Top(operator_stack).op != LEFT)
                    {
                        computeFuction(TopAndPop(number_stack), TopAndPop(number_stack), TopAndPop(operator_stack).op,
                                       number_stack);
                    }
                    TopAndPop(operator_stack);
                }
                    break;
            }
        }
        else if (infix_expr[i] == '=') // 是根据条件 “=” 来判断是否该计算的，如果等式本身没有等号则需要修改该条件
        {
            while (operator_stack->TopOfStack >= 0) // 符号栈还没空就全部出栈计算
            {
                computeFuction(TopAndPop(number_stack), TopAndPop(number_stack), TopAndPop(operator_stack).op,
                               number_stack);
            }
        }
    }
    printf("%.2lf", number_stack->Array[number_stack->TopOfStack].num);
}

int main()
{
    char infix[MAX_LEN_EXPR];
    gets(infix);
    infix_compute(infix);
    return 0;
}

Stack CreateStack(int MaxElements)
{
    Stack S;
    S = malloc(sizeof(struct StackRecord));
    S->Array = malloc(sizeof(ElementType) * MaxElements);
    S->Capacity = MaxElements;
    S->TopOfStack = -1; // Empty Stack
    return S;
}

void Push(ElementType X, Stack S)
{
    if (S->TopOfStack == S->Capacity - 1)
    {
        printf("Out of space!");
        return;
    }
    S->Array[++S->TopOfStack] = X;
}

ElementType TopAndPop(Stack S)
{
    return S->Array[S->TopOfStack--];
}

ElementType Top(Stack S)
{
    return S->Array[S->TopOfStack];
}