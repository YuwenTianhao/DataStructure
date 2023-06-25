/**
  ******************************************************************************
  * @file           : path.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/18
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK_NUM 1000

typedef struct
{
    int dir;
    int times;
} Way;

Way ways[MAX_STACK_NUM];
int TopOfStack = -1;

void push(int now_dir, int now_times)
{
    if (now_times > 0)
    {
        TopOfStack++;
        ways[TopOfStack].dir = now_dir;
        ways[TopOfStack].times = now_times;
    }
}

Way pop()
{
    return ways[TopOfStack--];
}

int main()
{
//
//    freopen("a.in", "r", stdin);
//    freopen("a.out", "w", stdout);
    int now_dir;
    int now_times;
    int tmp_dir = 0;
    int tmp_times = 0;
    while (scanf("%d-%d", &now_dir, &now_times) != EOF)
    {
        if (now_dir == 0)break;
        if (TopOfStack == -1)
            push(now_dir, now_times);
        else
        {
            switch (now_dir)
            {
                case 5:
                {
                    if (ways[TopOfStack].dir == 6)
                    {
                        // now大于等于栈顶
                        if (now_times >= ways[TopOfStack].times)
                        {
                            now_times -= ways[TopOfStack].times;
                            pop();
                            push(now_dir, now_times);
                        }
                        else
                            ways[TopOfStack].times -= now_times;
                    }
                    else push(now_dir, now_times);
                }
                    break;
                case 6:
                {
                    if (ways[TopOfStack].dir == 5)
                    {
                        if (now_times >= ways[TopOfStack].times)
                        {
                            now_times -= ways[TopOfStack].times;
                            pop();
                            push(now_dir, now_times);
                        }
                        else
                            ways[TopOfStack].times -= now_times;
                    }
                    else push(now_dir, now_times);
                }
                    break;
                case 7:
                {
                    if (ways[TopOfStack].dir == 8)
                    {
                        if (now_times >= ways[TopOfStack].times)
                        {
                            now_times -= ways[TopOfStack].times;
                            pop();
                            push(now_dir, now_times);
                        }
                        else
                            ways[TopOfStack].times -= now_times;
                    }
                    else push(now_dir, now_times);
                }
                    break;
                case 8:
                {
                    if (ways[TopOfStack].dir == 7)
                    {
                        if (now_times >= ways[TopOfStack].times)
                        {
                            now_times -= ways[TopOfStack].times;
                            pop();
                            push(now_dir, now_times);
                        }
                        else
                            ways[TopOfStack].times -= now_times;
                    }
                    else push(now_dir, now_times);
                }
                    break;
                default:
                    break;
            }
        }
    }
    // 出栈
    while (TopOfStack != -1)
    {
        Way now_pop = pop();
        if (tmp_dir != now_pop.dir)
        {

            switch (tmp_dir)
            {
                case 5:
                    printf("6-%d ", tmp_times);
                    break;
                case 6:
                    printf("5-%d ", tmp_times);
                    break;
                case 7:
                    printf("8-%d ", tmp_times);
                    break;
                case 8:
                    printf("7-%d ", tmp_times);
                    break;
                default:
                    break;
            }



            tmp_dir = now_pop.dir;
            tmp_times = now_pop.times;
        }
        else
            tmp_times += now_pop.times;
    }
    switch (tmp_dir)
    {
        case 5:
            printf("6-%d ", tmp_times);
            break;
        case 6:
            printf("5-%d ", tmp_times);
            break;
        case 7:
            printf("8-%d ", tmp_times);
            break;
        case 8:
            printf("7-%d ", tmp_times);
            break;
        default:
            break;
    }
    return 0;
}