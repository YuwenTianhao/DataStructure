/**
  ******************************************************************************
  * @file           : line.c
  * @author         : YuwenTianhao
  * @brief          : "1. 连续线段"
  * @attention      : 一遍过
  * @date           : 2023/3/27
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "LinkedList.h"

struct Node
{
    int x_1;
    int y_1;
    int x_2;
    int y_2;
    Position Next;
};

List Line[100];
int total_Lines;

void headInsert(Position P, List L)
{
    P->Next = L->Next;
    L->Next = P;
}

void tailInsert(Position P, List L)
{
    Position Ptr;
    Ptr = L;
    while (Ptr->Next != NULL)
        Ptr = Ptr->Next;
    Ptr->Next = P;
}

Position First(List L)
{
    return L->Next;
}

Position Last(List L)
{
    Position Ptr = L;
    while (Ptr->Next != NULL)
        Ptr = Ptr->Next;
    return Ptr;
}

int lineLength(List L)
{
    int length = 0;
    Position Ptr = L;
    while (Ptr->Next != NULL)
    {
        Ptr = Ptr->Next;
        length++;
    }
    return length;
}

void initList(Position P)
{
    memset(P, 0, sizeof(struct Node));
}

int main()
{
    int n = 0;
    int length_longest = 0;
    int x1_longest = 0;
    int y1_longest = 0;
    scanf("%d", &n);
    while (n--)
    {
        Position Tmp = malloc(sizeof(struct Node));
        int flag = 0; // flag = 0 新建一个线段存储， flag = 1 可以和先前线段连接起来
        initList(Tmp);
        scanf("%d%d%d%d", &Tmp->x_1, &Tmp->y_1, &Tmp->x_2, &Tmp->y_2);
        for (int i = 0; i < total_Lines; i++)
        {
            if (Tmp->x_2 == First(Line[i])->x_1 && Tmp->y_2 == First(Line[i])->y_1)
            {
                headInsert(Tmp, Line[i]);
                flag = 1;
            }
            if (Tmp->x_1 == Last(Line[i])->x_2 && Tmp->y_1 == Last(Line[i])->y_2)
            {
                tailInsert(Tmp, Line[i]);
                flag = 1;
            }
        }
        if (!flag)
        {
            Line[total_Lines] = malloc(sizeof(struct Node));
            initList(Line[total_Lines]);
            tailInsert(Tmp, Line[total_Lines]);
            total_Lines++;
        }
    }
    for (int i = 0; i < total_Lines; i++)
    {
        if (lineLength(Line[i]) > length_longest)
        {
            length_longest = lineLength(Line[i]);
            x1_longest = First(Line[i])->x_1;
            y1_longest = First(Line[i])->y_1;
        }
    }
    printf("%d %d %d", length_longest, x1_longest, y1_longest);
    return 0;
}