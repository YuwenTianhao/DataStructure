/**
  ******************************************************************************
  * @file           : encode.c
  * @author         : YuwenTianhao
  * @brief          : 4. 文件加密（环）
  * @attention      : 简单而又复杂的一道题，做对了很简单，debug很困难（数据量太大）
  * @date           : 2023/4/2
  ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

#define MAX 256

char key[MAX]; // 字符加密Hash Table
char str[MAX]; // 加密密钥
int used[MAX]; // 记录密钥重复字母

Position cycle_times(Position P, int times);
void encode(List L);
/**
 * 加密函数
 * @param L ：加密环
 */
void encode(List L)
{
    Position now = First(L);
    char first = First(L)->ch;
    while (now->Next != now)
    {
        int times = (int) now->ch;
        Position next = now->Next;
        Delete(now, now);
        next = cycle_times(next, times - 1);
        key[times] = next->ch;
        now = next;
    }
    key[now->ch] = first;
}
/**
 * 按 times 遍历循环链表
 * @param P
 * @param times
 * @return Position next
 */
Position cycle_times(Position P, int times)
{
    while (times--)
        P = P->Next;
    return P;
}

int main()
{
    int pst = 0; // HashTable当前最末位
    char ch = 0; // 文件读取字符
    FILE *in, *out;
    List L = MakeNewList(); // 加密环
    in = fopen("in.txt", "r");
    out = fopen("in_crpyt.txt", "w+");
    gets(str); // gets会使最后没有'\n'
    // 先制作一个加密数组
    for (int i = 0; str[i]; i++)
    {
        char p = str[i];
        if (!used[p])
        {
            key[pst++] = p;
            used[p] = 1;
        }
    }
    for(char tem = 32;tem <= 126;tem++ ){
        if(!used[tem])
            key[pst++] = tem;
    }
    // 制作加密环
    for (int i = 0; i < 95; i++)
    {
        Position Tmp = MakeNewNode();
        Tmp->ch = key[i];
        tailInsert(Tmp, L);
    }
    Last(L)->Next = First(L);
    encode(L);
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch >= 32)
            ch = key[ch];
        fputc(ch, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}