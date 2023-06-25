/**
  ******************************************************************************
  * @file           : replace.c
  * @author         : YuwenTianhao
  * @brief          : "2. 字符串替换（新）"
  * @attention      : 这道题就是字符串替换 + 文件输入输出，但是加入条件：大小写不区分 —— 使得我们必须自己写一个查找函数（不得不说，如果需要现场写的话，debug可能还真挺烦）
  *                   答案学习：
  *                   答案的函数简洁程度真的惊到了，归根结底在于离散数学，对判断的逻辑“不敏感”，较多的使用 if else，贴近自然语言而不是与或非的逻辑语言
  *                   但是说实话，这道题我的思路也很不错，更简明易懂
  * @date           : 2023/3/10
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>

#define BUFFERMAX 1024 // 最大缓存区

char origin[100]; // 被替代单词
char replace[100]; // 替代单词

int judgeSame(char a_j, char b_j);

char *myStrstr(char *str1, char *str2);

int main()
{
    FILE *IN; // 输入文件指针
    FILE *OUT; // 输出文件指针
    gets(origin);
    gets(replace);
    IN = fopen("filein.txt", "r");
    OUT = fopen("fileout.txt", "w");
    while (!feof(IN)) // feof() : 检测到文件末尾，返回非 0 值，否则返回 0 值
    {
        char in_line[BUFFERMAX] = ""; // 每行输入
        char out_line[BUFFERMAX] = ""; // 每行输出
        char *re = NULL; // 用来存储 myStrstr 查找结果
        char *now = NULL; // 用指针代替inline，可以移动
        fgets(in_line, BUFFERMAX, IN);
        now = in_line;
        while (1)
        {
            re = myStrstr(now, origin);
            if (re != NULL)
            {
                int length = re - now;
                strncat(out_line, now, length); // re前复制
                strncat(out_line, replace, strlen(replace)); // 替换词
                now = re + strlen(origin); // 重定向
            }
            else
            {
                strcat(out_line, now);
                break;
            }
        }
        fputs(out_line, OUT);
    }
    fclose(IN);
    fclose(OUT);
    return 0;
}

/**
 * @brief 判断两个字符是否相等（忽略大小写区别）
 * @note None
 * @param a_j, b_j ：判断的两个数
 * @return 是否相等
 * @retval 1 ： equal 0: different
 */
 // 修改后降低了判断能力，有可能会有意料不到的bug，但是简单得多
int judgeSame(char a_j, char b_j)
{
    return a_j == b_j || a_j == b_j - 32 || a_j == b_j + 32;
}
// 下面为未修改前的
//int judgeSame(char a_j, char b_j)
//{
//    if (a_j >= 'a' && a_j <= 'z')
//    {
//        if (b_j >= 'a' && b_j <= 'z')
//            return a_j == b_j;
//        else if (b_j >= 'A' && b_j <= 'Z')
//            return a_j == (b_j - 'A' + 'a');
//        return 0;
//    }
//    else if (a_j >= 'A' && a_j <= 'Z')
//    {
//        if (b_j >= 'a' && b_j <= 'z')
//            return a_j == (b_j + 'A' - 'a');
//        else if (b_j >= 'A' && b_j <= 'Z')
//            return a_j == b_j;
//        return 0;
//    }
//    else
//        return a_j == b_j;
//}

/**
 * @brief 判断字符串中是否包含子字符串（忽略大小写）
 * @note None
 * @param *str1 : 母字符串, *str2 : 子字符串
 * @return 包含的母字符串指针位置
 * @retval char * : 包含的母字符串指针位置, NULL : 不包含
 */
char *myStrstr(char *str1, char *str2)
{
    char *s1 = str1;
    char *s2 = str2;
    char *p = str1;
    while (*p != '\0')
    {
        s1 = p;
        s2 = str2;
        while (*s1 != '\0' && *s2 != '\0' && judgeSame(*s1, *s2))
        {
            s1++;
            s2++;
        }
        if (*s2 == '\0')
            return (char *) p;
        p++;
    }
    return NULL;
}