/**
  ******************************************************************************
  * @file           : graphSearch.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/5
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Graph.h"

int vertex_num;
int edge_num;
int delete_v;

VLink Gra[MaxV]; // 创建图
int  Visited[MaxV] ; // DFS：标识顶点是否被访问过

typedef struct{
    int v1;
    int v2;
}Nodes;
Nodes nodes[MaxV];

int cmp_function(const void *p1, const void *p2)
{
    Nodes *e1 = (Nodes *)p1;
    Nodes *e2 = (Nodes *)p2;
    if(e1->v1 >e2->v1)return 1;
    if(e1->v1 < e2->v1)return -1;
    if(e1->v2 > e2->v2)return 1;
    if(e1->v2 < e2->v2)return  -1;
    return  0;
}

void DFS(VLink G[], int v)
{
    ELink  *p;
    Visited[v] = 1; //标识某顶点被访问过
    printf("%d ",v); //访问某顶点
    for(p = G[v].link; p !=NULL;  p=p->next)
        if( !Visited[p->adjvex] )
            DFS(G, p->adjvex);
}

void BFS(VLink G[], int v)
{
    int front = 0,rear = - 1;
    int queue[MaxV] = {0};
    ELink  *p;
    Visited[v] = 1;
    queue[++rear] = v;
    while (front<=rear)
    {
        v = queue[front++];
        printf("%d ",v);
        for(p = G[v].link;p!=NULL;p=p->next)
            if(!Visited[p->adjvex])
            {
                Visited[p->adjvex] = 1;
                queue[++rear] = p->adjvex;
            }
    }
}

int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%d%d",&vertex_num,&edge_num);
    for(int i = 0 ; i < edge_num;i++)
        scanf("%d%d",&nodes[i].v1,&nodes[i].v2);
    scanf("%d",&delete_v);
    qsort(nodes,edge_num, sizeof(Nodes),cmp_function);
    for(int i = 0 ; i < edge_num;i++)
    {
        Gra[nodes[i].v1].link = insertEdge( Gra[nodes[i].v1].link,nodes[i].v2);
        Gra[nodes[i].v2].link = insertEdge(Gra[nodes[i].v2].link,nodes[i].v1);
    }
    DFS(Gra,0);
    printf("\n");
    memset(Visited,0,edge_num*sizeof(int));
    BFS(Gra,0);
    memset(Visited,0,edge_num*sizeof(int));
    printf("\n");
    Visited[delete_v] = 1;
    DFS(Gra,0);
    printf("\n");
    memset(Visited,0,edge_num*sizeof(int));
    Visited[delete_v] = 1;
    BFS(Gra,0);
    memset(Visited,0,edge_num*sizeof(int));
    return 0;
}