/**
  ******************************************************************************
  * @file           : LinkedList.h
  * @author         : YuwenTianhao
  * @brief          : 链表结构头文件
  * @attention      : None
  * @date           : 2023/3/18
  ******************************************************************************
  */
  // 链表还可以有插入排序！注意

#ifndef HOMEWORK3_LINKEDLIST_H
#define HOMEWORK3_LINKEDLIST_H

#define MAX_WORD 64

#define ElementType int //数据类型

int cmp_times = 0;

struct Node;
typedef struct Node *PtrToNode; // 链表结点指针
typedef PtrToNode List; // 链表表头指针
typedef PtrToNode Position; // 链表结点指针
/** 
* @brief 链表结点
*/
struct Node
{
    int num;
    int times;
    Position Next;
};
List MakeNewList(); // 创建新链表表头

Position MakeNewNode(); // 创建新链表结点

void tailInsert(Position P, List L); // 向链表末端插入新的结点 P

void headInsert(Position P, List L); // 向链表 L 前端（表头后一位）插入新的结点 P

List MakeEmpty(List L); // 清空链表 L

int IsEmpty(List L); // 检查链表 L 是否为空

int IsLast(Position P, List L); // 检查 P 是否为链表 L 的最后一个元素

Position Last(List L); // 返回链表 L 的尾部元素

Position Find(ElementType X, List L); // 在链表 L 中找到 ElementType X 返回结点指针

Position FindPrevious(Position P, List L); // 在链表 L 中找到结点 P 的上一个位置

void Insert(Position NewPtr, List L, Position P); // 在链表 L 中

void Delete(Position Ptr, List L); // 在链表 L 中删除结点 P

Position Header(List L); // 链表 L 的表头

Position First(List L); // 链表 L 的首个非表头结点

int LengthOfList(List L); // 链表 L 的长度

void SortList(List L); // 以正序（从小到大）按冒泡排序对链表 L 进行排序。

void SortList_Reverse(List L, int NumOfElements, int (*PtFuncCompare)(const void *, const void *)); // 以逆序（从大到小）按冒泡排序对链表 L 进行排序。

#endif //HOMEWORK3_LINKEDLIST_H
