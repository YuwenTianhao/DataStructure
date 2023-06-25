/**
  ******************************************************************************
  * @file           : Tree.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : 还应该添加遍历
  * @date           : 2023/4/20
  ******************************************************************************
  */

#ifndef HOMEWORK5_TREE_H
#define HOMEWORK5_TREE_H

#define ElementType int

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X,SearchTree T);
SearchTree Delete(ElementType X,SearchTree T);
ElementType Retrive(Position P);

#endif //HOMEWORK5_TREE_H

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};