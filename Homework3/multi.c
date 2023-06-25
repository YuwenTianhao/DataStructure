/**
  ******************************************************************************
  * @file           : multi.c
  * @author         : YuwenTianhao
  * @brief          : "3. 多项式相乘"
  * @attention      : 系数稀疏的多项式相乘是一道很经典的链表题目
  *                   难点主要有：
  *                   1、链表排序
  *                   2、链表元素间合并
  *                   3、不定长输入，这个值得注意一下输入方式
  * @date           : 2023/3/27
  ******************************************************************************
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "LinkedList.h"

#define MAX_PtrARRAY_LENGTH 256

struct Node{
    int Coefficient; // 系数
    int Exponent; // 幂
    Position Next;
};
typedef PtrToNode Polynomial;

Polynomial initTable()
{
    Polynomial P = malloc(sizeof(struct Node));
    memset(P,0, sizeof(struct Node));
    return P;
}

void tailInsert(Polynomial P,List L)
{
    Position Ptr = L;
    while (Ptr->Next != NULL)
        Ptr = Ptr->Next;
    Ptr->Next = P;
}

int NumOfPolynomial(Polynomial P)
{
    int n = 0;
    while (P->Next != NULL)
    {
        n++;
        P = P->Next;
    }
    return n;
}

void MultiPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum)
{
    Polynomial Ptr_1 = Poly1;
    while (1)
    {
        Polynomial Ptr_2 = Poly2;
        Ptr_1 = Ptr_1->Next;
        if(Ptr_1 == NULL)
            break;
        while (1)
        {
            Ptr_2 = Ptr_2->Next;
            if(Ptr_2 == NULL)
                break;
            else
            {
                Polynomial Sum = initTable();
                Sum->Coefficient = Ptr_1->Coefficient * Ptr_2->Coefficient;
                Sum->Exponent = Ptr_1->Exponent + Ptr_2->Exponent;
                tailInsert(Sum,PolySum);
            }
        }
    }
}

void InputPolynomial(Polynomial P)
{
    int tmp_co = 0;
    int tmp_ex = 0;
    char tmp_c;
    do{
        scanf("%d%d%c",&tmp_co,&tmp_ex,&tmp_c);
        Polynomial Tmp = initTable();
        Tmp->Coefficient = tmp_co;
        Tmp->Exponent = tmp_ex;
        tailInsert(Tmp,P);
    } while (tmp_c != '\n');
}
void SortList(Polynomial Sum)
{
    int n = NumOfPolynomial(Sum);
    for (int i = 0; i < n - 1; i++)
    {
        Polynomial Ptr2 = Sum;
        for (int j = 0; j < n - 1 - i; j++)
        {
            Ptr2 = Ptr2->Next;
            if (Ptr2->Exponent < (Ptr2->Next)->Exponent)
            {
                int tmp_co = (Ptr2->Next)->Coefficient;
                int tmp_ex = (Ptr2->Next)->Exponent;
                (Ptr2->Next)->Coefficient = Ptr2->Coefficient;
                (Ptr2->Next)->Exponent = Ptr2->Exponent;
                Ptr2->Coefficient = tmp_co;
                Ptr2->Exponent = tmp_ex;
            }
        }
    }
}

void CombineSum(Polynomial SortedSum)
{
    Polynomial P = SortedSum->Next;
    while (P->Next != NULL)
    {
        while (P->Exponent == (P->Next)->Exponent)
        {
            Polynomial N = P->Next;
            P->Coefficient += N->Coefficient;
            P->Next = N->Next;
            free(N);
        }
        if(P->Coefficient == 0)
        {
            Position Pre = FindPrevious(P,SortedSum);
            Pre->Next = P->Next;
            free(P);
        }
        P = P->Next;
    }
}

Position FindPrevious(Position P, List L)
{
    Position Pre = L;
    while (Pre->Next != NULL)
        if(Pre->Next == P)
            return Pre;
        else Pre = Pre->Next;
    return NULL;
}

int main(){
    Polynomial Poly1 = initTable();
    Polynomial Poly2 = initTable();
    Polynomial PolySum = initTable();
    Polynomial Result[MAX_PtrARRAY_LENGTH];
//    freopen("a.in","r",stdin);
//    freopen("a.out","w",stdout);
    InputPolynomial(Poly1);
    InputPolynomial(Poly2);
    MultiPolynomial(Poly1,Poly2,PolySum);
    SortList(PolySum);
    CombineSum(PolySum);
    while(PolySum->Next !=NULL)
    {
        PolySum = PolySum->Next;
        printf("%d %d ",PolySum->Coefficient,PolySum->Exponent);
    }

    return 0;
}