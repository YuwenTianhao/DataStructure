/**
  ******************************************************************************
  * @file           : edit.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/16
  ******************************************************************************
  */

#include "edit.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define MAX_LENGTH 512

char String[MAX_LENGTH];

void PreProcess(Stack StackOfOperation)
{
    while (StackOfOperation->TopOfStack != -1)
    {
        struct Operation Tmp;
        Tmp.op = Top(StackOfOperation).op;
        Tmp.pos = Top(StackOfOperation).pos;
        Tmp.str = Top(StackOfOperation).str;
        TopAndPop(StackOfOperation);
        switch (Tmp.op)
        {
            case INSERT:
                strcat(&String[Tmp.pos],&String[Tmp.pos+ strlen(Tmp.str)]);
                break;
            case DELETE:
                strcat(Tmp.str,&String[Tmp.pos]);
                strncpy(&String[Tmp.pos],Tmp.str,MAX_LENGTH - Tmp.pos);
                break;
            default:
                printf("wrong!\n");
                break;
        }
    }
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    Stack StackOfOperation = CreateStack(512);  // 操作栈，用于存储及操作现在时刻之后的命令
    Stack PreStack = CreateStack(512); // 操作栈，用于存储现在时刻之前的命令
    int n = 0;
    int now_op = 0; // 临时变量，存储现在时刻的命令
    int BackToEarly = 0; // 标志位，若回退到之前版本，则为1；否则为0
    gets(String);
    scanf("%d", &n);
    // 存储之前的命令
    for (int i = 0; i < n; i++)
        scanf("%d%d%s", &StackOfOperation->Array[i].op, &StackOfOperation->Array[i].pos,
              StackOfOperation->Array[i].str);

    PreProcess(StackOfOperation);

    while (1)
    {
        scanf("%d", &now_op);
        if (now_op == EXIT)
            break;
        if (now_op == UNDO)
        {
            // 现在的命令没有回退到之前版本
            if(StackOfOperation->TopOfStack != -1)
                TopAndPop(StackOfOperation);
            else
            {
                // 回退函数
            }
        }
        else
        { // 入栈即可
            int tmp_pos = 0;
            char tmp_str[MAX_LENGTH] = "";
            scanf("%d%s", &tmp_pos, tmp_str);
            struct Operation Tmp = {now_op, tmp_pos, tmp_str};
            Push(Tmp, StackOfOperation);
        }
    }
        return 0;
}


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
    S = malloc(sizeof(struct StackRecord));
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
void Push(ElementType X, Stack S)
{
    if (S->TopOfStack == S->Capacity - 1)
    {
        printf("Out of space!");
        return;
    }
    S->Array[++S->TopOfStack] = X;
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
    if (S->TopOfStack != -1)
        return S->Array[S->TopOfStack--];
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