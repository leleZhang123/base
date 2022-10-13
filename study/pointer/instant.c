#include<stdio.h>
// void main()
// {
//     int a=100,b=10;
//     int *pointer_1,*pointer_2;//指针引用
//     pointer_1=&a;//赋值将a的地址赋值给1
//     pointer_2=&b;//赋值将b 的 地址赋值给2
//     printf("a=%d,b=%d\n",a,b);//通过基本引用
//     printf("a=%d,b=%d",*pointer_1,*pointer_2);//指针引用
// }
/*--------------指针变量赋值--------------*/
// void main()
// {
//     int *p1,*p2,*p,a,b;
//     printf("Input number:");
//     scanf("%d%d",&a,&b);
//     p1=&a;
//     p2=&b;
//     if(a<b)
//     {
//         p=p1;//通过内部的交换实现由指针交换
//         p1=p2;
//         p2=p;
//     }
//     printf("a=%d,b=%d\n",a,b);
//     printf("max=%d,min=%d",*p1,*p2);
// }
/*--------------指针变量为参数--------------*/
 void main()
 {
    void swap(int * p1,int * p2);
    int a,b;
    int *pointer_1,*pointer_2;
    printf("please enter a and b:");
    scanf("%d %d",&a,&b);
    pointer_1 = &a;
    pointer_2 = &b;
    if(a<b)
    swap(pointer_1,pointer_2);
    printf("max = %d,min = %d",*pointer_1,*pointer_2);

 }
//  void swap(int * p1,int* p2)
//  {
//      int temp;
//      temp = *p1;
//      *p1=*p2;
//      *p2= temp;
//  }
//交换指针的指向(值不变更)
 void swap(int * p1,int* p2)
 {
     int *temp;
     temp = p1;
     p1=p2;
     p2= temp;
 }
 /*--------------指针引用数组-----------------*/