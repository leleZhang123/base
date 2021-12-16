#include<stdio.h>
void main()
{
    int year ;
    printf("input year:");
    scanf("%d",&year);
    //条件为是400 的整数倍
    //可以整除4并且不可整除100
    if(year%400 ==0 ||year%4==0 && year%100 != 0)
    {
        printf("%d is a leap year!",&year);
    }
    else
    {
        printf("%d is not a leap year!",&year);
    }
}