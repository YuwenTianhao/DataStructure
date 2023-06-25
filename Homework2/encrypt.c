/**
  ******************************************************************************
  * @file           : encrypt.c
  * @author         : YuwenTianhao
  * @brief          : "3. 加密文件"
  * @attention      : 这道题没有什么含量，最难的部分是查找，但由于是顺序对应，可以用一个数组假装 hashtable，反而把题变简单了
  *                   答案学习：
  *                   1、表扬自己，用数组存放的方式是最正确的
  *                   2、答案写法的简明程度总是令人发指
  * @date           : 2023/3/10
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>

#define c_encrypt(c) Hash_table[(c - 'a')] // 宏定义：小写字母转int

char Hash_table[30] = ""; // 与加密内容形成一一对应
char en_word[30] = "";

void encryptHash();

int main()
{
    FILE *IN;
    FILE *OUT;
    scanf("%s", en_word);
    encryptHash(); // 形成编码对应表
    while (1)
    {
        char buf_ch = '\0';
        buf_ch = (char) fgetc(IN);
        if (feof(IN))
        {
            break;
        }
        if (buf_ch >= 'a' && buf_ch <= 'z')
            fputc(c_encrypt(buf_ch), OUT);
        else
            fputc(buf_ch, OUT);
    }
    fclose(IN);
    fclose(OUT);
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
        while (1)
        {
            if (*check == '\0')
                break;
            if (en_word[i] == *check)
                flag = 0;
            check++;
        }
        if (flag == 1)
        {
            *check = en_word[i];
        }
    }
    for (int i = 0; i < 26; ++i)
    { // 将反向字母表加入后部，过程类似上面
        char *check = Hash_table;
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
//    答案给出的方法：
//    for(i = 0; str[i]; i++) {
//    p = str[i];
//    if(!used[p - 'a']) {
//    key[pst++] = p;
//    used[p - 'a'] = 1;
//    }
//    }
//    for(p = 'z'; p >= 'a'; p--) {
//    if(!used[p - 'a'])
//    key[pst++] = p;
//    }