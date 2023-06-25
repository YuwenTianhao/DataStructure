/**
  ******************************************************************************
  * @file           : login.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/8
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
    int ID; // 学号
    char name[15]; // 姓名
    int machine; //机器号
    char login_time[6]; // 登录时间
} LoginMessage;

LoginMessage LM[300];

int cmp_function(const void *p1, const void *p2)
{
    LoginMessage *a = (LoginMessage *) p1;
    LoginMessage *b = (LoginMessage *) p2;
    if (a->ID > b->ID)return 1;
    if (a->ID < b->ID)return -1;
    return strcmp(a->login_time, b->login_time);
}

int main()
{
    int login_num = 0;
    int now_ID = 0;
    int now_machine = 0;
    char now_name[15] = "";
    int now_flag = 0;
    scanf("%d", &login_num);
    for (int i = 0; i < login_num; i++)
        scanf("%d %s %d %s", &LM[i].ID, LM[i].name, &LM[i].machine, LM[i].login_time);

    qsort(LM, login_num, sizeof(LoginMessage), cmp_function);
    for (int i = 0; i < login_num; i++)
    {
        if (LM[i].ID == now_ID)
        {
            if (now_flag == 0)
            {
                if (now_machine != LM[i].machine)
                {
                    printf("%d %s\n", now_ID, now_name);
                    now_flag = 1;
                }
            }
        }
        else
        {
            now_ID = LM[i].ID;
            strcpy(now_name, LM[i].name);
            now_machine = LM[i].machine;
            now_flag = 0;
        }
    }
    return 0;
}