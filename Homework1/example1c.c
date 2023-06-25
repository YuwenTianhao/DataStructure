/**
  ******************************************************************************
  * @file           : example1c.c
  * @author         : YuwenTianhao
  * @brief          : ”2. 表达式计算（支持空格，连乘，连除）“
  * @attention      : 1、将中缀表达式变为后缀表达式（字符类型的栈实现）
  *                   2、将后缀表达式进行计算（int数组作为栈）
  *                   PS 函数逻辑较为复杂，还是建议参考更好的写法
  * @date           : 2023/3/15
  ******************************************************************************
  */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define MAX_LEN_EXPR 100

/**
* @brief 栈的结构体（字符类型）
*/
struct StackRecord
{
    int Capacity;
    int TopOfStack;
    char *Array;
};
typedef struct StackRecord *Stack;

// 字符操作函数：底层
int transform_ch2int(char *str);

int is_operator(char c);

int operator_precedence(char op);

// 栈的操作函数：底层
Stack CreateStack(int MaxElements);

void Push(char X, Stack S);

char TopAndPop(Stack S);

char TopPeek(Stack S);

// 主程序函数：上层
void infix_to_postfix(char *infix_expr, char *postfix_expr);

int evaluate_postfix(char *postfix_expr);


int main()
{
    char infix_expr[MAX_LEN_EXPR] = "";
    char post_expr[MAX_LEN_EXPR] = "";
    int result;
    scanf("%[^\n]", infix_expr);
    getchar();
    infix_to_postfix(infix_expr, post_expr);
    result = evaluate_postfix(post_expr);
    printf("%d", result);
}

/**
 * @brief 将字符串转化为10进制整数
 * @note 不需要头文件, 输入的字符串除了数字不能有别的， 对字符串的判断停止在'\0'
 * @param *str
 * @return 一个整数
 * @retval 转化后的值
 */
int transform_ch2int(char *str)
{
    char *strlen_p = str;
    int str_len = 0;
    int result = 0;
    while (*strlen_p != '\0')
    {
        str_len++;
        strlen_p++;
    }
    while (str_len > 0)
    {
        int tem_result = *str - '0';
        for (int ch2int_i = 0; ch2int_i < str_len - 1; ch2int_i++)
        {
            tem_result *= 10;
        }
        result += tem_result;
        str_len--;
        str++;
    }
    return result;
}

int operation(int a, int b, char symbol)
{
    switch (symbol)
    {
        case '+':
        {
            return a + b;
        }
        case '-':
        {
            return a - b;
        }
        case '*':
        {
            return a * b;
        }
        case '/':
        {
            return a / b;
        }
        default:
            break;
    }
    return 0;
}

int is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}

int operator_precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '=':
            return 0;
        default:
            printf("Invalid operator\n");
            exit(1);
    }
}

Stack CreateStack(int MaxElements)
{
    Stack S;
    S = malloc(sizeof(struct StackRecord));
//    if(S == NULL)
//    {
//        printf("Out of space!");
//        return NULL;
//    }
    S->Array = malloc(sizeof(char) * MaxElements);
//    if( S->Array == NULL )
//    {
//        printf("Out of space!");
//        return NULL;
//    }
    S->Capacity = MaxElements;
    S->TopOfStack = -1; // Empty Stack
    return S;
}

void Push(char X, Stack S)
{
//    if(S->TopOfStack == S->Capacity - 1)
//    {
//        printf("Out of space!");
//        return;
//    }
    S->Array[++S->TopOfStack] = X;
}

char TopAndPop(Stack S)
{
//    if(S->TopOfStack == -1)
//    {
//        printf("Out of space!");
//        return 0;
//    }
    return S->Array[S->TopOfStack--];
}

char TopPeek(Stack S)
{

    return S->Array[S->TopOfStack];
}

/**
 * @brief 中缀表达式转后缀表达式
 * @note 参考 ”https://www.cnblogs.com/lanhaicode/p/10776166.html“，输出为元素间有空格的后缀表达式
 * @param char *infix_expr ： 中缀表达式
 * @param char *postfix_expr ： 后缀表达式
 * @return None
 * @retval None
 */
void infix_to_postfix(char *infix_expr, char *postfix_expr)
{
    Stack operator_stack;
    operator_stack = CreateStack(50);
    int i, j;
    char c;
    for (i = 0, j = 0; infix_expr[i] != '\0'; i++)
    {
        c = infix_expr[i];
        if (isdigit(c)) // 若数字则直接加入输出
        {
            postfix_expr[j++] = c;
            while (isdigit(infix_expr[i + 1]))
            {
                postfix_expr[j++] = infix_expr[++i];
            }
            postfix_expr[j++] = ' ';
        }
        else if (is_operator(c)) // 若字符：if(检查栈是否为空 && 符号优先级比较) { 出栈，留空; } 入栈;
        {
            while (operator_stack->TopOfStack >= 0 &&
                   operator_precedence(c) <= operator_precedence(TopPeek(operator_stack)))
            {
                postfix_expr[j++] = TopAndPop(operator_stack);
                postfix_expr[j++] = ' ';
            }
            Push(c, operator_stack);
        }
    }

    while (operator_stack->TopOfStack >= 0)
    {
        if (TopPeek(operator_stack) == '=')
        {
            TopAndPop(operator_stack);
        }
        else
        {
            postfix_expr[j++] = TopAndPop(operator_stack);
            postfix_expr[j++] = ' ';
        }
    }
    postfix_expr[j] = '\0';
}

/**
 * @brief 计算后缀表达式的值
 * @note 后缀表达式元素之间需要有空格间隔
 * @param char *postfix_expr
 * @return int
 * @retval 后缀表达式的值
 */
int evaluate_postfix(char *postfix_expr)
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
            num_stack[++top] = transform_ch2int(tmp);
        }
        else if (is_operator(*tmp))
        {
            if (top > 0) // 错误避免
            {
                int b = num_stack[top--];
                int a = num_stack[top--];
                num_stack[++top] = operation(a, b, *tmp);
            }
        }
        ptrTopost += strlen(tmp) + 1; // 1 for blank
    }
    return num_stack[0];
}