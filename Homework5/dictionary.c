/**
  ******************************************************************************
  * @file           : dictionary.c
  * @author         : YuwenTianhao
  * @brief          : “2. 词频统计（树实现）”
  * @attention      : 树是我见过最强的数据结构了（4.27）
  *                   不过其经常卡循环，主要是递归很容易出错
  *                   此外还有树的插入或删除的赋值问题也不可小觑
  * @date           : 2023/4/27
  ******************************************************************************
  */

#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 256

typedef struct
{
    char name[100];
    int times;
} Word;


Word words[10000];
int words_ind;

char stop_words[10000][100];
int stop_words_ind;

void PrintTree(SearchTree T)
{
    if (T == NULL)return;
    PrintTree(T->Left);
    strcpy(words[words_ind].name, T->Element);
    words[words_ind].times = T->times;
    words_ind++;
    PrintTree(T->Right);
}

int cmp_function(const void *e1, const void *e2)
{
    Word *p1 = (Word *) e1;
    Word *p2 = (Word *) e2;
    if (p1->times != p2->times)
        return p2->times - p1->times;
    return strcmp(p1->name, p2->name);
}

int search_p(char p[])
{
    int i = 0;
    while (1)
    {
        if (strcmp(p, stop_words[i]) < 0)
            return 0;
        else if (strcmp(p, stop_words[i]) == 0)
            return 1;
        i++;
    }

}

int main()
{
    SearchTree T = NULL;
    FILE *Article = fopen("article.txt", "r");
    FILE *STOP = fopen("stopwords.txt", "r");
    while (~fscanf(STOP, "%s", stop_words[stop_words_ind]))
        stop_words_ind++;

    char Tmp[MAX_WORD_LENGTH] = "";
    while (fscanf(Article, "%s", Tmp) != EOF) // 以字符串读入Tmp
    {
        // 先使单词中的非字符都为'\0'且大写转小写，再找到第一个非0的字符为单词起始点，读入第一个单词后继续重复单词拆分
        // 例： “It's

        int length = strlen(Tmp);
        char *now_word = Tmp;
        for (int i = 0; i < length; i++)
        {
            if (isalpha(Tmp[i]) == 0)
                Tmp[i] = '\0';
            else if (Tmp[i] >= 'A' && Tmp[i] <= 'Z')
                Tmp[i] = Tmp[i] - 'A' + 'a';
        }
        // ‘ it s’，前有空格
        do
        {
            if (*now_word == '\0')
                now_word++;
            else
            {
                // 若不想结构体开太大，可以在这里改动，char *word;(struct words)
                // words[NumOfWords++].word = malloc( MAX_WORD_LENGTH * sizeof(char));
                char *p = NULL;
                p = malloc(MAX_WORD_LENGTH * sizeof(char));
                memset(p, 0, MAX_WORD_LENGTH * sizeof(char));
                memcpy(p, now_word, strlen(now_word));
                if (!search_p(p))
                    T = Insert(p, T);
                now_word += strlen(now_word);
            }
        } while (now_word - Tmp < length); // 防指针越界
    }
    PrintTree(T);
    qsort(words, words_ind, sizeof(Word), cmp_function);
    for (int i = 0; i < words_ind; i++)
        printf("%s:%d\n", words[i].name, words[i].times);
    return 0;
}