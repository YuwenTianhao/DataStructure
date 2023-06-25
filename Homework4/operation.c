/**
  ******************************************************************************
  * @file           : operation.c
  * @author         : YuwenTianhao
  * @brief          : "1. 栈操作（栈-基本题）"
  * @attention      : None
  * @date           : 2023/4/11
  ******************************************************************************
  */
#include "stdio.h"
#include "Stack.h"

#define MAX_CAPACITY 100

void pop(Stack S)
{
    if(S->TopOfStack == -1)
    {
    printf("error ");
    return;
    }
    printf("%d ",S->Array[ S->TopOfStack -- ]);
}

void push(ElementType X,Stack S)
{
    if(S->TopOfStack == S->Capacity - 1)
    {
        printf("error ");
        return;
    }
    S->Array [ ++S->TopOfStack ] = X;
}

int main()
{
    int op,num;
    Stack S = CreateStack(100);
    while (1)
    {
        scanf("%d",&op);
        switch (op)
        {
            case -1: return 0;
            case 0:
                pop(S);
                break;
            case 1:
            {
                scanf("%d",&num);
                push(num,S);
            }
        }
    }
}