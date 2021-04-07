#include<stdio.h>
int main()
{int i;
int f[30]={1,1};
for(i=1;i<=30;i++)
 f[i]=f[i-1]+f[i-2];
 for(i=0;i<30;i++)
 {
 	if(i%5==0)printf("\n");
 	printf("%12d",f[i]);
 }
 printf("\n");
 return 0;
}
