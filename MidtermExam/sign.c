/**
  ******************************************************************************
  * @file           : sign.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/26
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NUM 64
#define MAX_LENGTH 64

char sign[MAX_NUM][MAX_LENGTH];
char str[256];

int now_i = 0;
int now_j = 0;

int cmp_function(const void *p1,const void *p2)
{
    char *a = (char *)p1;
    char *b = (char *)p2;
    int re = strcmp(a,b);
    if(re == 1)return -1;
    if(re == -1) return 1;
    return 0;
}

int main()
{
    char *p;
    int delete_num = 0;
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    gets(str);

    p = str;

    while (*p != ';')
    {
        if (isalnum(*p) || *p == '_')
            sign[now_i][now_j++] = *p;
        else if (strlen(sign[now_i]) != 0)
        {
            now_j = 0;
            now_i++;
        }
        p++;
    }
    now_i++;
    for (int i = 0; i < now_i; i++)
    {
        int flag = 0;
        int length = strlen(sign[i]);
        for (int j = 0; j < length; j++)
            if (isalpha(sign[i][j]))
                flag = 1;
        if (!flag) {memset(sign[i], 0, length);delete_num ++;}
    }

    for (int i = 0; i < now_i; i++)
        for (int j = 0; j < now_i; j++)
        {
            if (i == j)continue;
            if (strcmp(sign[i], sign[j]) == 0)
                if (strlen(sign[i]) != 0)
                {
                    int length = strlen(sign[j]);
                    memset(sign[j], 0, length);
                    delete_num ++;
                }
        }
    qsort(sign,now_i, MAX_LENGTH* sizeof(char),cmp_function);
    for(int i = 0; i < now_i-delete_num ;i++)
    {
        printf("%s ",sign[i]);
    }
    return 0;
}