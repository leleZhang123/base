#include"stdio.h"
//指针初级问题(初始化问题)
int main()
{   
    int a = 10;
    int *p = &a,*po;
    po = &a;
    printf("指针的数值为%d",*p);
    printf("指针的地址为%d",p);
    *po = 13;
    printf("指针的数值为%d",*po);
    printf("指针的地址为%d",po);
    
}