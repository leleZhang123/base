#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

//display����ʵ�ִ�ӡ����Ԫ�أ� 
//array-��ӡ�����飬maxlen-����Ԫ�ظ���

void display(int array[], int maxLen)
{
	int i;
	
	for( i = 0; i <maxLen; i++)
	{
		printf("%-3d",array[i]);//��ӡ���� 
	}
	printf("\n");
			
	return;
	}
	
//swap����ʵ�ֽ�����������ֵ�� 

void swap(int *a,int *b)
{
	int temp;
	
	temp = *a;//ʵ�ֽ��� 
	*a = *b;
	*b = temp;
	
	return ;
}

//quickSort����ʵ�� ���������㷨�� 

void quickSort(int array[], int maxLen, int begin, int end)
{
	int i, j;
	
	if(begin < end)
	{
		i=begin + 1;//��array[begin]��Ϊ��׼������˴�array[begin+1]��ʼ���׼���Ƚϣ�
		j=end;//array[end]����������һλ
		
	while(i < j)
	{
		if(array[i] > array[begin])//����Ƚϵ�����Ԫ�ش��ڻ�׼�����򽻻�λ�á�
		{
			swap(&array[i], &array[j]);//����������
			j--;
		}
		else
		{
		    i++;//�����������һλ���������׼���Ƚϡ�
		}
	}
	/*����whileѭ����i=j��
	*��ʱ���鱻�ָ����������array[begin+1]~array[i-1]<array[begin]
	*array[i+1]~array[end]>array[begin]
	*���ʱ������array�ֳ��������֣��ٽ�array[i]��array[begin]���бȽϣ�����array[i]��λ�á�
	*���array[i]��array[begin]���������������ָ�ֵ������Դ����ƣ�ֱ�����i=j�������������˳���
	*/
	if(array[i] >= array[begin])//����Ԫ������ͬ��ֵʱ������ִ���
	{
		i--;
	}
	
	swap(&array[begin],&array[i]);//����array[i]��array[begin]
	
	quickSort(array,maxLen, begin, i);
	quickSort(array,maxLen, j, end);
	}
}
//������
int main()
{
	int n;
	int i;
	int array[SIZE]; 
	
	printf("������ʮ�����֣�");
	for(i=0; i<SIZE; i++ ) 
	{
		scanf("%d", &array[i]);//����ʮ������ 
	}
	int maxLen=SIZE;
	
	printf("����ǰ������\n");
	display(array, maxLen);
	
	quickSort(array, maxLen, 0, maxLen-1);//��������
	
	printf("����������\n");
	display(array, maxLen);
	
	return 0;
}
