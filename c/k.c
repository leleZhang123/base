#include <stdio.h>
#include <stdlib.h>
int main()
{FILE *fp;
char i;
fp=fopen("D:\\c.txt","r");
if(fp=fopen("D:\\c.txt","r")==NULL)
{printf("cannot open this file\n");
 exit(0);
}
//fprintf(fp,"%c",&i);
//fscanf(fp,"%c",&i); 
i=getchar();
fputc(i,fp);
//printf("%d",i);
putchar(i);
return 0;
 } 
