/**
  ******************************************************************************
  * @file           : test.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/5/28
  ******************************************************************************
  */

#include "stdio.h"

#define NHASH  3001
#define MULT  37

unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}

int main()
{
    printf("%d %d %d", hash("wins"), hash("physics"), hash("physics\n"));
}