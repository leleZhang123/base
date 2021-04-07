#include <stdio.h>
int main()
{
  int a=3;
	int max = 0;
	int b = 4;
	int c = 0;
	printf("please input a,b,c:\n");
	printf("The largest number is \n");
	scanf("%d,%d,%d",&a,&b,&c);
	printf("The largest number is ---- %d\n",a);
	
	printf("The largest number is %d\n",b);

	printf("The largest number is %d\n",c);
	max=a;
	printf("The largest number is %d\n",max);
	if(max<b)
		max=b;
	if(max<c)
		max=c;
	printf("The largest number is %d\n",max);
	return 0;
	
}