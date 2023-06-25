/**
  ******************************************************************************
  * @file           : books.c
  * @author         : YuwenTianhao
  * @brief          : “5. 小型图书管理系统”
  * @attention      : 这道题是结构体和链表的绝佳练习平台。1、下划线字符参加排序 2、图书不会重名
  *                   排序方法选择了插入排序，非常合适。
  *                   这道题目要好好的总结一下，这是第一道我做的稍微比较大型的题目，错误原因有两点，需要特别注意：
  *                   1、最低级错误：输出txt名字写错了，下次不能再犯
  *                   2、链表的每一个函数都会出错！要特别考虑出错时候的情况，不能想当然
  *
  *                   错误具体是：
  *                   当"books.txt"第一个本来就是最高位顺序时，排序会自动给它放到最后一个
  *                   错误原因是：
  *                   顺次比较链表会返回正确的元素位置或由于遍历结束链表的最后一个值，但最后一个值并不一定是没找到才返回的！
  *                   有可能是正确的。改进方法可以有两种：
  *                   1、返回回来最后一个再检查一下，是不是因为没找到才返回的
  *                   2、直接返回NULL
  *
  *                   还有一个小问题
  *                   当使用malloc来生成一个新的链表，并且不能完全确定它的所有值的时候，一定要memset清零！（或者专门做一个初始化函数）
  * @date           : 2023/3/17
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "books.h"

#define BUFFERMAX 128 // 最大缓存区

/**
* @brief 图书信息结构体
*/
struct Book
{
    char Name[50];
    char Author[20];
    char Press[30];
    char Date[10];
    Position Next;
};

/**
 * @brief 插入排序
 * @note 出现问题最多的地方，插入排序不可小觑
 * @param Position newBook, ListBook LBook
 * @return None
 * @retval None
 */
void InsertionSort(Position newBook, ListBook LBook)
{
    Position oldBook = LBook;
    if (Header(LBook)->Next == NULL) // 若只有一个Header，则将结构体直接加入
    {
        Header(LBook)->Next = newBook;
        return;
    }
    oldBook = oldBook->Next;
    // 这里的条件判断是写得极丑的，可以说每个多加的条件都是自己debug出来的，插入排序还是需要整体学一下
    while(dictionary_cmp(newBook->Name,oldBook->Name) < 0 && oldBook->Next !=NULL)
    {
        oldBook = oldBook->Next;
    }
    if(dictionary_cmp(newBook->Name,oldBook->Name) < 0)
        Insert_Book(newBook,oldBook->Next,LBook);
    else
        Insert_Book(newBook,oldBook,LBook);
}

/**
 * @brief 根据操作（op = 1,2,3）和内容(content[])，来执行具体操作的上层封装
 * @note None
 * @param int op, char *content,ListBook LBook
 * @return None
 * @retval None
 */
void Options(int op, char *content, ListBook LBook)
{
    switch (op)
    {
        case 1:
        {
            Position newBook = malloc(sizeof(struct Book));
            initTable(newBook);
            sscanf(content, "%s%s%s%s", newBook->Name, newBook->Author, newBook->Press, newBook->Date);
            InsertionSort(newBook, LBook);
        }
            break;
        case 2:
        {
            Position NowBook;
            NowBook = Find(content, LBook);
            while (NowBook != NULL)
            {
                printf("%-50s%-20s%-30s%-10s\n", NowBook->Name, NowBook->Author, NowBook->Press, NowBook->Date);
                NowBook = Find(content, NowBook);
            }
        }
            break;
        case 3:
        {
            while (Delete_Book(content, LBook) != 0);
        }
            break;
        default:
            break;
    }
}

/**
* @brief 链表底层操作函数
*/

// 插入函数涉及到，是将该位置后移再插入，还是在该位置后插入，最好每次自己写
void Insert_Book(Position newBook, Position P, ListBook L)
{
    Position Pre = FindPrevious(P, L);
    Pre->Next = newBook;
    newBook->Next = P;
}

// 同样也建议自己写，比如这个函数就会return特定的值来判断是否删除成功
int Delete_Book(char *name, ListBook L)
{
    Position P = Find(name, L);
    Position Pre = FindPrevious(P, L);
    if (P != NULL)
    {
        Pre->Next = P->Next;
        free(P);
        return 1;
    }
    return 0;
}

// 下面是比较基本的操作函数，不太建议自己写
Position Find(char *name, ListBook L)
{
    Position P;
    P = L->Next;
    while (P != NULL && strstr(P->Name, name) == NULL)
    {
        P = P->Next;
    }
    return P;
}

Position FindPrevious(Position P, ListBook L)
{
    Position Pre = L;
    while (Pre->Next != NULL && Pre->Next != P)
    {
        Pre = Pre->Next;
    }
    return Pre;
}

Position Header(ListBook L)
{
    return L;
}

void initTable(Position P)
{
    memset(P, 0, sizeof(struct Book));
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


int main()
{
    ListBook LBook; // 生成一个链表结构
    LBook = malloc(sizeof(struct Book)); // 生成一个header
    Position NowBook = LBook;
    initTable(LBook);
    int command;
    char query[BUFFERMAX] = "";
    // 文件操作
    FILE *Book_txt, *Order_txt;
    Book_txt = fopen("books.txt", "r");
    Order_txt = fopen("ordered.txt", "w");

    // 初始化保存
    while (!feof(Book_txt))
    {
        char in_line[BUFFERMAX] = ""; // 每行输入
        fgets(in_line, BUFFERMAX, Book_txt); // gets() 不读取 '\n'而替换为 '\0', fgets() 读取‘\n'
        Position newBook = malloc(sizeof(struct Book));
        initTable(newBook);
        sscanf(in_line, "%s %s %s %s", newBook->Name, newBook->Author, newBook->Press, newBook->Date);
        InsertionSort(newBook, LBook);
    }
    // 按指令操作
    while (1)
    {
        scanf("%d", &command);
        if (command == 0)
            break;
        getchar();
        gets(query);
        Options(command, query, LBook);
    }
    // 最终输出
    while (1)
    {
        if (NowBook->Next == NULL)
            break;
        NowBook = NowBook->Next;
        fprintf(Order_txt, "%-50s%-20s%-30s%-10s\n", NowBook->Name, NowBook->Author, NowBook->Press, NowBook->Date);
    }
    fclose(Book_txt);
    fclose(Order_txt);
    return 0;
}