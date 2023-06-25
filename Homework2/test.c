#include<stdio.h>
#include "string.h"

void func(char *q)
{
    char c = 'c';
    q = &c;
}

int main()
{
    char *p ;
    func(p);
    puts(p);
}