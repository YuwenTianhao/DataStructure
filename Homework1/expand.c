#include "stdio.h"
#include "string.h"
char in_line[100];
char expand[100];
char *check;
char *result_p;

int judge_alnum(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    else if (ch >= 'a' && ch <= 'z')
        return 2;
    else if (ch >= 'A' && ch <= 'Z' )
        return 3;
    else
        return 0;
}

void expand_fuction(char *now_check,char *now_result)
{
    char *front = now_check;
    char *back = now_check;
    front--;
    back++;
    if(judge_alnum(front[0]))
    {
        if(judge_alnum(front[0]) == judge_alnum(back[0]))
        {
            if(back[0] > front[0])
                while (1)
                {
                    *now_result = *(now_result - 1) + 1;
                    if(*now_result == back[0])
                        return;
                    now_result++;
                }
        }
    }
    *now_result = *now_check;
    now_result++;
    *now_result = *back;
}

int main()
{
    while (gets(in_line)!=NULL)
    {
        check = in_line;
        result_p = expand;
        while (*check != '\0')
        {
            if(*check == '-')
            {
                expand_fuction(check,result_p);
                while (*result_p != '\0')
                    result_p++;
                result_p--;
            }
            else
            {
                *result_p = *check;
                result_p++;
            }
            check++;
        }
        puts(expand);
        memset(expand,0,sizeof(expand));
    }
}