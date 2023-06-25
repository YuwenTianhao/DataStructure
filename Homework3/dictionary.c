/**
  ******************************************************************************
  * @file           : dictionary.c
  * @author         : YuwenTianhao
  * @brief          : "5. 词频统计（数组或链表实现）"
  * @attention      : （该方法基于链表实现）最难的地方在于输入的处理
  *                   用指针遍历数组时一定小心不要报错！
  * @date           : 2023/3/29
  ******************************************************************************
  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "LinkedList.h"

void getWord();

int searchWord(char *w, List L);

void insertWord(List L, char *w);

/**
 * @brief 从文件中读取单词，并做转换
 * @note None
 * @param List L
 * @return None
 * @retval None
 */
void getWord(List L)
{
    FILE *Article = fopen("article.txt", "r");
    char Tmp[MAX_WORD] = "";
    while (fscanf(Article, "%s", Tmp) != EOF) // 以字符串读入Tmp
    {
        int length = strlen(Tmp);
        char *word = Tmp;
        for (int i = 0; i < length; i++)
        {
            if (isalpha(Tmp[i]) == 0)
                Tmp[i] = '\0';
            else if (Tmp[i] >= 'A' && Tmp[i] <= 'Z')
                Tmp[i] = Tmp[i] - 'A' + 'a';
        }
        do
        {
            if (*word == '\0')
                word++;
            else
            {
                if (searchWord(word, L) == 0)
                    insertWord(L, word);
                word += strlen(word);
            }
        } while (word - Tmp < length);
    }
}

int searchWord(char *w, List L)
{
    Position Ptr = First(L);
    while (Ptr != NULL)
    {
        if (strcmp(w, Ptr->word) == 0)
        {
            Ptr->count++;
            return 1;
        }
        Ptr = Ptr->Next;
    }
    return 0;
}

void insertWord(List L, char *w)
{
    Position Ptr = NULL;
    Ptr = First(L);
    Position Tmp = MakeNewNode();
    strcpy(Tmp->word, w);
    Tmp->count++;
    while (Ptr != NULL)
    {
        if (strcmp(w, Ptr->word) < 0)
        {
            Insert(Tmp, L, Ptr);
            return;
        }
        Ptr = Ptr->Next;
    }
    tailInsert(Tmp, L); // 和插入尾部和插入“NULL的前一个结点”是一个意思
}

void PrintList(List L)
{
    Position P = L->Next;
    while (P != NULL)
    {
        printf("%s %d\n", P->word, P->count);
        P = P->Next;
    }
}

int main()
{
    List WordTable = MakeNewList();
    getWord(WordTable);
    PrintList(WordTable);

    return 0;
}