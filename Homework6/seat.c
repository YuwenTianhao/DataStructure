/**
  ******************************************************************************
  * @file           : seat.c
  * @author         : YuwenTianhao
  * @brief          : None
  * @attention      : None
  * @date           : 2023/6/5
  ******************************************************************************
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N; // 学生总数
typedef struct
{
    int ID; // 学号
    char name[21];
    int seat;
} Student;
Student *st_list[101];

// 升序
int cmp_int_asc(const void* e1, const void* e2)
{
    return *(int*)e1 - *(int*)e2;
}

int main()
{
    FILE *fp_in, *fp_out;
    int i = 0;
    int tem_ID;
    char tem_name[21] = "";
    int tem_seat = 0;
    scanf("%d", &N);
    fp_in = fopen("in.txt", "r");
    for (int i = 0; i < N; i++)
    {
        st_list[i] = malloc(sizeof(Student));
        memset(st_list[i], 0, sizeof(Student)); // 指针还是
        fscanf(fp_in, "%d %s %d", &st_list[i]->ID,st_list[i]->name,&st_list[i]->seat);
    }
    fclose(fp_in);

    fp_out = fopen("out.txt", "w");


    return 0;
}
