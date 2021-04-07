#include<stdio.h>
int main()
{int i,j,a[9][9] ,t;
 	for(i=1;i<=9;i++)
 	{
 	  for(j=1;j<=i;j++)
 	  {
	  t=i*j;
	   printf("%d*%d=%-3d",i,j,t);
	   if(i==j)
	   printf("\n");
      }	
 	}
 	printf("\n");
 	return 0;
 }
 
