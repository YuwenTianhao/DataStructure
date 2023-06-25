#include<stdio.h>
#include<string.h>
#include "stdlib.h"
#include "ctype.h"

char CODE[26], INPUT[60];
char code_tmp[26];
int SIGN[26]; // 标记

void Set_code(void);//将剩余的密码部分填满
void Read_input(void);//依照输入填充密码最开始的部分
void reverse();

int main()
{
    gets(INPUT);
    Read_input();
    reverse();
    Set_code();
    for (int i = 0; i < 26; i++)
        printf("%c %c\n", i + 'a', CODE[i]);
    return 0;
    return 0;
}

void Read_input(void)
{
    for (int pInp = 0, pCod = 0; INPUT[pInp] != '\0'; pInp++)
    {
        if (isalpha(INPUT[pInp]))
        {
            if (INPUT[pInp] >= 'A' && INPUT[pInp] <= 'Z')
                INPUT[pInp] = INPUT[pInp] + 'a' - 'A';
            if (!SIGN[INPUT[pInp] - 'a'])//假如该字母未出现过，则将其标记，并填充至密码
            {
                SIGN[INPUT[pInp] - 'a'] = 1;
                code_tmp[pCod++] = INPUT[pInp];
            }
        }
    }
    return;
}

void reverse()
{
    int length = strlen(code_tmp);
    for (int i = 0; i < length; i++)
        CODE[i] = code_tmp[length - i - 1];
}

void Set_code(void)//倒序将未出现过的密码填充
{
    for (int pSig = 25, pCod = strlen(CODE); pSig >= 0; pSig--)
    {
        if (!SIGN[pSig])
        {
            CODE[pCod++] = pSig + 'a';
        }
    }
    return;
}
