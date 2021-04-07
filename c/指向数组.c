# include <stdio.h>
int main()
{int a[10];
 int *p,i;
 printf("please enter 10 integer number:");
 for(i=0;i<10;i++)
 {
 	scanf("%d",&a[i]);
 }
 for(p=a;p<(a+10);p++)//指针指向当前数组 
 {
 	printf("%d",*p);
 }
 printf("\n"); 
 return 0;
} 
