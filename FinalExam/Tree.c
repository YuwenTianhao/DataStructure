/**
  ******************************************************************************
  * @file           : Tree.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/20
  ******************************************************************************
  */

#include "Tree.h"
#include "stdio.h"
#include "stdlib.h"

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
        return NULL;
    if (X < T->Element)
        return Find(X, T->Left);
    else if (X > T->Element)
        return Find(X, T->Right);
    else
        return T;
}

Position FindMin(SearchTree T)
{
    if (T != NULL)
        while (T->Left != NULL)
            T = T->Left;
    return T;
}

Position FindMax(SearchTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    /* Create and return a one-node tree */
    if (T == NULL)
    {
        T = malloc(sizeof(struct TreeNode));
        T->Element = X;
        T->Left = T->Right = NULL;
    }
        /* Insert X in proper position */
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    /* Else X is already in the tree, we'll do nothing */
    return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;
    if (T == NULL)
    {
        printf("Element not found");
        return NULL;
    }
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else /* Found element to be deleted */
    if (T->Left && T->Right)
    {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else
    { /* One or zero children */
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}

void preOrderTraversal(SearchTree T)
{
    if (T == NULL)return;
    /**
     * do something
    */
    preOrderTraversal(T->Left);
    preOrderTraversal(T->Right);
}

void inOrderTraversal(SearchTree T)
{
    if (T == NULL)return;
    inOrderTraversal(T->Left);
    /**
     * do something
    */
    inOrderTraversal(T->Right);
}

void postOrderTraversal(SearchTree T)
{
    if (T == NULL)return;
    postOrderTraversal(T->Left);
    postOrderTraversal(T->Right);
    /**
     * do something
    */
}