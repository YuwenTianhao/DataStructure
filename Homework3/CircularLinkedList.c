/**
  ******************************************************************************
  * @file           : CircularLinkedList.c
  * @author         : YuwenTianhao
  * @brief          : 循环链表的C文件
  * @attention      : 循环链表的查找和返回都可能出错，只能用逻辑的复杂和时间的增加换取可靠性，且循环链表分为开环和闭环的状态操作
  * @date           : 2023/4/23
  ******************************************************************************
  */

#include "CircularLinkedList.h"
#include "stdlib.h"
#include "string.h"

// 每一次针对如下语句需要格外小心，如果链表为空，该遍历直接会卡死，若不使用如下语句也会有很多问题
//        Position P = First(L);
//        while (P->Next != First(L))

/**
* @brief 返回头结点
*/
Position Header(List L)
{
    return L;
}

/**
* @brief 返回首个元素（有头节点的链表）
*/
Position First(List L)
{
    return L->Next;
}

/**
* @brief 返回尾结点（针对已经闭合的链表）：如果链表为空返回NULL
*/
Position LastCircular(List L)
{
    // 如果链表为空，直接判断会卡死
    if (!IsEmpty(L))
    {
        Position P = First(L);
        while (!IsLast(P, L))
            P = P->Next;
        return P;
    }
    return NULL;
}

Position Last(List L)
{
    // 如果链表为空，直接判断会卡死
    if (!IsEmpty(L))
    {
        Position P = First(L);
        while (!IsLast(P, L))
            P = P->Next;
        return P;
    }
    return NULL;
}

/**
* @brief 找到P的上一个元素（未闭合的链表）：若没有找到返回NULL;
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

/**
* @brief 找到P的上一个元素（针对已经闭合的链表）：若没有找到或只有一个元素返回NULL;
*/
Position FindPreviousCircular(Position P, List L)
{
    if(First(L) == P)
    {
        if(P ->Next == P)
            return NULL;
        else
            return LastCircular(L);
    }
    else
    {
        Position Pre = First(L);
        while (Pre->Next != First(L))
        {
            if(Pre->Next == P)
                return Pre;
            Pre = Pre->Next;
        }
        return NULL;
    }
}
/**
* @brief 返回结点长度（已经闭合的循环链表）
*/
int LengthOfListCircular(List L)
{
    if (IsEmpty(L))return 0;
    else
    {
        int n = 1;
        Position P = First(L);
        while (P->Next != First(L))
            n++;
        return n;
    }
}

/**
* @brief 在链表L中插入新的结点，且将结点置于P的后面
*/
void Insert(Position NewPtr, List L, Position P)
{
    NewPtr->Next = P->Next;
    P->Next = NewPtr;
}

/**
* @brief 在未闭合链表L中删除Ptr，无错误检测
*/
void Delete(Position Ptr, List L)
{
    Position Pre = FindPrevious(Ptr, L);
    Pre->Next = Ptr->Next;
    free(Ptr);
}

/**
* @brief 闭合链表中删除Ptr，无错误检查（若Ptr不在L中则死循环）
*/
void DeleteCircular(Position Ptr, List L)
{
    if (IsEmpty(L)) return; // 如果链表为空遍历会卡死
    if (Ptr == First(L)) // 如果是头结点需要判断，因为这时候findPrevious()会返回NULL
    {
        if (IsLast(Ptr, L)) // 链表中只有头结点
        {
            L->Next = NULL; // 删除后只剩表头
            free(Ptr);
        }
        else // 是表头，但是不是表中的唯一元素
        {
            LastCircular(L)->Next = Ptr->Next;
            L->Next = Ptr->Next;
            free(Ptr);
        }
        return;
    }
    else // 若链表既不为空，也不删除第一个结点
    {
        Position Pre = FindPreviousCircular(Ptr, L);
        Pre->Next = Ptr->Next;
        free(Ptr);
        return;
    }
}



/**
* @brief 检查链表是否为空
*/
int IsEmpty(List L)
{
    return L->Next == NULL;
}

/**
* @brief 检查元素是否为链表的最后一个元素（闭合链表）
*/
int IsLast(Position P, List L)
{
    return P->Next == First(L);
}

/**
* @brief 从链表L的尾部插入新的结点P（未闭合链表）
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
