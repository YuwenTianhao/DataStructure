/**
  ******************************************************************************
  * @file           : qsort.c
  * @author         : YuwenTianhao
  * @brief          : ”qsort()“几乎是考试必考，线性表、字符串都用得到，在这里给出常用的比较函数
  * @attention      : None
  * @date           : 2023/4/26
  ******************************************************************************
  */

// 整数比较函数（字符型也适用）

// 升序
int cmp_int_asc(const void* e1, const void* e2)
{
    return *(int*)e1 - *(int*)e2;
}

// 降序
int cmp_int_des(const void* e1, const void* e2)
{
    return *(int*)e2 - *(int*)e1;
}

// 字符串排序

//升序
int cmp_string_asc(const void* e1, const void* e2)
{
    return strcmp((char*)e1, (char*)e2);
}

int cmp_string_des(const void* e1, const void* e2)
{
    return strcmp((char*)e2, (char*)e1);
}