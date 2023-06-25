/**
  ******************************************************************************
  * @file           : memory1.c
  * @author         : YuwenTianhao
  * @brief          : 空闲空间申请-复做
  * @attention      : 该版的逻辑清晰多了
  * @date           : 2023/4/23
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "CircularLinkedList.h"

Position response(int space, List L)
{
    Position flag = NULL;
    Position cycle = First(L);
    Position returnPtr = NULL;
    do
    {
        if (cycle->length == space)
        {
            if (cycle->Next != cycle) // 删除分类讨论了，然而返回值也需要分类讨论
            {
                returnPtr = cycle->Next;
                DeleteCircular(cycle, L);
                return returnPtr;
            }
            return NULL;
        }
        if (cycle->length > space)
        {
            if (flag == NULL) flag = cycle;
            else flag = cycle->length > flag->length ? flag : cycle;
        }
        cycle = cycle->Next;
    } while (cycle != First(L));
    if (flag != NULL)
    {
        returnPtr = flag;
        flag->length -= space;
        return returnPtr;
    }
    return First(L);
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int size; // 空间链表总长度
    int request; // 空间请求
    List Storage = MakeNewList(); // 循环链表的dummy node
    Position tmp_storage = MakeNewNode();
    Storage->Next = tmp_storage;
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
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
    if (!IsEmpty(Storage))
    {
        Position cycle = First(Storage);
        do
        {
            if (cycle->length != 0)
                printf("%d %d\n", cycle->start, cycle->length);
            cycle = cycle->Next;
        } while (cycle != First(Storage));
    }
    return 0;
}