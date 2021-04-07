#include<stdio.h>
int main()
{ int a[10]={0,1,2,3,4,5,6,7,8,9};
	int *p;
	int i=0,j,k=100,n=1;
		for(p=a;p<(a+1);p++)
		   {
		   if(*p!=(2*n))
		           {
  		   
  					        while(p<(a+1))
  							{
  							
  							    for(i=0;i<10;i++)
  								{
  									for(j=0;j<i;j++)
  									{
  										printf("*");
  									}
  									printf("\n");
  							    }
  			                }
  			              
  					}
  		    else     
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
									printf("\n");
							    }	
						    }
			}
	return 0;
} 
