/**
  ******************************************************************************
  * @file           : inter.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/16
  ******************************************************************************
  */

#ifndef FINALEXAM_INTER_H
#define FINALEXAM_INTER_H

typedef struct
{
    char name;
    float value;
}var;

// linked list

struct Node;
typedef struct Node *PtrToNode; // 链表结点指针
typedef PtrToNode List; // 链表表头指针
typedef PtrToNode Position; // 链表结点指针

struct Node
{
    var variable;
    Position Next;
};

Position Find(char element,List L)
{
    Position P = L->Next;
    while (P !=NULL)
    {
        if(P->variable.name == element)
        {
            return P;
        }
        P = P->Next;
    }
    return NULL;
}

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
* @brief 返回尾结点
*/
Position Last(List L)
{
    Position P = L;
    while (P->Next != NULL)
        P = P->Next;
    return P;
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

/**
* @brief 返回结点长度（int）
*/
int LengthOfList(List L)
{
    int n = 0;
    while (L->Next != NULL)
    {
        n++;
        L = L->Next;
    }
    return n;
}

/**
* @brief 在链表L中插入新的结点，且将结点置于P的前面
*/
void Insert(Position NewPtr, List L, Position P)
{
    Position Pre = FindPrevious(P, L);
    Pre->Next = NewPtr;
    NewPtr->Next = P;
}

/**
* @brief 链表中删除Ptr
*/
void Delete(Position Ptr, List L)
{
    Position Pre = FindPrevious(Ptr, L);
    Pre->Next = Ptr->Next;
    free(Ptr);
}

/**
* @brief 清空链表
*/
List MakeEmpty(List L)
{
    while (L != NULL)
    {
        Position Ptr = L;
        Ptr = L->Next;
        free(L);
        L = Ptr;
    }
    return L;
}

/**
* @brief 检查链表是否为空
*/
int IsEmpty(List L)
{
    return L->Next == NULL;
}

/**
* @brief 检查元素是否为链表的最后一个元素
*/
int IsLast(Position P, List L)
{
    return P->Next == NULL;
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

#endif //FINALEXAM_INTER_H
