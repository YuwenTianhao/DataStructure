/**
  ******************************************************************************
  * @file           : outputf.c
  * @author         : YuwenTianhao
  * @brief          : 格式控制输入输出，期中模拟题
  * @attention      : 十分钟胡乱写的
  * @date           : 2023/4/20
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char str[300];
char gar[300];
int state;

int main(){
    int m,n;
    char tem;
    getchar();
    tem = getchar();
    if(tem == '-')
        state  = 1;
    else ungetc(tem,stdin);
    scanf("%d:%dS",&m,&n);
    gets(gar);
    gets(str);
    if(m < strlen(str))
    {
        str[m] = '\0';
    }
    else m = strlen(str);
    if(state)
    {
        for(int j = 0; j < n - m;j++)
            printf("#");
        printf("%s",str);
    }
    else
    {
        printf("%s",str);
        for(int j = 0; j < n - m;j++)
            printf("#");
    }
    printf("\n");
    return 0;
}