#include<stdio.h>
 void main(){
     int swap(int x,int y);
     int a,b,c;
     scanf("%d %d %d",&a,&b,&c);
     int temp = 0 ;
     temp = swap(a,b);
     a = swap(temp,c);
     printf("%d\n",a);
 }

 //比较大小方法
 int swap(int x,int y){
     if(x>y){
         x = x;
     }else {
         x = y;
     }
     return x;
 }