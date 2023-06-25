/**
  ******************************************************************************
  * @file           : same.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/18
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
    char number[12]; // 手机号
    char base; // 基站类型
    int in_time;
    int out_time;
} LoginMessage;

LoginMessage LM[1001];
LoginMessage search_record[1001];
LoginMessage print_record[1001];

int cmp_string_des(const void *e1, const void *e2)
{
    LoginMessage *p1 = (LoginMessage *) e1;
    LoginMessage *p2 = (LoginMessage *) e2;
    return strcmp(p2->number, p1->number);
}

int main()
{
    int n; // 信息条数
    int total_num;
    char search_number[11] = "";
    int m = 0;
    int k = 0;
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    total_num = n;
    for (int i = 0; i < n; i++)
        scanf("%s %c %d %d", LM[i].number, &LM[i].base, &LM[i].in_time, &LM[i].out_time);
    scanf("%s", search_number);

    for (int i = 0; i < total_num; i++)
        if (memcmp(LM[i].number, search_number, 12) == 0)
        {
            strcpy(search_record[m].number, search_number);
            search_record[m].base = LM[i].base;
            search_record[m].in_time = LM[i].in_time;
            search_record[m].out_time = LM[i].out_time;
            m++;
//            printf("%s %c %06d %06d\n",LM[i].number,LM[i].base,LM[i].in_time,LM[i].out_time);
        }
//    printf("\n");
    qsort(LM, total_num, sizeof(LoginMessage), cmp_string_des);
    for (int i = 0; i < total_num; i++)
        for (int j = 0; j < m; j++)
        {
            if (strcmp(LM[i].number, search_number) != 0)
            {
                if (LM[i].base == search_record[j].base)
                    if (LM[i].in_time <= search_record[j].out_time && LM[i].out_time >= search_record[j].in_time)
                    {
                        int flag = 1;
                        for (int w = 0; w < k; w++)
                            if (memcmp(LM[i].number, print_record[w].number, 11) == 0 &&
                                print_record[w].base == LM[i].base)
                                flag = 0;
                        if (flag)
                        {
                            strcpy(print_record[k].number, LM[i].number);
                            print_record[k].base = LM[i].base;
                            print_record[k].in_time = LM[i].in_time;
                            print_record[k].out_time = LM[i].out_time;
                            k++;
                        }
                    }
            }
        }
    for(int i = 0 ; i < k;i++)
        printf("%s %c\n",print_record[i].number,print_record[i].base);
    return 0;
}