/**
  ******************************************************************************
  * @file           : CircularLinkedList.h
  * @author         : YuwenTianhao
  * @brief          : 循环链表头文件
  * @attention      : None
  * @date           : 2023/4/23
  ******************************************************************************
  */

#ifndef HOMEWORK3_CIRCULARLINKEDLIST_H
#define HOMEWORK3_CIRCULARLINKEDLIST_H

#define ElementType int

struct Node;
typedef struct Node *PtrToNode; // 链表结点指针
typedef PtrToNode List; // 链表表头指针
typedef PtrToNode Position; // 链表结点指针
/**
* @brief 链表结点
*/
struct Node
{
    ElementType start;
    ElementType length;
    Position Next;
};
List MakeNewList(); // 创建新链表表头

Position MakeNewNode(); // 创建新链表结点

void tailInsert(Position P, List L); // 向链表末端插入新的结点 P

void headInsert(Position P, List L); // 向链表 L 前端（表头后一位）插入新的结点 P

int IsEmpty(List L); // 检查链表 L 是否为空

int IsLast(Position P, List L); // 检查 P 是否为链表 L 的最后一个元素

Position Last(List L);

Position LastCircular(List L); // 返回链表 L 的尾部元素

Position Find(ElementType X, List L); // 在链表 L 中找到 ElementType X 返回结点指针

Position FindPrevious(Position P, List L);

Position FindPreviousCircular(Position P, List L); // 在链表 L 中找到结点 P 的上一个位置

void Insert(Position NewPtr, List L, Position P); // 在链表 L 中

void Delete(Position Ptr, List L);

void DeleteCircular(Position Ptr, List L);

Position Header(List L); // 链表 L 的表头

Position First(List L); // 链表 L 的首个非表头结点



int LengthOfListCircular(List L); // 链表 L 的长度

#endif //HOMEWORK3_CIRCULARLINKEDLIST_H
