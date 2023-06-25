/**
  ******************************************************************************
  * @file           : ADT.c
  * @author         : YuwenTianhao
  * @brief          : 这里是关于ADT的初步学习，参考教材为《数据结构与算法分析——C语言描述》:Mark Allen Weiss
  * @attention      : 主要是关于链表的学习
  * @date           : 2023/3/14
  ******************************************************************************
  */

#include "ADT.h"
#include "stdio.h"
#include "stdlib.h"
// 表
// 对于普通表，有一些最基本的概念
// 表有顺序关系，有前驱元、后驱元， 表的元素Ai应该是可以在表A中排序的
// 表中数值可以是整数，也可以是复数
// 对表的操作集合： PrintList  MakeEmpty  Find（关键字首次出现的位置） Insert Delete
// Next Previous 也是一种操作
// 当然所有操作的有无都取决于程序员

// 最简单的表是通过数组实现的 但很不常用 最大的问题已经出现了：1、空间浪费 2、删改困难
// 数组最大的缺点：虽然是动态指定的， 但是需要估计最大数量， 严重浪费空间！！！
// PrintList Find 都是线性执行 O(N)

// 链表
// 最大的优点就是： 避免了插入和删除的线性开销，允许表不连续储存
// 一般是由结构构成
// A1 -> A2 -> A3 -> NULL
// Next指针
// 删除和插入都是修改指针，特别的，插入需要调用malloc
// 程序设计细节： 1、起始端插入元素困难 2、起始段删除困难 3、一般的删除，找前面一项很困难
// 为解决1 2，将其稍作变化，留出一个标志节点，称为表头header（dummy node）
// 为解决3 我们需要编写 FindPrevious
// 但是由于Find只能找到关键字的第一个， FindPrevious也只能这样。故

struct Node
{
    ElementType Element;
    Position Next;
};


int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Position P, List L)
{
    return P->Next == NULL;
}

/**
 * @brief 用于查找链表的某一个值
 * @note None
 * @param X: 查找的值 L: 列表
 * @return Position : struct Node *PtrToNode
 * @retval 找到该值的位置或返回 NULL
 */
Position Find(ElementType X, List L)
{
    Position P;
    P = L->Next;
    while (P != NULL && P->Element != X)
    {
        P = P->Next;
    }
    return P;
}

/**
 * @brief 用于查找链表的某一个值的上一个指针位置
 * @note None
 * @param P: 查找的该元素 L: 列表
 * @return Position : struct Node *PtrToNode
 * @retval 找到该值上一个的位置或返回 队尾
 */
Position FindPrevious(Position P, List L)
{
    Position Pre;
    Pre = L;
    while (Pre->Next != NULL && Pre->Next != P)
    {
        Pre = Pre->Next;
    }
    return Pre;
}

/**
 * @brief 删除链表中的一个元素
 * @note 由于 Find() FindPrevious() 的特性，有可能是队尾（若判断是队尾则不操作）
 * @param ElementType X: 删除的对象
 * @return None
 * @retval None
 */
void Delete(ElementType X, List L)
{
    Position P = Find(X, L);
    Position Pre = Find(P, L);
    Position Tmp;
    if (!IsLast(Pre, L))
    {
        Tmp = Pre->Next;
        Pre->Next = Tmp->Next;
        free(Tmp);
    }
}

void Insert(ElementType X, List L, Position P)
{
    Position Tmp;
    Tmp = malloc(sizeof(struct Node));
    Tmp->Element = X;
    Tmp->Next = P->Next;
    P->Next = Tmp;
}

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}