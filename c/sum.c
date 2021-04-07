# include<stdio.h>
int main()
{int i,a[3];
int sum=0;
int ave; 
printf("please enter 3 number :");
for(i=0;i<3;i++)
{
scanf("%d",&a[i]);
 sum=sum+a[i];
// printf("%d",sum);
 }
 ave=sum/3;
 printf("%d",ave);
 return 0;

 } 
