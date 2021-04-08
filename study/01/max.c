#include<stdio.h>
int main()
{
    int max(int x,int y);
    int a, b;
    scanf("%d,%d",&a,&b);
    int sum = max(a,b);
    printf("max is %d\n",sum);
    return 0;
}

int max(int x, int y)
{
    int z;
    if(x>y)z=x;
    else x=y;
    return x;  
}