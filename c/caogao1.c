#include<stdio.h>
int main(){ int a[10]={0,1,2,3,4,5,6,7,8,9};
	int *p;
	int i,j;
	  while(p<(a+1))
							{
							
							    for(i=0;i<10;i++)
								{
									for(j=0;j<10-i;j++)
									{
										printf(" ");
									}
								for(j=0;j<i;j++)
									printf("*");
							    }	
						    }	
return 0;
}
