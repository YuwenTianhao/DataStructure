/**
  ******************************************************************************
  * @file           : list.c
  * @author         : YuwenTianhao
  * @brief          : ”5. 全排列数的生成“
  * @attention      : 1、用一个栈来存储即将输出的该组数据
  *                   2、用一个数组来表示该组里未被使用过的数
  *                   3、递归（最难想）
  *                   本题是唯一一道不是自己做出来的
  * @date           : 2023/3/15
  ******************************************************************************
  */
#include <stdio.h>
#define MAX 10

int Mark[MAX];
char Stack[MAX + 1];
int N;
void print(char *ptr);
void rank(int top, int n);
int main()
{
    scanf("%d", &N);
    rank(0, N);
    return 0;
}
void rank(int top, int n) //
{
    int i;

    if (n == 0)
    {
        Stack[top] = '\0';
        print(Stack);
        return;
    }
    for (i = 1; i < N + 1; i++) // 遍历 1->N 的所有数，取最小的放入 Stack 的顶部
    {
        if (Mark[i] == 0)
        {
            Mark[i] = 1;
            Stack[top] = '0' + i; // Push
            rank(top + 1, n - 1);
            Mark[i] = 0;
        }
    }
}

void print(char *ptr)
{
    while (*ptr != '\0')
    {
        printf("%c ",*ptr);
        ptr++;
    }
    printf("\n");
}