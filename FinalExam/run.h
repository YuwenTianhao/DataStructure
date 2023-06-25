/**
  ******************************************************************************
  * @file           : run.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/17
  ******************************************************************************
  */

#ifndef FINALEXAM_RUN_H
#define FINALEXAM_RUN_H

#include "stdio.h"
#include "stdlib.h"

#define ElementType int

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);

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

#endif //FINALEXAM_RUN_H
