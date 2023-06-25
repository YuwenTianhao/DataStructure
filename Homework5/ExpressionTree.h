/**
  ******************************************************************************
  * @file           : ExpressionTree.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/28
  ******************************************************************************
  */

#ifndef HOMEWORK5_EXPRESSIONTREE_H
#define HOMEWORK5_EXPRESSIONTREE_H

#include "stdlib.h"

/**
* @brief 数据栈和符号栈的联合
*/
union sym
{
    int num;
    char op;
};

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct StackRecord;
typedef struct StackRecord *Stack;

Stack CreateStack(int MaxElements);
void Push(SearchTree X,Stack S);
SearchTree TopAndPop(Stack S);

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    SearchTree *Array;
};

struct TreeNode
{
    int category; // 0 for num, 1 for enum oper
    union sym Element;
    SearchTree Left;
    SearchTree Right;
};

Stack CreateStack(int MaxElements)
{
    Stack S;
    S = malloc(sizeof( struct StackRecord ) );
//    if(S == NULL)
//    {
//        printf("Out of space!");
//        return NULL;
//    }
    S->Array = malloc(sizeof(int) * MaxElements);
//    if( S->Array == NULL )
//    {
//        printf("Out of space!");
//        return NULL;
//    }
    S->Capacity = MaxElements;
    S->TopOfStack = -1; // Empty Stack
    return S;
}

void Push(SearchTree X,Stack S)
{
//    if(S->TopOfStack == S->Capacity - 1)
//    {
//        printf("Out of space!");
//        return;
//    }
    S->Array [ ++S->TopOfStack ] = X;
}

SearchTree TopAndPop(Stack S)
{
//    if(S->TopOfStack == -1)
//    {
//        printf("Out of space!");
//        return 0;
//    }
    return S->Array[ S->TopOfStack -- ];
}



#endif //HOMEWORK5_EXPRESSIONTREE_H
