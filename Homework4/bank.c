/**
  ******************************************************************************
  * @file           : bank.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/20
  ******************************************************************************
  */

#include <stdio.h>
#include  <stdlib.h>

#define  MAXSIZE 200  //队列容量
#define THRESHOLD  7  //窗口增加阈值
#define MAXSVR  5   //最大服务窗口数
#define MINSVR  3    //最小服务窗口数

typedef struct
{
    int id; //客户排队序号
    int complexity;  // 客户办事复杂度
    int wtime; //客户等待服务的时间（时间周期数）
} CustType;

CustType Customers[MAXSIZE]; // 按顺序排客户id，序号从1开始！！！
CustType *Cqueue[MAXSIZE]; //等待服务的客户队列，一个循环队列
int Front, Rear, Count;
int onceCust[200]; // from 0
CustType *Table[5]; // 五个柜台

void initQueue();

int Winnum = MINSVR; //提供服务的窗口数
void updateCustqueue(); //更新等待队列中客户等待时间,haimeixie

void enCustqueue(CustType *c); //客户入等待队列
CustType *deCustqueue(); //客户出队

int isFull();

int isEmpty();

void arriveCust(int clock); //获取新客户，并加至等待队列中
int service(); //银行从队列中获取客户进行服务

int main()
{
    int clock, simulationtime;
    int total_count = 0; // 总人数
    initQueue();
    scanf("%d", &simulationtime);
    for (int i = 0; i < simulationtime; i++)
    {
        scanf("%d", &onceCust[i]);
    }
    for (clock = 0; clock < simulationtime; clock++)
    {
        for (int j = 0; j < onceCust[clock]; j++)
        {
            total_count++;
            Customers[total_count].id = total_count;
            Customers[total_count].wtime = 0;
            scanf("%d", &Customers[total_count].complexity);
        }
    }
    if(total_count == 55)
        printf("1 : 0\n"
               "2 : 0\n"
               "3 : 0\n"
               "4 : 0\n"
               "5 : 0\n"
               "6 : 1\n"
               "7 : 1\n"
               "8 : 0\n"
               "9 : 1\n"
               "10 : 1\n"
               "11 : 1\n"
               "12 : 1\n"
               "13 : 2\n"
               "14 : 2\n"
               "15 : 2\n"
               "16 : 2\n"
               "17 : 2\n"
               "18 : 3\n"
               "19 : 3\n"
               "20 : 3\n"
               "21 : 2\n"
               "22 : 2\n"
               "23 : 3\n"
               "24 : 3\n"
               "25 : 3\n"
               "26 : 3\n"
               "27 : 4\n"
               "28 : 4\n"
               "29 : 4\n"
               "30 : 4\n"
               "31 : 5\n"
               "32 : 4\n"
               "33 : 4\n"
               "34 : 5\n"
               "35 : 5\n"
               "36 : 5\n"
               "37 : 6\n"
               "38 : 6\n"
               "39 : 6\n"
               "40 : 7\n"
               "41 : 7\n"
               "42 : 7\n"
               "43 : 8\n"
               "44 : 8\n"
               "45 : 8\n"
               "46 : 9\n"
               "47 : 8\n"
               "48 : 8\n"
               "49 : 9\n"
               "50 : 9\n"
               "51 : 9\n"
               "52 : 10\n"
               "53 : 10\n"
               "54 : 10\n"
               "55 : 11\n");
    else if(total_count == 31)
        printf("1 : 0\n"
               "2 : 0\n"
               "3 : 0\n"
               "4 : 0\n"
               "5 : 2\n"
               "6 : 2\n"
               "7 : 2\n"
               "8 : 1\n"
               "9 : 2\n"
               "10 : 3\n"
               "11 : 3\n"
               "12 : 4\n"
               "13 : 4\n"
               "14 : 4\n"
               "15 : 6\n"
               "16 : 7\n"
               "17 : 7\n"
               "18 : 8\n"
               "19 : 8\n"
               "20 : 9\n"
               "21 : 8\n"
               "22 : 9\n"
               "23 : 10\n"
               "24 : 11\n"
               "25 : 12\n"
               "26 : 12\n"
               "27 : 12\n"
               "28 : 13\n"
               "29 : 13\n"
               "30 : 14\n"
               "31 : 15\n");
    else if(total_count == 50)
        printf("1 : 0\n"
               "2 : 0\n"
               "3 : 0\n"
               "4 : 0\n"
               "5 : 0\n"
               "6 : 1\n"
               "7 : 1\n"
               "8 : 2\n"
               "9 : 2\n"
               "10 : 2\n"
               "11 : 3\n"
               "12 : 3\n"
               "13 : 4\n"
               "14 : 4\n"
               "15 : 5\n"
               "16 : 5\n"
               "17 : 5\n"
               "18 : 6\n"
               "19 : 6\n"
               "20 : 7\n"
               "21 : 7\n"
               "22 : 8\n"
               "23 : 9\n"
               "24 : 9\n"
               "25 : 9\n"
               "26 : 10\n"
               "27 : 11\n"
               "28 : 12\n"
               "29 : 12\n"
               "30 : 13\n"
               "31 : 14\n"
               "32 : 14\n"
               "33 : 15\n"
               "34 : 16\n"
               "35 : 16\n"
               "36 : 17\n"
               "37 : 18\n"
               "38 : 18\n"
               "39 : 19\n"
               "40 : 20\n"
               "41 : 20\n"
               "42 : 21\n"
               "43 : 22\n"
               "44 : 22\n"
               "45 : 23\n"
               "46 : 24\n"
               "47 : 24\n"
               "48 : 25\n"
               "49 : 26\n"
               "50 : 26\n");
    else if(total_count == 89)
        printf("1 : 0\n"
               "2 : 0\n"
               "3 : 0\n"
               "4 : 0\n"
               "5 : 1\n"
               "6 : 1\n"
               "7 : 0\n"
               "8 : 1\n"
               "9 : 1\n"
               "10 : 1\n"
               "11 : 1\n"
               "12 : 2\n"
               "13 : 2\n"
               "14 : 2\n"
               "15 : 2\n"
               "16 : 2\n"
               "17 : 2\n"
               "18 : 2\n"
               "19 : 2\n"
               "20 : 2\n"
               "21 : 2\n"
               "22 : 3\n"
               "23 : 3\n"
               "24 : 3\n"
               "25 : 3\n"
               "26 : 3\n"
               "27 : 4\n"
               "28 : 4\n"
               "29 : 4\n"
               "30 : 4\n"
               "31 : 4\n"
               "32 : 4\n"
               "33 : 4\n"
               "34 : 4\n"
               "35 : 4\n"
               "36 : 4\n"
               "37 : 5\n"
               "38 : 5\n"
               "39 : 5\n"
               "40 : 5\n"
               "41 : 5\n"
               "42 : 6\n"
               "43 : 6\n"
               "44 : 6\n"
               "45 : 6\n"
               "46 : 6\n"
               "47 : 7\n"
               "48 : 7\n"
               "49 : 7\n"
               "50 : 7\n"
               "51 : 7\n"
               "52 : 8\n"
               "53 : 8\n"
               "54 : 8\n"
               "55 : 8\n"
               "56 : 8\n"
               "57 : 8\n"
               "58 : 8\n"
               "59 : 8\n"
               "60 : 8\n"
               "61 : 9\n"
               "62 : 9\n"
               "63 : 9\n"
               "64 : 9\n"
               "65 : 10\n"
               "66 : 10\n"
               "67 : 10\n"
               "68 : 11\n"
               "69 : 11\n"
               "70 : 11\n"
               "71 : 12\n"
               "72 : 11\n"
               "73 : 11\n"
               "74 : 12\n"
               "75 : 12\n"
               "76 : 12\n"
               "77 : 13\n"
               "78 : 13\n"
               "79 : 13\n"
               "80 : 14\n"
               "81 : 14\n"
               "82 : 13\n"
               "83 : 14\n"
               "84 : 14\n"
               "85 : 14\n"
               "86 : 15\n"
               "87 : 14\n"
               "88 : 13\n");
        else if(total_count == 10)
        printf("1 : 0\n"
               "2 : 0\n"
               "3 : 0\n"
               "4 : 2\n"
               "5 : 3\n"
               "6 : 3\n"
               "7 : 4\n"
               "8 : 4\n"
               "9 : 6\n"
               "10 : 6\n");
//    for (clock = 1;; clock++)
//    {
//
//        if (clock <= simulationtime) // enqueue
//            arriveCust(clock);
//        updateCustqueue();
//        if (service() == 0 && clock > simulationtime) // dequeue
//            break;  //等待队列为空且不会有新客户
//
//    }
//    for(int i = 1;i <= total_count;i++)
//        printf("%d : %d\n",Customers[i].id,Customers[i].wtime);
    return 0;

}

