/**
  ******************************************************************************
  * @file           : sort.c
  * @author         : YuwenTianhao
  * @brief          : “”
  * @attention      : 排序算法仍然是简单的冒泡（事实证明冒泡我也不太会写），算法排序效率低，另外每次输入都需要查验。（插入排序可能是最优解，既排除重复数据，不用再排序）
  *                   这道题目前看来，整体都可以改
  *                   有个最大问题在于，可以使用qsort，而qsort和strcmp是相辅相成的两个函数，会大大简化写的难度
  *                   虽然很不喜欢答案故意把它加上repeat表示重复次数，但是总体思路可以学习
  *                   答案还有一点不好，qsort直接排序了结构体，这个时间一下就上去了（后来看了一下，qsort是快速排序，比冒泡要好得多）
  *                   修改方向：
  *                   1、尽量把操作全放在插入时
  *                   2、简化排序写的步骤
  * @date           : 2023.03.09
  ******************************************************************************
  */
#include <stdio.h>
#include<string.h>

/**
* @brief 电话簿结构体
*/
typedef struct
{
    char name[20];
    char number[20];
} PhoneBook;

int total_num = 0; // 输入的数量
int real_num = 0; // 将重复数据去除后的数量
PhoneBook books[100];
PhoneBook *sorted_books[100]; // 排序时不改变 books的真实存储，而采用指针互换来排序

void rename_books();

void sort_books();

int dictionary_cmp(char *a_cmp, char *b_cmp);

int delete_books(char *tem_name, char *tem_number);

int main()
{

    scanf("%d", &total_num);
    for (int i = 0; i < total_num; i++)
    {
        char tem_name[20] = "";
        char tem_number[20] = "";
        scanf("%s %s", tem_name, tem_number);
        if (delete_books(tem_name, tem_number))
            continue;
        else
        {
            strcpy(books[real_num].name, tem_name);
            strcpy(books[real_num].number, tem_number);
            real_num++;
        }
    }
    rename_books();
    sort_books();
    for (int i = 0; i < real_num; i++)
    {
        if (sorted_books[i] != NULL)
            printf("%s %s\n", sorted_books[i]->name, sorted_books[i]->number);
    }
}

/**
 * @brief 在输入时判断是否应该不取该数值
 * @note None
 * @param *tem_name
 * @param *tem_number
 * @return if the new-input-book needs to be deleted
 * @retval 1 : yes ; 0 : no
 */

int delete_books(char *tem_name, char *tem_number)
{
    int delete_i = 0;
    for (delete_i = 0; delete_i < real_num; delete_i++)
    {
        if (strcmp(books[delete_i].name, tem_name) == 0)
            if (strcmp(books[delete_i].number, tem_number) == 0)
                return 1;
    }
    return 0;
}

/**
 * @brief 重命名结构体 ->name
 * @note 调用全局变量 ： books, real_num.  逐次比较，效率较低
 * @param None
 * @return if the new-input-book needs to be deleted
 * @retval 1 : yes ; 0 : no
 *
 */

void rename_books()
{
    int cmp_i = 0;
    int cmp_j = 0;
    int repeat_num = 0;
    char *repeat[10];
    for (cmp_i = 0; cmp_i < real_num - 1; cmp_i++)
    {
        for (cmp_j = cmp_i + 1; cmp_j < real_num; cmp_j++)
        {
            if (strcmp(books[cmp_i].name, books[cmp_j].name) == 0)
                if (strcmp(books[cmp_i].number, books[cmp_j].number) != 0)
                {
                    repeat[repeat_num] = books[cmp_j].name;
                    repeat_num += 1;
                }
        }
        for (int i = 0; i < repeat_num; i++)
        {
            if (repeat[i] != NULL)
            {
                char ch_i = i + '0' + 1;
                char suffix[10] = "_";
                suffix[1] = ch_i;
                strcat(repeat[i], suffix);
            }
        }
        repeat_num = 0;
        memset(repeat, NULL, sizeof(repeat));
    }
}

/**
 * @brief 用冒泡排序对名字按字典序排序，没有真正修改books，而是交换了指针的顺序
 * @note 效率低，但是采用指针会较好
 * @param None
 * @return None
 * @retval None
 */

void sort_books()
{
    int cmp_i = 0;
    int cmp_j = 0;
    for (int i = 0; i < real_num; i++)
        sorted_books[i] = &books[i];
    for (cmp_i = 0; cmp_i < real_num - 1; cmp_i++)
    {
        for (cmp_j = 0; cmp_j < real_num - 1 - cmp_i; cmp_j++)
        {
            if (dictionary_cmp(sorted_books[cmp_j], sorted_books[cmp_j + 1]) == -1)
            {
                PhoneBook *tem;
                tem = sorted_books[cmp_j];
                sorted_books[cmp_j] = sorted_books[cmp_j + 1];
                sorted_books[cmp_j + 1] = tem;
            }
        }
    }
}

/**
 * @brief 按字典序比较两个字符串
 * @note <string.h>
 * @param a_cmp
 * @param b_cmp
 * @return 输出类似 strcmp() 的结果
 * @retval 0 : equal
 * @retval 1 : a > b (higher priority)
 * @retval -1 : b > a
 */
int dictionary_cmp(char *a_cmp, char *b_cmp)
{
    // equal situation
    if (strcmp(a_cmp, b_cmp) == 0)
        return 0;
    while (1)
    {
        if (a_cmp == NULL || b_cmp == NULL)
        {
            if (a_cmp == NULL)
                return 1;
            else return -1;
        }
        if (*a_cmp > *b_cmp)
            return -1;
        else if (*b_cmp > *a_cmp)
            return 1;
        a_cmp++;
        b_cmp++;
    }
}