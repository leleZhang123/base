#include<stdio.h>
int main()
{int f1=1,f2=1;int i;
 printf("%12d%12d",f1,f2);
 for(i=1;i<=19;i++)
 {f1=f1+f2;
 f2=f1+f2; 
printf("%12d%12d",f1,f2); 
}
return 0;}
