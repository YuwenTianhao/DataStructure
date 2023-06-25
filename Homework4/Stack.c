/**
  ******************************************************************************
  * @file           : Stack.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/6
  ******************************************************************************
  */
#include "Stack.h"
#include "stdlib.h"
#include "stdio.h"

/**
 * @brief 创建新的栈
 * @note None
 * @param MaxElements 最大元素容量
 * @return new stack
 * @retval 新的栈
 */
Stack CreateStack(int MaxElements)
{
    Stack S;
    S = malloc(sizeof( struct StackRecord ) );
    S->Array = malloc(sizeof(ElementType) * MaxElements);
    S->Capacity = MaxElements;
    S->TopOfStack = -1; // Empty Stack
    return S;
}

/**
 * @brief 入栈
 * @note None
 * @param ElementType X 入栈元素 ,Stack S 栈
 * @return None
 * @retval None
 */
void Push(ElementType X,Stack S)
{
    if(S->TopOfStack == S->Capacity - 1)
    {
        printf("Out of space!");
        return;
    }
    S->Array [ ++S->TopOfStack ] = X;
}

/**
 * @brief 出栈
 * @note None
 * @param Stack S 栈
 * @return ElementaryType
 * @retval 出栈元素的值
 */
ElementType TopAndPop(Stack S)
{
    if(S->TopOfStack == -1)
    {
        printf("Out of space!");
        return 0;
    }
    return S->Array[ S->TopOfStack -- ];
}
/**
 * @brief 栈顶元素
 * @note None
 * @param Stack S 栈
 * @return ElementaryType
 * @retval 栈顶元素的值（不出栈）
 */
ElementType Top(Stack S)
{
    return S->Array[S->TopOfStack];
}