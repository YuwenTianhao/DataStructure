#include "stdio.h"
#include "string.h"

char in_line[100];
char out_line[100];
char base_num[100];
char index_num[10];
// Warning!!! The platform refuse to use the function 'itoa' in "stdlib.h" , the function below is copied from origin file
char* itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
    unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
    int i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。

    //获取要转换的整数的绝对值
    if(radix==10&&num<0)//要转换成十进制数并且是负数
    {
        unum=(unsigned)-num;//将num的绝对值赋给unum
        str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
    }
    else unum=(unsigned)num;//若是num为正，直接赋值给unum

    //转换部分，注意转换后是逆序的
    do
    {
        str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
        unum/=radix;//unum去掉最后一位

    }while(unum);//直至unum为0退出循环

    str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。

    //将顺序调整过来
    if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
    else k=0;//不是负数，全部都要调整

    char temp;//临时变量，交换两个值时用到
    for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp=str[j];//头部赋值给临时变量
        str[j]=str[i-1+k-j];//尾部赋值给头部
        str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
    }

    return str;//返回转换后的字符串
}

void base_check() // check the number of non-zero element in array
{
    char *base;
    int i = 0;
    base = in_line;
    while (*base == '0'|| *base == '.')
        base++;
    while (*base != '\0')
    {
        if(*base != '.')
        {
            base_num[i] = *base;
            i++;
        }
        base++;
    }

}

int index_check() // check the number of non-zero element in array
{
    char *non_zero = in_line;
    char *dot = in_line;
    while (*non_zero == '0' || *non_zero == '.')
        non_zero ++;
    while (*dot != '.')
        dot ++;
    if(dot - non_zero > 0)
        return dot - non_zero - 1;
    else
        return dot - non_zero;
}

int main()
{
    while (scanf("%s",in_line) != EOF)
    {
        char *now = out_line; // '*now' for pointing the current position of output_array while outputting
        base_check();
        // output the base_num
        *now = base_num[0];
        now++;
        if(strlen(base_num) > 1)
        {
            *now = '.';
            now++;
            char *tem = &base_num[1];
            while (*tem != '\0')
            {
                *now = *tem;
                now++;
                tem++;
            }
        }

        *now = 'e';
        now++;

        itoa(index_check(),index_num,10);
        strcat(out_line,index_num);

        printf("%s",out_line);
        // reset array
        memset(out_line,0,sizeof(out_line));
        memset(base_num,0,sizeof(base_num));
        memset(index_num,0,sizeof(index_num));
    }
}