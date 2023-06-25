/**
  ******************************************************************************
  * @file           : sort.c
  * @author         : YuwenTianhao
  * @brief          : 3. 整数排序（排序-基本题）
  * @attention      : 考试时应该注意简单排序的变体要求，复杂排序的逻辑认知(需要到什么地步呢，问一下)，由于题目全是现成的函数，没学到什么
  * @date           : 2023/6/5
  ******************************************************************************
  */

#include "stdio.h"
#include "stdlib.h"

int total_num;
int method;
int cmp_times;
int array[101];

// adjust的三个参数：数组名，待调整二叉树根结点的编号，正在处理的二叉树中的结点的个数
void adjust(int k[ ],int i,int n)	//构建堆
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n){
        if(j<n-1 && k[j]<k[j+1])
            j++;
        cmp_times++;			//********此时次数+1
        if(temp>=k[j])
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}

void heapSort(int k[],int n)	//堆排序
{
    int i;
    int temp;
    for(i=n/2-1;i>=0;i--)
        adjust(k,i,n);		//构建堆
    for(i=n-1;i>=1;i--){
        temp=k[i];			//把最大的移到最后，然后处理前面的数
        k[i]=k[0];
        k[0]=temp;
        adjust(k,0,i);		//处理前面的数
    }
}


void selectSort()
{
    for (int i = 0; i < total_num; i++)
        for (int j = i; j < total_num; j++)
        {
            if (array[i] > array[j])
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    cmp_times = total_num * (total_num - 1) / 2; // 偷一个懒
}

void bubbleSort()
{
    int flag = 1;
    for (int i = total_num - 1; i > 0 && flag; i--)
    {
        flag = 0;
        for (int j = 0; j < i; j++)
        {
            cmp_times++;
            if (array[j] > array[j + 1])
            {
                int tem = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tem;
                flag = 1;
            }
        }
    }
}

void merge(int x[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend)
    {
        cmp_times++;
        if (x[i] <= x[j])
        {
            tmp[q++] = x[i++];
        }
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
}

void mSort(int k[], int tmp[], int left, int right)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;        //递归处理归并
        mSort(k, tmp, left, center);
        mSort(k, tmp, center + 1, right);
        merge(k, tmp, left, center, right);
    }
}

//归并排序
void mergeSort(int k[], int n)
{
    int *tmp;
    tmp = (int *) malloc(sizeof(int) * n);    //申请外空间
    if (tmp != NULL)
    {
        mSort(k, tmp, 0, n - 1);
        free(tmp);
    }
    else
        printf("No space for tmp array!!!\n");
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int k[], int left, int right)
{
    int i, last;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            cmp_times++;            //********此时次数+1
            if (k[i] < k[left])
                swap(&k[++last], &k[i]);
        }
        swap(&k[left], &k[last]);
        quickSort(k, left, last - 1);
        quickSort(k, last + 1, right);
    }
}


int main()
{
    scanf("%d%d", &total_num, &method);
    for (int i = 0; i < total_num; i++)
        scanf("%d", &array[i]);
    switch (method)
    {
        case 1:
            selectSort();
            break;
        case 2:
            bubbleSort();
            break;
        case 3:
            heapSort(array,total_num);
            break;
        case 4:
            mergeSort(array, total_num);
            break;
        case 5:
            quickSort(array, 0, total_num - 1);
            break;
        default:
            break;
    }
    for (int i = 0; i < total_num; i++)
        printf("%d ", array[i]);
    printf("\n%d", cmp_times);
    return 1;
}