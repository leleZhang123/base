#include<stdio.h>
#include<math.h>
int main()
{double a,b,c,disc,x1,x2,p,q;
 scanf("%lf%lf%lf",&a,&b,&c);//输入双精度型变量的值要用格式声明“%lf” 
 disc=b*b-4*a*c;//disc用于存变式 
 p=-b/(2.0*a);
 x1=p+q;
 x2=p-q;
 	printf("x1=%7.2f\nx2=%7.2f\n",x1,x2);//输出方程的两个根 
return 0;
 } 
