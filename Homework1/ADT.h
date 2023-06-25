/**
  ******************************************************************************
  * @file           : ADT.h
  * @author         : YuwenTianhao
  * @brief          : ADT的头文件
  * @attention      : 头文件只能声明，不能定义
  * @date           : 2023/3/14
  ******************************************************************************
  */

#ifndef HOMEWORK1_ADT_H
#define HOMEWORK1_ADT_H

#define ElementType int

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
Position FindPrevious(Position P, List L);
void Insert(ElementType X, List L, Position P);
void Delete(ElementType X,List L);
Position Header(List L);
Position First(List L);

#endif //HOMEWORK1_ADT_H

