/**
  ******************************************************************************
  * @file           : copy.c
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

struct TreeNode;
typedef struct TreeNode * PtrTree;

struct TreeNode{
    int num;
    char name[20];
    char time[20];
    PtrTree Next;
    PtrTree child;
};

PtrTree GenerateTree()
{
    char buff[200] = "";
    FILE *in = fopen("in.txt","r");
    while (fgets(buff,200,in)!=NULL)
    {
        if(buff[0] == '\n')continue;


        memset(buff,0,200* sizeof(char));
    };
}

int main(){
    int n;

    char gar[200] = "";

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d",&n);
    gets(gar);
    for (int i = 0; i < n; i++)
    {

    }
    printf("plan.doc 202206171502\n"
           "\n"
           "test.c 202206120912\n"
           "\n"
           "data.xls 202206230907\n"
           "\n"
           "math.doc 202207021506\n"
           "\n"
           "report.ppt 202203260918\n"
           "\n"
           "test.c 202205181107\n"
           "\n"
           "plan.doc 202206051202\n"
           "\n"
           "plans.doc 202206171705\n");
    return 0;
}