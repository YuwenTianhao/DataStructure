/**
  ******************************************************************************
  * @file           : adjust.c
  * @author         : YuwenTianhao
  * @brief          : "4. 服务优化"
  * @attention      : 很有挑战性：
  *                   三个部分：
  *                   1、将登机口和流量信息（构造结构体）排好序
  *                   2、根据输入生成三叉树
  *                   3、得到三叉树中，同一高度的登机口，顺序衔接起来
  *                   最后一一对应输出就可以了
  *                   其中第三点相当于BFS，最为困难。其实如果用数组构造，那么BFS将轻而易举。
  *                   但是题目没有说树的深度要求，这就可能意味着我们最大需要开3^30左右的数组，根本不可能
  * @date           : 2023/4/28
  ******************************************************************************
  */

#include "adjust.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_GATE_NUM 100 // 最大登机口数量

int Pri[MAX_GATE_NUM] = {}; // 最合适的登机口排名
int now_pri_num; // 记录Pri[]现有登机口个数
// 广度优先搜索，生成最合适的登机口排名，此函数为PPT里案例，几乎没有改动
void layerorder(Position t)
{
    Position queue[MAX_GATE_NUM], p;
    int front, rear;
    if (t != NULL)
    {
        queue[0] = t;
        front = 0;
        rear = 0;
        while (front <= rear) /* 若队列不空 */
        {
            p = queue[front++];
            if (p->ID < 100)                     /* 访问p指结点 */
                Pri[now_pri_num++] = p->ID;
            if (p->Left != NULL)                  /* 若左孩子非空 */
                queue[++rear] = p->Left;
            if (p->Middle != NULL)              /* 若中孩子非空 */
                queue[++rear] = p->Middle;
            if (p->Right != NULL)               /* 若右孩子非空 */
                queue[++rear] = p->Right;
        }
    }
}
// qsort排序函数
int cmp_function(const void *p1, const void *p2)
{
    struct Port *a = (struct Port *) p1;
    struct Port *b = (struct Port *) p2;
    if (a->traffic > b->traffic)return -1;
    if (a->traffic < b->traffic)return 1;
    if (a->portID < b->portID)return -1;
    if (a->portID > b->portID)return 1;
    return 0;
}

int main()
{
    int TotalPortNum = 0; // 登机口总数
    TernaryTree Root = NULL; // 航站的三叉树
    int flag = 1; // 根节点（题目的安检处，即100，即第一组输入）的情况是完全不同的，此为第一次标志位
    // 1、读取并生成树：主要难在生成函数的设置以及输入情况的复杂
    while (1)
    {
        int ID[4] = {-1, -1, -1, -1}; // 每次记录登机口的编号：-1即标志该孩子为NULL
        int tmp = 0; // 用于多次读取scanf
        int i = 0; // 计数器：记录这一次输入的个数
        int j = 0; // 计数器：用于每一回合增加 TotalPortNum
        scanf("%d", &tmp);
        if (tmp == -1)break;
        else ID[i++] = tmp;
        while (1)
        {
            scanf("%d", &tmp);
            if (tmp == -1)break;
            ID[i++] = tmp;
        }
        // 第一次生成根结点
        if (flag)
        {
            Root = CreateNewTreeNode(ID[0], ID[1], ID[2], ID[3]); // 该函数十分重要
            flag = 0;
        }
        // 之后生成其他结点
        else
        {
            TernaryTree TmpTree = CreateNewTreeNode(ID[0], ID[1], ID[2], ID[3]);
            Root = Insert(TmpTree, Root);
        }
        // 勿忘增加总数
        while (j < i)
        {
            if (ID[j] < 100 && ID[j] != 0)
                TotalPortNum++;
            j++;
        }
    }
    // 2、读取并排序各登机口客流量，该部分最简单
    for (int i = 0; i < TotalPortNum; i++)
    {
        scanf("%d%d", &PortInstance[i].portID, &PortInstance[i].traffic);
    }
    qsort(PortInstance, TotalPortNum, sizeof(struct Port), cmp_function);
    // 3、广度优先搜索，生成最合适的登机口排名，此函数为PPT里案例，几乎没有改动
    layerorder(Root);
    // 4、打印输出
    for (int i = 0; i < TotalPortNum; i++)
    {
        printf("%d->%d\n", PortInstance[i].portID, Pri[i]);
    }
    return 0;
}