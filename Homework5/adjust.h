/**
  ******************************************************************************
  * @file           : adjust.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/28
  ******************************************************************************
  */

#ifndef HOMEWORK5_ADJUST_H
#define HOMEWORK5_ADJUST_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct TreeNode;
typedef struct TreeNode *Position; // 三叉树树结点指针
typedef struct TreeNode *TernaryTree; // 三叉树根结点指针

/**
* @brief 登机口的实例
*/
struct Port
{
    int portID;
    int traffic;
} PortInstance[100];
/**
* @brief 三叉树
*/
struct TreeNode
{
    int ID;
    TernaryTree Left;
    TernaryTree Middle;
    TernaryTree Right;
};
/**
 * @brief 树的插入函数
 * @note 与普通插入函数完全不同：题目保证X一定可以在T中找到，因此若没有该结点则原树无变化
 * @param X:构造一个新的树结点后，插入树中
 * @param T:被插入的树
 * @return TernaryTree
 * @retval 插入后的树
 */
TernaryTree Insert(Position X, TernaryTree T)
{
    if (T == NULL)
        return NULL;
    /* Insert X in proper position */
    if (T->ID == X->ID)
    {
        T = X;
        return T;
    }
    else
    {
        T->Left = Insert(X, T->Left);
        T->Right = Insert(X, T->Right);
        T->Middle = Insert(X, T->Middle);
    }
    /* Else X is already in the tree, we'll do nothing */
    return T;
}
/**
 * @brief 创建新的树结点
 * @note 四个参数分别为根结点、左儿子、中儿子、右儿子的编号，-1表示该儿子不存在，不能超过2个儿子不存在
 * @param RootID：根结点的编号
 * @param LeftID：左儿子的编号
 * @param MiddleID：中儿子的编号
 * @param RightID：右儿子的编号
 * @return TernaryTree
 * @retval 创建好的树
 */
TernaryTree CreateNewTreeNode(int RootID, int LeftID, int MiddleID, int RightID)
{
    TernaryTree T = malloc(sizeof(struct TreeNode));
    T->Left = malloc(sizeof(struct TreeNode));
    T->Middle = malloc(sizeof(struct TreeNode));
    T->Right = malloc(sizeof(struct TreeNode));
    memset(T->Left, 0, sizeof(struct TreeNode));
    memset(T->Right, 0, sizeof(struct TreeNode));
    memset(T->Middle, 0, sizeof(struct TreeNode));
    T->ID = RootID;
    T->Left->ID = LeftID;
    if (MiddleID != -1)
        T->Middle->ID = MiddleID;
    else
        T->Middle = NULL;
    if (RightID != -1)
        T->Right->ID = RightID;
    else
        T->Right = NULL;
    return T;
}

#endif //HOMEWORK5_ADJUST_H
