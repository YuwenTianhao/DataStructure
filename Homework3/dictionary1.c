/**
  ******************************************************************************
  * @file           : dictionary1.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : 基于数组实现 可选择：二分查找+插入排序 或 qsort+删除重复（插入排序重点是插入，数组不适合实现）
  * @date           : 2023/4/24
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 256
#define MAX_WORD_LENGTH 256

typedef struct
{
    char word[MAX_WORD_LENGTH]; // 单词
    int times; // 次数
} WordsStruct;
WordsStruct words[MAX_WORDS];
int NumOfWords; // 用于二分查找

/**
* @brief 二分查找，非递归实现：排序从小到大
*/
//int searchElem(char *now_word)
//{
//    int low=0, high=NumOfWords-1, mid;
//    while(low <= high){
//        mid = (high + low) / 2;
//        if((strcmp(now_word,words[mid].word) < 0))
//            high = mid - 1;
//        else if (strcmp(now_word,words[mid].word)>0)
//            low = mid + 1;
//        else
//            return (mid);
//    }
//    return -1;
//}

int cmp_function(const void *p1, const void *p2)
{
    WordsStruct *a = (WordsStruct *) p1;
    WordsStruct *b = (WordsStruct *) p2;
    return strcmp(a->word, b->word);
}

void getWord()
{
    FILE *Article = fopen("article.txt", "r");
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
                words[NumOfWords].times = 1;
                memcpy(words[NumOfWords++].word, now_word, strlen(now_word));
                now_word += strlen(now_word);
            }
        } while (now_word - Tmp < length); // 防指针越界
    }
    qsort(words, NumOfWords, sizeof(WordsStruct), cmp_function);
}

void DelRepeat()
{
    for (int i = 0; i < NumOfWords - 1; i++)
    {
        if (strcmp(words[i].word, words[i + 1].word) == 0)
        {
            words[i + 1].times += words[i].times;
            words[i].times = 0;
        }
    }
    qsort(words, NumOfWords, sizeof(WordsStruct), cmp_function);
}

int main()
{
    getWord();
    DelRepeat();
    for (int i = 0; i < NumOfWords; i++)
        if (words[i].times != 0)
            printf("%s %d\n", words[i].word, words[i].times);
    return 0;
}