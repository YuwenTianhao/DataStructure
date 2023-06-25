/**
  ******************************************************************************
  * @file           : chess.c
  * @author         : YuwenTianhao
  * @brief          : “1. 五子棋危险判断”
  * @attention      : 1、调试难 2、判断麻烦（需要防止越界） 3、通读性极差！
  *                   答案学习：
  *                   1、开指针把题目做复杂了，实际上记录 MAX = 19，直接检查最后一位不要越界即可
  *                   2、判断的过于啰嗦
  *                   3、可读性太差，因为没有很好的把模块，judge只能当一个黑盒子用，出任何错都查不出来
  * @date           : 2023.03.09
  ******************************************************************************
  */
#include "stdio.h"

#define CHESSBOARD_SIZE 19 // 确定棋盘大小

int chess[CHESSBOARD_SIZE][CHESSBOARD_SIZE]; // 存入棋盘数据
int (*Pchess)[CHESSBOARD_SIZE] = &chess; // 用指针可以进行判断， 防止数组越界

int judge_winner(int row, int column);

int main()
{
    for (int i = 0; i < CHESSBOARD_SIZE; i++)
        for (int j = 0; j < CHESSBOARD_SIZE; ++j)
        {
            scanf("%d", &chess[i][j]);
        }
    for (int i = 0; i < CHESSBOARD_SIZE; i++)
        for (int j = 0; j < CHESSBOARD_SIZE; ++j)
        {
            if (judge_winner(i, j) == 1)
            {
                printf("1:");
                printf("%d,", i + 1);
                printf("%d\n", j + 1);
                return 0;
            }
            else if (judge_winner(i, j) == 2)
            {
                printf("2:");
                printf("%d,", i + 1);
                printf("%d\n", j + 1);
                return 0;
            }
        }
    printf("No\n");
    return 0;
}

/**
 * @brief judge if chess[row][column] is winner
 * @note None
 * @param row
 * @param column
 * @return who wins
 */
int judge_winner(int row, int column)
{
    switch (chess[row][column])
    {
        case 0:
        {
            return 0;
        }
        case 1:
        {
            int flag = 0;
            // judge row
            for (int i = column; i < column + 4; i++)
            {
                if ((*(Pchess + row) + i) != NULL)
                    if (*(*(Pchess + row) + i) == 1)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row) + column - 1) != NULL)
                {
                    if (*(*(Pchess + row) + column - 1) == 0)
                        return 1;
                    else if ((*(Pchess + row) + column + 4) != NULL)
                        if (*(*(Pchess + row) + column + 4) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row) + column + 4) != NULL)
                        if (*(*(Pchess + row) + column + 4) == 0)
                            return 1;
                        else return 0;
                    else return 0;
                }
            }

            //judge column
            flag = 0;
            for (int j = row; j < row + 4; j++)
            {
                if ((*(Pchess + j) + column) != NULL)
                    if (*(*(Pchess + j) + column) == 1)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row - 1) + column) != NULL)
                {
                    if (*(*(Pchess + row - 1) + column) == 0)
                        return 1;
                    else if ((*(Pchess + row + 4) + column) != NULL)
                        if (*(*(Pchess + row + 4) + column) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row + 4) + column) != NULL)
                        if (*(*(Pchess + row + 4) + column) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
            }

            // judge right diagonal
            flag = 0;
            for (int j = 0; j < 4; j++)
            {
                if ((*(Pchess + row + j) + column + j) != NULL)
                    if (*(*(Pchess + row + j) + column + j) == 1)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row - 1) + column - 1) != NULL)
                {
                    if (*(*(Pchess + row - 1) + column - 1) == 0)
                        return 1;
                    else if ((*(Pchess + row + 4) + column + 4) != NULL)
                        if (*(*(Pchess + row + 4) + column + 4) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row + 4) + column + 4) != NULL)
                        if (*(*(Pchess + row + 4) + column) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
            }

            // judge left diagonal
            flag = 0;
            for (int j = 0; j < 4; j++)
            {
                if ((*(Pchess + row + j) + column - j) != NULL)
                    if (*(*(Pchess + row + j) + column - j) == 1)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row - 1) + column + 1) != NULL)
                {
                    if (*(*(Pchess + row - 1) + column + 1) == 0)
                        return 1;
                    else if ((*(Pchess + row + 4) + column - 4) != NULL)
                        if (*(*(Pchess + row + 4) + column - 4) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row + 4) + column - 4) != NULL)
                        if (*(*(Pchess + row + 4) + column - 4) == 0)
                            return 1;
                        else return 0;
                    else
                        return 0;
                }
            }
            return 0;
        }

        case 2:
        {
            int flag = 0;
            // judge row
            for (int i = column; i < column + 4; i++)
            {
                if ((*(Pchess + row) + i) != NULL)
                    if (*(*(Pchess + row) + i) == 2)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row) + column - 1) != NULL)
                {
                    if (*(*(Pchess + row) + column - 1) == 0)
                        return 2;
                    else if ((*(Pchess + row) + column + 4) != NULL)
                        if (*(*(Pchess + row) + column + 4) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row) + column + 4) != NULL)
                        if (*(*(Pchess + row) + column + 4) == 0)
                            return 2;
                        else return 0;
                    else return 0;
                }
            }

            //judge column
            flag = 0;
            for (int j = row; j < row + 4; j++)
            {
                if ((*(Pchess + j) + column) != NULL)
                    if (*(*(Pchess + j) + column) == 2)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row - 1) + column) != NULL)
                {
                    if (*(*(Pchess + row - 1) + column) == 0)
                        return 2;
                    else if ((*(Pchess + row + 4) + column) != NULL)
                        if (*(*(Pchess + row + 4) + column) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row + 4) + column) != NULL)
                        if (*(*(Pchess + row + 4) + column) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
            }

            // judge right diagonal
            flag = 0;
            for (int j = 0; j < 4; j++)
            {
                if ((*(Pchess + row + j) + column + j) != NULL)
                    if (*(*(Pchess + row + j) + column + j) == 2)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row - 1) + column - 1) != NULL)
                {
                    if (*(*(Pchess + row - 1) + column - 1) == 0)
                        return 2;
                    else if ((*(Pchess + row + 4) + column + 4) != NULL)
                        if (*(*(Pchess + row + 4) + column + 4) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row + 4) + column + 4) != NULL)
                        if (*(*(Pchess + row + 4) + column) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
            }

            // judge left diagonal
            flag = 0;
            for (int j = 0; j < 4; j++)
            {
                if ((*(Pchess + row + j) + column - j) != NULL)
                    if (*(*(Pchess + row + j) + column - j) == 2)
                        flag += 1;
            }
            if (flag > 3)
            {
                if ((*(Pchess + row - 1) + column + 1) != NULL)
                {
                    if (*(*(Pchess + row - 1) + column + 1) == 0)
                        return 2;
                    else if ((*(Pchess + row + 4) + column - 4) != NULL)
                        if (*(*(Pchess + row + 4) + column - 4) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
                else
                {
                    if ((*(Pchess + row + 4) + column - 4) != NULL)
                        if (*(*(Pchess + row + 4) + column - 4) == 0)
                            return 2;
                        else return 0;
                    else
                        return 0;
                }
            }
            return 0;
        }
        default:
            return 0;
    }
}