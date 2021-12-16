#include<stdio.h>
//初级指针问题(赋值问题)
int main()
{
    int *p, a[10]={0};
    p = a;
    for(int i = 0;i<10;i++)
    {
        a[i]=i;
         printf("a数组为%d",*p++);
    }
    
}