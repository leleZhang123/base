#include<stdio.h>
int main()
{
	int i,j,n=0;
	for(i=1;i<=4;i++)
	for(j=1;j<=4;j++,n++)
      {
	  
	  if(n%4==0)printf("\n");//n�����ۼ� ����������ݸ����� 
	  printf("%d",i*j);
	
	  } 
	  printf("\n");
   return 0;
 } 
