/**
  ******************************************************************************
  * @file           : bst.c
  * @author         : YuwenTianhao
  * @brief          : "1. 树叶节点遍历（树-基础题）"
  * @attention      : 由于和普通树的操作不全一致，因此有关联头文件
  * @attention      : 对树的每一个操作都需要检验空树，否则很容易SIGSEGV
  * @attention      : 远不是最优，但很可能最简
  * @date           : 2023/4/27
  ******************************************************************************
  */

#include "bst.h"

void search_leaf(SearchTree T)
{
    if(T == NULL)return;
    else if (T->Left == NULL && T->Right == NULL)
        T->isLeaf = 1;
    if (T->Left != NULL)
        search_leaf(T->Left);
    if (T->Right != NULL)
        search_leaf(T->Right);
    return;
}

void Tree_Height(SearchTree T, int height)
{
    if(T == NULL)return;
    T->height = height;
    if (T->Left == NULL && T->Right == NULL)
        return;
    if (T->Left != NULL)
        Tree_Height(T->Left, height + 1);
    if (T->Right != NULL)
        Tree_Height(T->Right, height + 1);
    return;
}

void PrintLeaf(SearchTree T)
{
    if(T == NULL)return;
    if (T->isLeaf)
        printf("%d %d\n", T->Element, T->height);
    else
    {
        PrintLeaf(T->Left);
        PrintLeaf(T->Right);
    }
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    SearchTree T = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        T = Insert(tmp, T);
    }
    search_leaf(T);
    Tree_Height(T, 1);
    PrintLeaf(T);
}