/**
  ******************************************************************************
  * @file           : ExpressionTree.c
  * @author         : YuwenTianhao
  * @brief          : "3. 计算器（表达式计算-表达式树实现）" - 整数计算
  * @attention      : 中缀后缀及表达式计算是数据结构里关于栈绕不开的命题，然而我查阅，大多的资料并不能成为一个合适的函数来用
  *                   甚至于，我们自己的PPT也有错误，无法完成自然语言直接转为编程语言
  *                   程序流程：从字符串输入需要经过字符串处理，到中缀转后缀（或中缀直接计算），到后缀计算。
  *                   数据结构：字符串（数组），表达式符号栈，数据栈（若合二为一需要使用联合），表达式树的计算
  *                   经过多次写作，对于表达式计算，十分不建议使用 Stack 等固定的数据结构（复用率太低），建议自己写（反正也很简单）
  *                   牢记：只有逻辑本身通顺了，才能调试出正确结果，不可照本宣科，将算法的自然语言翻译成代码即可（一旦出错，自己永远也查不出来，也不会选合适的测试案例）
  *                   有两个函数可以模块化复用，十分有效
  * @date           : 2023/4/28
  ******************************************************************************
  */

#include "ExpressionTree.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_EXPRESSION_LENGTH 256

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
    for (int i = 0; infix_exp[i] != '='; i++)
    {
        // 若是数字直接输出，即成为后缀表达式的一部分；
        if (isdigit(infix_exp[i]))
        {
            while (isdigit(infix_exp[i]))
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
int evaluate_postfix(char postfix_expr[])
{
    int num_stack[50] = {};
    int top = -1; // init stack
    char tmp[50] = ""; // tmp for element in postfix_expr
    char *ptrTopost = postfix_expr;
    while (1)
    {
        sscanf(ptrTopost, "%s", tmp); // sscanf 每次都会重新从头读，必须用一个指针使其增加固定读过的数
        if (ptrTopost == NULL || *ptrTopost == '\0')
            break;
        if (isdigit(*tmp))
        {
            num_stack[++top] = atoi(tmp);
        }
        else if ((*tmp) == '+' || (*tmp) == '-' || (*tmp) == '*' || (*tmp) == '/')
        {
            if (top > 0) // 避免空栈
            {
                int b = num_stack[top--];
                int a = num_stack[top--];
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
        ptrTopost += strlen(tmp) + 1; // 1 because of the blank, but it's OK to not plus 1
    }
    return num_stack[0];
}

/**
 * @brief 生成表达式树
 * @note None
 * @param postfix_expr: 后缀表达式（各项之间带有空格）
 * @param S: 使用的栈，也可经过函数内部修改将栈的生成放在函数体内
 * @return SearchTree
 * @retval 返回的表达式树（与BST同构）
 */
SearchTree GenerateTree(char postfix_expr[], Stack S)
{
    int length = strlen(postfix_expr);
    for (int i = 0; i < length; i++)
    {
        if (postfix_expr[i] == ' ')continue;
        if (isdigit(postfix_expr[i]))
        {
            SearchTree Tmp = malloc(sizeof(struct TreeNode));
            Tmp->category = 0;
            Tmp->Left = NULL;
            Tmp->Right = NULL;
            Tmp->Element.num = atoi(&postfix_expr[i]);
            Push(Tmp, S);
            while (isdigit(postfix_expr[++i]));
            i--;
        }
        else
        {
            SearchTree Tmp = malloc(sizeof(struct TreeNode));
            Tmp->category = 1;
            Tmp->Right = TopAndPop(S);
            Tmp->Left = TopAndPop(S);
            Tmp->Element.op = postfix_expr[i];
            Push(Tmp, S);
        }
    }
    return TopAndPop(S);
}

void PrintNode(SearchTree T)
{
    if (T->category)printf("%c ", T->Element.op);
    else printf("%d ", T->Element.num);
}

int main()
{
    char post_exp[MAX_EXPRESSION_LENGTH] = ""; // 后缀表达式
    char infix_exp[MAX_EXPRESSION_LENGTH] = ""; // 中缀表达式
    int result = 0; // 表达式结果
    SearchTree T = NULL;
    Stack S = CreateStack(256);
    gets(infix_exp);
    InfixToPost(256, infix_exp, post_exp); // 中缀转后缀
    result = evaluate_postfix(post_exp); // 后缀计算
    T = GenerateTree(post_exp, S); // 生成表达式树
    if (T != NULL)
    {
        PrintNode(T);
        if (T->Left != NULL)
            PrintNode(T->Left);
        if (T->Right != NULL)
            PrintNode(T->Right);
    }
    printf("\n%d", result);
    return 0;
}