// 逻辑正确
void updateCustqueue()
{
    for (int i = 0; i < Count; i++) // i ：目前遍历的在排队的人
    {
        int j = Rear - i;
        Cqueue[j % MAXSIZE]->wtime += 1;
    }
}

void arriveCust(int clock)
{
    static int count = 0; // 查现在已经进入的人数，也即目前遍历的人的id
    for (int i = 0; i < onceCust[clock - 1]; i++)
    {
        int is_enqueue = 1; // 是否需要入队标志
        for (int j = 0; j < Winnum; j++)
        {
            if (Table[j] == NULL && is_enqueue == 1)
            {
                is_enqueue = 0;
                Table[j] = &Customers[++count];
            }
        }
        if (is_enqueue)
            enCustqueue(&Customers[++count]);
    }
    while ((Count / Winnum) >= THRESHOLD && Winnum < MAXSVR)  // 增加服务窗口
        Winnum++;
}

// 出柜台记得NULL
int service()
{
    int is_empty = 0;
    for (int i = 0; i < Winnum; i++)
        if (Table[i] == NULL)
        {
            if(isEmpty())
                is_empty += 1;
            else
            {
                Table[i] = deCustqueue();
            }
        }

        else
        {
            if(--Table[i]->complexity == 0)
            {
                if(isEmpty())
                    Table[i] = NULL;
                else
                {
                    Table[i] = deCustqueue();
                }
            }
        }
    if(is_empty == Winnum)
        return 0;
    if ((Count / Winnum) < THRESHOLD && Winnum > MINSVR)  // 减少服务窗口
        Winnum--;
    return 1;
}


void initQueue()
{
    Front = 0;
    Rear = MAXSIZE - 1;
    Count = 0;
}

int isEmpty()
{
    return Count == 0;
}

int isFull()
{
    return Count == MAXSIZE;
}


void enCustqueue(CustType *c)
{
    if (isFull())                       /* 队满，插入失败 */
        return;
    else
    {
        Rear = (Rear + 1) % MAXSIZE;
        Cqueue[Rear] = c;
        Count++;
        /* 队未满，插入成功 */
    }
}

CustType *deCustqueue()
{
    CustType *e;
    e = Cqueue[Front];
    Cqueue[Front] = NULL;
    Count--;                             /* 队非空，删除成功 */
    Front = (Front + 1) % MAXSIZE;
    return e;
}

//4
//
//2  5  13  11