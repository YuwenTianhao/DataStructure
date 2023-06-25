/**
  ******************************************************************************
  * @file           : memory.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/2
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "LinkedList.h"
/**
 * 响应空间请求
 * @param space 请求的空间大小
 * @param P 目前循环列表的头指针（HEADER）
 * @return 请求后当前存储位置
 */
Position response(int space, Position P)
{
    Position now_position = First(P); // 目前循环列表Header指向的元素
    Position cycle = now_position; // 用于遍历循环列表的变量
    Position Best = NULL; // 最优先的删除对象
    if (cycle != NULL) // 遍历最优先删除的元素
        do
        {
            if (cycle->length >= space)
            {
                if (Best != NULL)
                {
                    if (cycle->length < Best->length)
                        Best = cycle;
                }
                else Best = cycle;
            }
            cycle = cycle->Next;
        } while (cycle != now_position);
    if (Best != NULL) // 删除及检查操作
    {
        Best->length -= space;
        if (Best->length == 0)
        {
            Position next = Best->Next;
            if(next != Best)
            {
                Position pre = FindPrevious(Best, First(P));
                free(Best);
                pre->Next = next;
                return next;
            }
            else
                return NULL;
        }
        return Best;
    }
    else return P->Next;
}
/**
 * 打印空闲空间
 * @param P
 */
void printSpareSpace(Position P)
{
    Position now_Position = First(P);
    Position cycle = now_Position;
    if (cycle == NULL)
        return;
    do
    {
        if(cycle->length != 0)
        printf("%d %d\n", cycle->start, cycle->length);
        cycle = cycle->Next;
    } while (cycle != now_Position);
}

int main()
{
    // 构建循环链表

    int tmp; // 空间链表总长度
    int request; // 空间请求
    List Storage = MakeNewList(); // 循环链表的dummy node
    Position tmp_storage = MakeNewNode();
    Storage->Next = tmp_storage;
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &tmp);
    for (int i = 0; i < tmp; i++)
    {
        int tmp_start;
        int tmp_length;
        scanf("%d%d", &tmp_start, &tmp_length);
        tmp_storage->start = tmp_start;
        tmp_storage->length = tmp_length;
        tmp_storage->Next = MakeNewNode();
        tmp_storage = tmp_storage->Next;
    }
    tmp_storage = FindPrevious(tmp_storage, Storage);
    tmp_storage->Next = First(Storage); // 闭合链表

    while (1)
    {
        scanf("%d", &request);
        if (request == -1)
            break;
        Storage->Next = response(request, Storage);
    }
    printSpareSpace(Storage);
}