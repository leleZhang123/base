#include<stdio.h>
#define N 10
int main()
{
	int i,j,a[N][N];
	for(i=0;i<N;i++)
	{
		a[i][i]=1;//ʹ�Խ���ֵΪ1�� 
        a[i][0]=1;//ʹ��1��Ԫ��ֵΪ1 
	}
	for(i=2;i<N;i++)//�ӵ����п�ʼ���� 
	  for(j=1;j<=i-1;j++)
        a[i][j]=a[i-1][j-1]+a[i-1][j]; 
    for(i=0;i<N;i++)
	{
		for(j=0;j<=i;j++)
		  printf("%6d",a[i][j]);//���ֵ��� 
		  printf("\n");
		  } 
	printf("\n");
	return 0; 
} 

 
