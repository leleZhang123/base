#include<stdio.h>
#define LIST_INIT_SIZE 10
#define ERROR -1
int b;
typedef int  ElemType;
typedef struct Sqlist
{
   ElemType  data[LIST_INIT_SIZE];
	int len;
}SqList;
void createSqList(SqList &L,int n){
	int i;
	printf("%d\n",n);
     for(i=0;i<n;i++){ 
	scanf("%d",&L.data[i]);
	}
		L.len=n;
		
}
void printSqList(SqList L){
	printf("打印线性表:");
	int i;
	for(i=0;i<5;i++){
		printf("%d",L.data[i]);
	}
	printf("\n");
}
int insertSqlist(SqList L)
{
	int k,i;
	i=b;
	if((i<1)||(i>LIST_INIT_SIZE))
	{
		printf("插入位置不合法!");
		return ERROR;
	}
	if(i=LIST_INIT_SIZE)
	{
		printf("表已满，无法插入！");
		return ERROR; 
	}
	for(k=LIST_INIT_SIZE;k>=i-1;k--)
	{
	    L.data[k+1]=L.data[k];
	}
		for(i=0;i<5;i++){
		printf("%d",L.data[i]);
	}
		L.data[i-1]=L.data[i];
		L.data[LIST_INIT_SIZE]++;
		return 1; 
}
	

int main(){
	SqList L;
	L.len=0;
	scanf("%d",&b);

	
	createSqList(L,5);
	
    insertSqlist(L);

	printSqList(L);

return 0;	
}
	
	
