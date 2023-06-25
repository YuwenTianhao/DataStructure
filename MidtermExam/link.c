/**
  ******************************************************************************
  * @file           : link.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/27
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXElement 100000

int cmp_times = 0;
struct Node;
typedef struct Node *PtrToNode; // 链表结点指针
typedef PtrToNode List; // 链表表头指针
typedef PtrToNode Position; // 链表结点指针

struct Node
{
    int num;
    int times;
    Position Next;
};

/**
 * @brief 创建新的链表
 * @note 需要使用malloc()-stdlib.h
 * @param None
 * @return List
 * @retval 新的链表的地址
 */
List MakeNewList()
{
    List L = malloc(sizeof(struct Node));
    memset(L, 0, sizeof(struct Node));
    return L;
}

/**
 * @brief 创建新的结点
 * @note 需要使用malloc()-stdlib.h
 * @param None
 * @return Position
 * @retval 新的链表的地址
 */
Position MakeNewNode()
{
    Position P = malloc(sizeof(struct Node));
    memset(P, 0, sizeof(struct Node));
    return P;
}

/**
* @brief 从链表L的尾部插入新的结点P，但是耗时
*/
void tailInsert(Position P, List L)
{
    Position Ptr = L;
    while (Ptr->Next != NULL)
        Ptr = Ptr->Next;
    Ptr->Next = P;
}

/**
* @brief 在链表头部插入新结点
*/
void headInsert(Position P, List L)
{
    P->Next = L->Next;
    L->Next = P;
}

/**
* @brief 找到P的上一个元素
*/
Position FindPrevious(Position P, List L)
{
    Position Pre = L;
    while (Pre->Next != NULL)
        if (Pre->Next == P)
            return Pre;
        else Pre = Pre->Next;
    return NULL;
}

Position Find(int element, List L)
{
    Position P = L->Next;
    while (P != NULL)
    {
        if (P->num == element)
        {
            P->times++;
            cmp_times++;
            return P;
        }
        P = P->Next;
        cmp_times++;
    }
    return NULL;
}

void Delete(Position Ptr, List L)
{
    Position Pre = FindPrevious(Ptr, L);
    Pre->Next = Ptr->Next;
    free(Ptr);
}

int main()
{
    List L = MakeNewList();
    int n;
    int k = 5;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);

        Position P = Find(tmp, L);
        if (P == NULL)
        {
            Position TmpNode = MakeNewNode();
            TmpNode->times = 1;
            TmpNode->num = tmp;
            tailInsert(TmpNode, L);
        }
        else
        {
            Position Tmp = MakeNewNode();
            Tmp->num = P->num;
            Tmp->times = P->times;
            headInsert(Tmp, L);
            Delete(P, L);
        }

    }
    while (k--)
    {
        if(L == NULL)
            break;
        L = L->Next;
        if (L != NULL)
            printf("%d %d\n", L->num, L->times);
    }
    printf("%d", cmp_times);
    return 0;
}