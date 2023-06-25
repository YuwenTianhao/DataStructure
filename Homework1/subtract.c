// coding by Yuwen Tianhao
#include "stdio.h"
#include "string.h"

char input_a[100];
char input_b[100];
char a_num[100];
char b_num[100];
char sub[100];

void pretreatment()
{
    char *non_zero = input_a;
    while (*non_zero == '0')
        non_zero++;
    strcat(a_num,non_zero);
    non_zero = input_b;
    while (*non_zero == '0')
        non_zero++;
    strcat(b_num,non_zero);
}

int cmp_num()
{
    if (strlen(a_num) > strlen(b_num))
        return 1;
    else if (strlen(a_num) < strlen(b_num))
        return  -1;
    else
    {
        int i = 0;
        while (a_num[i] != '\0')
        {
            if(a_num[i] > b_num[i])
                return 1;
            else if(b_num[i] > a_num[i])
                return -1;
            else
            {
                i++;
            }
        }
    }
    return 0;
}

void reverse()
{
    char *end;
    char *start;
    // reverse a_num[]
    end = a_num;
    while (*end != '\0')
        end ++;
    end --;
    for(start = a_num;end > start ;end--,start++)
    {
        char tem;
        tem = *start;
        *start = *end;
        *end = tem;
    }
    // reverse b_num[]
    end = b_num;
    while (*end != '\0')
        end ++;
    end --;
    for(start = b_num;end > start ;end--,start++)
    {
        char tem;
        tem = *start;
        *start = *end;
        *end = tem;
    }

}

void borrow(char *sub_p)
{
    while(1)
    {
        sub_p += 1;
        if(*sub_p > '0')
            break;
        *sub_p = '9';
    }
    *sub_p -= 1;
}

void long_subtraction()
{
    char *a_now;
    char *b_now;
    char *end;
    char *result = sub;
    if(cmp_num() > 0)
    {
        a_now = a_num;
        b_now = b_num;
        end = a_num;
        while (*end != '\0')
            end++;
        end--;
    }
    else
    {
        a_now = b_num;
        b_now = a_num;
        end = b_num;
        while (*end != '\0')
            end++;
        end--;
    }

    while (1)
    {
        if(*a_now >= *b_now)
        {
            if(*b_now == '\0')
                *result = *a_now;
            else
                *result = *a_now - *b_now + '0';
        }

        else
        {
            borrow(a_now);
            *result = *a_now + 10 - *b_now + '0';
        }
        result ++;
        a_now ++;
        b_now ++;
        if(a_now == end)
        {
            if(*a_now >= *b_now)
            {
                if(*b_now == '\0')
                    *result = *a_now;
                else
                    *result = *a_now - *b_now + '0';
            }
            else
            {
                borrow(a_now);
                *result = *a_now + 10 - *b_now + '0';
            }
            break;
        }
    }
}

int main()
{
    gets(input_a);
    gets(input_b);
    pretreatment();
    reverse();
    long_subtraction();
    if (strcmp(a_num, b_num) == 0)
    {
        printf("0\n");
        return 0;
    }
    else
    {
        char *end = sub;

        while (*end != '\0')
            end++;
        while (*end == '0' || *end == '\0')
            end--;

        if(cmp_num() < 0)
        {
            printf("-");
        }
        while (1)
        {
            printf("%c",*end);
            if(end == sub)
            {
                break;
            }
            end--;
        }
    }
}