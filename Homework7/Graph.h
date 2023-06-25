/**
  ******************************************************************************
  * @file           : Graph.h
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/5
  ******************************************************************************
  */

#ifndef HOMEWORK7_GRAPH_H
#define HOMEWORK7_GRAPH_H

#define MaxV  256 // <最大顶点个数>

typedef struct edge
{
    int adjvex;
    int weight;
    struct edge *next;
} ELink;

typedef struct ver
{
    int vertex;
    ELink *link;
} VLink;

void createGraph();

//在链表尾插入一个节点
// 使用方法同Tree ： G[v1].link = insertEdge(G[v1].link,v2);
ELink *insertEdge(ELink *head, int avex)
{
    ELink *e, *p;
    e = (ELink *) malloc(sizeof(ELink));
    e->adjvex = avex;
    e->weight = 1;
    e->next = NULL;
    if (head == NULL)
    {
        head = e;
        return head;
    }
    for (p = head; p->next != NULL; p = p->next);
    p->next = e;
    return head;
}


#endif //HOMEWORK7_GRAPH_H
