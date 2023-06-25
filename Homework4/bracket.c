/**
  ******************************************************************************
  * @file           : bracket.c
  * @author         : YuwenTianhao
  * @brief          : “2. C程序括号匹配检查”
  * @attention      : 重中之重在于读题：当检测的程序括号为'{'时，若其前序尚未匹配的括号为'('时，输出该'('左括号及所在行号；
  * @date           : 2023/4/11
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include "bracket.h"

#define LEN_MAX 256
#define MAX_CAPACITY 256

char output[MAX_CAPACITY]; // 输出括号匹配情况

/**
 * @brief 字符处理函数
 * @note None
 * @param char ch : 处理字符
 * @param int line ： 所在行号
 * @param Stack Bracket ： 括号栈
 * @return 处理是否出错
 * @retval 0:没有出错
 * @retval 1：出现不匹配判断
 */
int Dealing(char ch, int line, Stack Bracket)
{
    if (ch == '{' || ch == '(' || ch == '}' || ch == ')')
    {
        char tmp_str[LEN_MAX]; // 以字符串存储，方便使用 strcat()
        struct Element tmp; // 临时结构体，用于Push进栈中
        memset(tmp_str, 0, sizeof(0));
        tmp.bracket = ch;
        tmp.line = line;
        tmp_str[0] = ch;
        tmp_str[1] = '\0';
        strcat(output, tmp_str); // 括号输出到string
        // 以下为判断条件
        // 若 空栈 或 左小括号，直接入栈
        if (Bracket->TopOfStack == -1 || ch == '(')
            Push(tmp, Bracket);
        else if (ch == '{') // 若为左侧大括号，进行判断栈顶是否为小括号
        {
            if (Top(Bracket).bracket == '(')
            {
                // 判断为小括号后报错并输出
                printf("without maching \'(\' at line %d\n", TopAndPop(Bracket).line);
                return 1;
            }
            else Push(tmp, Bracket);
        }
            // 若为两个右括号，进行括号匹配，不匹配左侧括号即输出
        else if (ch == ')')
        {
            if (Top(Bracket).bracket == '(')
                TopAndPop(Bracket);
            else
            {
                printf("without maching \')\' at line %d\n", line);
                return 1;
            }
        }
        else
        {
            if (Top(Bracket).bracket == '{')
                TopAndPop(Bracket);
            else
            {
                printf("without maching \'}\' at line %d\n", line);
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    Stack Bracket = CreateStack(MAX_CAPACITY); // 括号栈
    int line = 0; // 行号
    int MultiLinesComments = 0; // 多行注释标志位
    FILE *IN;
    char buf[LEN_MAX]; // 文件按行输入，行存储器
    IN = fopen("example.c", "r");
    memset(buf, 0, sizeof(buf));
    while (fgets(buf, LEN_MAX, IN) != NULL) // 按行读入
    {
        char ch;
        char *now = buf; // 每次增 1 位
        int ConstChar = 0; // 字符常量标志位，按照要求：0:不处于字符串/字符常量中 1:处于字符串常量中 2:处于字符常量中
        line++;
        while (1) // 按字符分析，按判断优先等级：多行注释 > 单行注释 > 字符（串）常量 > 字符判断（检查括号）
        {
            if (*now == '\0')break;
            sscanf(now++, "%c", &ch);
            // 不是多行注释才能进入判断
            if (!MultiLinesComments)
            {
                // 若是注释
                if (ch == '/')
                {
                    sscanf(now++, "%c", &ch);
                    if (ch == '*') // 多行注释
                    {
                        MultiLinesComments = 1;
                        continue;
                    }
                    else // 单行注释
                        break;
                }
                // 不是注释
                // 不在字符常量中
                if (!ConstChar)
                {
                    if (ch == '\"')
                        ConstChar = 1;
                    else if (ch == '\'')
                        ConstChar = 2;
                    else if (Dealing(ch, line, Bracket))
                        return 0; // 字符判断
                }
                    // 在字符串常量中
                else if (ConstChar == 1)
                {
                    if (ch == '\"')
                        ConstChar = 0;
                }
                else // 在字符常量中
                {
                    if (ch == '\'')
                        ConstChar = 0;
                }
            }
                // 若是多行注释，需要等待取消多行注释
            else
            {
                if (ch == '*')
                    while (ch != '/')
                    {
                        sscanf(now++, "%c", &ch);
                        if (ch == '/')
                            MultiLinesComments = 0;
                        else if (ch == '*') // 这个错查了很久，需要防止这种情况： /*zhushi**/
                            continue;
                        else break;
                    }
            }
        }
        memset(buf, 0, sizeof(buf));
    }
    // 栈内元素判断，若不为空则仍然算错
    if (Bracket->TopOfStack != -1)
    {
        printf("without maching \'%c\' at line %d\n", Top(Bracket).bracket, Top(Bracket).line);
        return 0;
    }
    printf("%s\n", output);
    return 0;
}

