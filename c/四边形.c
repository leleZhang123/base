#include<stdio.h>
int main()
{int i,j; 
 for(i=1;i<=5;i++)

 { for(j=1;j<=9-2*i;j++) 
 printf(" ");
   for(j=1;j<=5;j++)
{
  printf("*");
 if(j%5==0)
 printf("\n");}
}
 return 0;
  
 } 
