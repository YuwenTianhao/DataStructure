/**
  ******************************************************************************
  * @file           : key.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/4/27
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "ctype.h"

#define c_encrypt(c) Hash_table[(c - 'a')] // 宏定义：小写字母转int

char transform(char p)
{
    if (p >= 'A' && p <= 'Z')return p - 'A' + 'a';
    return p;
}


char Hash_table[30] = ""; // 与加密内容形成一一对应
char en_word[30] = "";
int unused[30];
char Hash_table_true[30] = "";

void encryptHash();

int main()
{
    scanf("%s", en_word);
    encryptHash(); // 形成编码对应表
    for (int i = 0; i < 26; i++)
        printf("%c %c\n", i + 'a', Hash_table_true[i]);
    return 0;
}

/**
 * @brief 对应特征词给HashTable赋值，先删除重复character，后将单词表反序追加
 * @note 使用全局变量 char *Hash_table, en_word;
 * @param None
 * @return None
 * @retval None
 */
void encryptHash()
{
    int en_len = (int) strlen(en_word);
    char a_z[26] = ""; // 构造反向字母表
    for (int i = 0; i < 26; ++i)
    {
        a_z[i] = 'z' - i;
    }
    for (int i = 0; i < en_len; ++i)
    { // 将删除后的特征词加入Hash的头部
        char *check = Hash_table;
        int flag = 1; // 记录是否有重复数据
        char now = transform(en_word[i]);
        while (1)
        {
            if (*check == '\0')
                break;
            if (isalpha(now) == 0)
                flag = 0;
            if (now == *check)
                flag = 0;
            check++;
        }
        if (flag == 1)
        {
            if(isalpha(now))
                *check = now;
        }
    }
    int length = strlen(Hash_table);
    for (int i = 0; i < length; i++)
        Hash_table_true[i] = Hash_table[length - i - 1];
    for (int i = 0; i < 26; ++i)
    { // 将反向字母表加入后部，过程类似上面
        char *check = Hash_table_true;
        int flag = 1; // 记录是否有重复数据
        while (1)
        {
            if (*check == '\0')
                break;
            if (a_z[i] == *check)
                flag = 0;
            check++;
        }
        if (flag == 1)
            *check = a_z[i];
    }

}
