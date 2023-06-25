/**
  ******************************************************************************
  * @file           : find.c
  * @author         : YuwenTianhao
  * @brief          : "1. 单词查找（查找-基本题）"
  * @attention      : 整个题只有最后一个哈希查找是难的，用链地址法解决冲突
  * @date           : 2023/5/24
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOTAL_NUM 3500
#define MAX_WORD_LENGTH 25
/* 以下为题目中给出的哈希表构建方法 */
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

char wordList[TOTAL_NUM][MAX_WORD_LENGTH]; // 构建单词表
int total_num = 0; // 读入单词总数
int indexList[256][2]; // 索引：indexList['a'][0]->起始位置;indexList['a'][1]->单词个数
struct Node; // 依靠链地址法的哈希表所需结构体（构建指针数组）
typedef struct Node *PtrToNode;
struct Node
{
    char word[MAX_WORD_LENGTH];
    PtrToNode Next;
};
PtrToNode HashTable[TOTAL_NUM];

/**
 * @brief 哈希插入函数
 * @note 该函数对于 unsigned int hash(char *str) 为字符串编码的哈希值，采用链地址法解决冲突
 * @param NWord : now word
 * @return None
 * @retval None
 */
void insertHash(char *NWord)
{
    unsigned int h = hash(NWord); // NWord 的哈希值
    PtrToNode Header = HashTable[h]; // 链表的头,需要小心当HashTable本身是NULL是赋值是失败的
    if (Header == NULL)
    {
        HashTable[h] = (PtrToNode)malloc(sizeof(struct Node));
        memset(HashTable[h],0,sizeof (struct  Node));
        strcpy(HashTable[h]->word,NWord);
        HashTable[h]->Next = NULL;
    }
    else
    {
        while (Header->Next != NULL)
            Header = Header->Next;
        Header->Next = malloc(sizeof(struct Node));
        Header = Header->Next;
        memset(Header,0,sizeof (struct  Node));
        strcpy(Header->word,NWord);
        Header->Next = NULL;
    }
}
// 返回result
int searchInHash(char *searching_word,int *cmp_times)
{
    unsigned int h = hash(searching_word);
    PtrToNode Header = HashTable[h];
    while (1)
    {
        if (Header == NULL)return 0;
        if (strcmp(Header->word, searching_word) == 0)
        {
            (*cmp_times)++;
            return 1;
        }
        else if (strcmp(Header->word, searching_word) < 0)
            (*cmp_times)++;
        Header = Header->Next;
    }
}

int HandleFunc()
{
    int method = 0; // 查找方式：具体如题所述
    char word[MAX_WORD_LENGTH] = ""; // 查找的单词
    int result = 0; // 查找结果：未查到 0 ； 查询成功 1
    int cmp_times = 0; // 比较次数
    if (scanf("%s%d", word, &method) == EOF)
        return 0;
    switch (method)
    {
        case 1:
        { // 顺序查找
            for (int i = 0; i < total_num; i++, cmp_times++)
            {
                if (strcmp(wordList[i], word) < 0)
                    continue;
                else if (strcmp(wordList[i], word) == 0)
                {
                    result = 1;
                    break;
                }
                else break;
            }
            cmp_times++; // 补全最后一次查找的比较
        }
            break;
        case 2:
        { // 二分查找
            int low = 0, high = total_num - 1, mid;
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (strcmp(word, wordList[mid]) == 0)
                {
                    cmp_times++;
                    result = 1;  /*  查找成功  */
                    break;
                }
                else if (strcmp(word, wordList[mid]) > 0)
                    low = mid + 1;            /*  准备查找后半部分 */
                else
                    high = mid - 1;           /* 准备查找前半部分 */
                cmp_times++;
            }
        }
            break;
        case 3:
        { // case 3 只是将二分查找换了一个 low 和 high
            int low = indexList[word[0]][0], high = low + indexList[word[0]][1] - 1, mid;
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (strcmp(word, wordList[mid]) == 0)
                {
                    cmp_times++;
                    result = 1;  /*  查找成功  */
                    break;
                }
                else if (strcmp(word, wordList[mid]) > 0)
                    low = mid + 1;            /*  准备查找后半部分 */
                else
                    high = mid - 1;           /* 准备查找前半部分 */
                cmp_times++;
            }
        }
            break;
        case 4:
            result = searchInHash(word,&cmp_times);
            break;
        default:
            break;
    }
    printf("%d %d\n", result, cmp_times);
    return 1;
}

int main()
{
    char buffer[MAX_WORD_LENGTH] = ""; // 读入的缓存器
    FILE *fp = fopen("dictionary3000.txt", "r");
    // 文件读入并处理
    while (~fscanf(fp, "%s", buffer)) // 绝对不能用 fgets(),会读入'\n'
    {
        indexList[buffer[0]][1]++; // 读入单词的首字母是索引
        for (int i = 0; buffer[i] != '\0'; i++)
            wordList[total_num][i] = buffer[i];
        // 构建Hash Table
        insertHash(buffer);
        total_num++;
    }
    // 构建单词索引表
    for (char i = 'a'; i < 'z'; i++)
        indexList[i + 1][0] = indexList[i][0] + indexList[i][1];
    // 开始处理
    while (HandleFunc());
    return 0;
}