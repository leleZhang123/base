#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

//display函数实现打印数组元素； 
//array-打印的数组，maxlen-数组元素个数

void display(int array[], int maxLen)
{
	int i;
	
	for( i = 0; i <maxLen; i++)
	{
		printf("%-3d",array[i]);//打印数组 
	}
	printf("\n");
			
	return;
	}
	
//swap函数实现交换两个数的值； 

void swap(int *a,int *b)
{
	int temp;
	
	temp = *a;//实现交换 
	*a = *b;
	*b = temp;
	
	return ;
}

//quickSort函数实现 快速排序算法； 

void quickSort(int array[], int maxLen, int begin, int end)
{
	int i, j;
	
	if(begin < end)
	{
		i=begin + 1;//将array[begin]作为基准数，因此从array[begin+1]开始与基准数比较！
		j=end;//array[end]是数组的最后一位
		
	while(i < j)
	{
		if(array[i] > array[begin])//如果比较的数组元素大于基准数，则交换位置。
		{
			swap(&array[i], &array[j]);//交换两个数
			j--;
		}
		else
		{
		    i++;//将数组向后移一位，继续与基准数比较。
		}
	}
	/*跳出while循环后，i=j。
	*此时数组被分割成两个部分array[begin+1]~array[i-1]<array[begin]
	*array[i+1]~array[end]>array[begin]
	*这个时候将数组array分成两个部分，再将array[i]与array[begin]进行比较，决定array[i]的位置。
	*最后将array[i]与array[begin]交换，进行两个分割部分的排序！以此类推，直到最后i=j不满足条件就退出！
	*/
	if(array[i] >= array[begin])//数组元素由相同的值时，会出现错误！
	{
		i--;
	}
	
	swap(&array[begin],&array[i]);//交换array[i]与array[begin]
	
	quickSort(array,maxLen, begin, i);
	quickSort(array,maxLen, j, end);
	}
}
//主函数
int main()
{
	int n;
	int i;
	int array[SIZE]; 
	
	printf("请输入十个数字：");
	for(i=0; i<SIZE; i++ ) 
	{
		scanf("%d", &array[i]);//输入十组数据 
	}
	int maxLen=SIZE;
	
	printf("排序前的数组\n");
	display(array, maxLen);
	
	quickSort(array, maxLen, 0, maxLen-1);//快速排序
	
	printf("排序后的数组\n");
	display(array, maxLen);
	
	return 0;
}
