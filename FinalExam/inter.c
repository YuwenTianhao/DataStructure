/**
  ******************************************************************************
  * @file           : inter.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/16
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "inter.h"

int total_var_num = 0;

float evaluate_postfix(char postfix_expr[], List L);

void InfixToPost(int STACK_MAX_Element, char infix_exp[], char post_exp[]);

int main()
{
    List var_list = MakeNewList();
    char buff[200] = "";
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    while (1)
    {
        char tem[10] = "";
        fgets(buff, 200, stdin);
        sscanf(buff, "%s", tem);
        if (strcmp(buff, "exit") == 0)// check
            break;
        else
        {

            if (strcmp(tem, "print") == 0)
            {
                for (int i = 6; buff[i] != '\r' && buff[i] != '\n'; i++)
                {
                    if(buff[i]!=' ')
                    {
                        Position Tmp = Find(buff[i], var_list);
                        if (Tmp != NULL)
                            printf("%.3f ", Tmp->variable.value);
                    }
                }
                printf("\n");
            }
            else
            {
                Position new_Node = MakeNewNode();
                new_Node->variable.name = buff[0];
                char post_exp[200] = "";
                InfixToPost(256, &buff[2], post_exp);
                new_Node->variable.value = evaluate_postfix(post_exp, var_list);
                tailInsert(new_Node,var_list);
            }
        }
        memset(tem, 0, 10 * sizeof(char));
        memset(buff, 0, 200 * sizeof(char));
    }
    return 0;
}

/**
 * @brief 中缀转后缀表达式
 * @note 为了不同的模块的通用性，该函数无需其他数据结构和头文件，将中缀表达式（字符串,带有括号）转到后缀表达式（字符串，带有括号），且支持括号。
 * @param infix_exp[]: 中缀表达式
 * @param post_exp[]:后缀表达式
 * @param STACK_MAX_Element : 最大符号栈长度，一般取256即可
 * @return None
 */
void InfixToPost(int STACK_MAX_Element, char infix_exp[], char post_exp[])
{
    char exp_stack[STACK_MAX_Element];
    int TopOfStack = -1;
    int post_length = 0; // 后缀表达式长度
    // 从左至右遍历中缀表达式中每个数字和符号
    for (int i = 0; infix_exp[i] != '\r' && infix_exp[i] != '\n'; i++)
    {
        // 若是数字直接输出，即成为后缀表达式的一部分；
        if (isdigit(infix_exp[i]) || isalpha(infix_exp[i]))
        {
            while (isdigit(infix_exp[i])|| isalpha(infix_exp[i]))
                post_exp[post_length++] = infix_exp[i++];
            i--;
            post_exp[post_length++] = ' ';
            continue;
        }
        // 若是符号：
        switch (infix_exp[i])
        {
            // 若是(，+，*等符号，则从栈中弹出并输出优先级高于等于当前的符号，直到遇到一个优先级低的符号或左括号；然后将当前符号压入栈中。
            // （优先级+，-最低，*，/次之，“(”最高，也即：若是左括号直接入栈）

            // 思路：需要判断的就是 + - * / (
            // 对于 + - ： + - * / 需要出栈，( 不需要
            // 对于 * / ： * / 需要出栈， + - ( 不需要
            // 对于（ ：没有需要出栈的，直接入栈

            // 根据以上规则
            // （所有符号优先级都比加减更高）除非遇到左括号或空栈，否则一直出栈
            case '+':
            {
                while (exp_stack[TopOfStack] != '(' && TopOfStack != -1)
                {
                    post_exp[post_length++] = exp_stack[TopOfStack--];
                    post_exp[post_length++] = ' ';
                }
                exp_stack[++TopOfStack] = '+';

            }
                break;
            case '-':
            {
                while (exp_stack[TopOfStack] != '(' && TopOfStack != -1)
                {
                    post_exp[post_length++] = exp_stack[TopOfStack--];
                    post_exp[post_length++] = ' ';
                }
                exp_stack[++TopOfStack] = '-';
            }
                break;
                // （没有比乘除优先级更高的符号，因为括号已经计算在内）
            case '*':
            {
                while (exp_stack[TopOfStack] == '*' || exp_stack[TopOfStack] == '/')
                {
                    post_exp[post_length++] = exp_stack[TopOfStack--];
                    post_exp[post_length++] = ' ';
                }
                exp_stack[++TopOfStack] = '*';
            }
                break;
            case '/':
            {
                while (exp_stack[TopOfStack] == '*' || exp_stack[TopOfStack] == '/')
                {
                    post_exp[post_length++] = exp_stack[TopOfStack--];
                    post_exp[post_length++] = ' ';
                }
                exp_stack[++TopOfStack] = '/';
            }
                break;
            case '(':
            {
                exp_stack[++TopOfStack] = '(';
            }
                break;
                // 若是)，则将栈中元素弹出并输出，直到遇到“(”， “(”弹出但不输出；
            case ')':
            {
                while (exp_stack[TopOfStack] != '(')
                {
                    post_exp[post_length++] = exp_stack[TopOfStack--];
                    post_exp[post_length++] = ' ';
                }
                exp_stack[TopOfStack--];
            }
                break;
            default:
                break;
        }
    }
    while (TopOfStack != -1)
    {
        post_exp[post_length++] = exp_stack[TopOfStack--];
        post_exp[post_length++] = ' ';
    }
}

/**
 * @brief 计算后缀表达式的值
 * @note 为了不同的模块的通用性，该函数无需其他数据结构和头文件，后缀表达式数字、符号之间需要有空格间隔
 * @param postfix_expr[]
 * @return result
 * @retval 后缀表达式的值
 */
float evaluate_postfix(char postfix_expr[], List L)
{
    float num_stack[50] = {};
    int top = -1; // init stack
    char tmp[50] = ""; // tmp for element in postfix_expr
    char *ptrTopost = postfix_expr;
    while (1)
    {
        sscanf(ptrTopost, "%s", tmp); // sscanf 每次都会重新从头读，必须用一个指针使其增加固定读过的数
        if (ptrTopost == NULL || *ptrTopost == '\0')
            break;
        if (isdigit(*tmp))
            num_stack[++top] = atoi(tmp);
        else if (isalpha(*tmp))
        {
            Position now_var = Find(*tmp, L);
            if (now_var != NULL)
                num_stack[++top] = now_var->variable.value;
        }
        else if ((*tmp) == '+' || (*tmp) == '-' || (*tmp) == '*' || (*tmp) == '/')
        {
            if (top > 0) // 避免空栈
            {
                float b = num_stack[top--];
                float a = num_stack[top--];
                switch (*tmp)
                {
                    case '+':
                        num_stack[++top] = a + b;
                        break;
                    case '-':
                        num_stack[++top] = a - b;
                        break;
                    case '*':
                        num_stack[++top] = a * b;
                        break;
                    case '/':
                        num_stack[++top] = a / b;
                        break;
                    default:
                        break;
                }
            }
        }
        ptrTopost += strlen(tmp) + 1;
        memset(tmp,0,50);
    }
    return num_stack[0];
}