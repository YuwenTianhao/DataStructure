/**
  ******************************************************************************
  * @file           : run.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/17
  ******************************************************************************
  */

#include "run.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define IS_END_OF_SENTENCE(c) ((c) == '\0' || (c) == '\r' || (c) == '\n')

SearchTree Root;

int winner_element = 0;
int winner_times = 10000;

/**
 * @brief 中缀后缀生成树
 * @note 关键在于 表达式的读取 和 递归的逻辑
 * @param char infix_exp[], char post_exp[], SearchTree T
 * @return SearchTree Root
 * @retval 返回根节点
 */
SearchTree insertTree(char infix_exp[], char post_exp[], SearchTree T)
{
    // 分配空间
    T = malloc(sizeof(struct TreeNode));
    memset(T, 0, sizeof(struct TreeNode));

    char *post = post_exp; // 后标
    int index_in_infix = 0; // 存放Root在infix_expr中的下标
    char left_infix[100] = "", left_post[100] = "", right_post[100] = ""; // 用于递归的表达式
    char T_element[100] = ""; // Root节点(T->Element)的表达式形式

    //  如果已经没有语句，则不递归
    if (IS_END_OF_SENTENCE(infix_exp[0]) || infix_exp[0] == ' ')
        return NULL;
    // 尾指针回到最后一个数字的数组下标：逻辑较为复杂
    while (!IS_END_OF_SENTENCE(*post))post++;
    do post--;
    while (!isdigit(*post));
    while (isdigit(*post))post--;
    post++;
    // int和char型转换
    T->Element = atoi(post);
    itoa(T->Element, T_element, 10);

    // 将语句分开
    for (; memcmp(infix_exp + index_in_infix, T_element, strlen(T_element)) != 0; index_in_infix++)
    {
        left_infix[index_in_infix] = infix_exp[index_in_infix];
        left_post[index_in_infix] = post_exp[index_in_infix];
    }
    for (int i = index_in_infix; memcmp(post_exp + i, T_element, strlen(T_element)) != 0; i++)
        right_post[i - index_in_infix] = post_exp[i];

    // 递归
    T->Left = insertTree(left_infix, left_post, T->Left);
    T->Right = insertTree(infix_exp + index_in_infix + strlen(T_element) + 1, right_post, T->Right);
    return T;
}

// 先序遍历维护最短路径
void preOrderTraversal(SearchTree T, int height)
{
    if (T == NULL)return;
    height++;
    if (T->Left == NULL && T->Right == NULL)
    {
        if (height < winner_times)
        {
            winner_element = T->Element;
            winner_times = height;
        }
        else if(height == winner_times)
        {
            if(T->Element < winner_element)
            {
                winner_element = T->Element;
                winner_times = height;
            }
        }
    }
    else
    {
        preOrderTraversal(T->Left, height);
        preOrderTraversal(T->Right, height);
    }
}

int main()
{
    char infix_exp[1000] = "";
    char post_exp[1000] = "";
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    while (fgets(infix_exp, 1000, stdin) != NULL)
    {
        if (IS_END_OF_SENTENCE(infix_exp[0]))break; // 保险起见
        fgets(post_exp, 1000, stdin);

        Root = insertTree(infix_exp, post_exp, Root);

        preOrderTraversal(Root, 1);

        printf("%d\n", winner_element);
        memset(infix_exp, 0, 1000 * sizeof(char));
        memset(post_exp, 0, 1000 * sizeof(char));
    }
    return 0;
}