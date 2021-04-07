#include <stdio.h>
#include<stdlib.h>
#define maxsize 50
typedef struct
{
int data[maxsize];
int last;
}Sequenlist;

Sequenlist * InitList () //创建顺序表
{
Sequenlist * L ;
L= (Sequenlist *) malloc( sizeof(Sequenlist) );
L->last =0;
return(L);
}

Sequenlist * creat() //创建一个有具体内容的顺序表
{
Sequenlist * L; int i=1,n;
L=InitList( );
printf("请插入数据,以0结束\n");
scanf("%d",&n);
while(n!=0 && L->last<maxsize)
{
L->data[i]=n;
i=i++;
L->last++;
scanf("%d",&n);
}
return(L);
}
int Length (Sequenlist * L) //求表的长度 
{
return (L->last); 
}

int GetData (Sequenlist * L, int i ) //获取第i个元素
{
if ( i >=1 && i <=L->last)
return (L->data[i]);
else
{
printf ("参数 i 不合理！\n");
return 0;
}

} 
int Find (Sequenlist *L, int x ) // 查找元素x
{
int i=1;
while ( i <=L->last && L->data[i] != x )
i++;
if ( i <=L->last )
return (i);
else
return (0);
}
int Insert ( Sequenlist * L, int x, int i ) //在某一位置插入数据
{
int j;
//在表中第 i 个位置插入新元素 x
if (i < 1|| i > L->last +1|| L->last == maxsize)
return 0; //插入不成功
else {
for ( j=L->last; j >=i; j-- )
{ L->data[j+1] = L->data[j]; }
L->data[i] = x; L->last++;
return 1; //插入成功
}
}
int Delete ( Sequenlist *L, int i ) //删除某一位置的数据
{
//在表中删除节点i
int j;
if ( i <1 || i >L->last) return 0;
for ( j=i+1; j <=L->last; j++ )
L->data[j-1] =L->data[j];
L->last=L->last -1;
return 1; //成功删除

}
void print(Sequenlist *L) //打印函数
{
int i;
for(i=1;i<=L->last;i++)
printf("%d\n",L->data[i]);
}
void main()
{
int length,i;
int value,number,location;
int j,k;
int flag;

Sequenlist * L ;
L=creat();
length=Length(L);
printf("The length is %d\n",length);
printf("Please input the location\n");
scanf("%d",&location);
value=GetData(L,location);
printf("The number is %d\n",value);

printf("Which number do you want to find?\n"); //查找功能
scanf("%d",&i);
value=Find(L,i+1);
if(value!=0)
printf("The location is %d\n",value);
else
printf("There is no such number!\n");

printf("Which place do you want to insert?\n"); //插入功能
scanf("%d",&j);
printf("Please input the number\n");
scanf("%d",&number);
flag=Insert(L,number,j);
if(flag==0)
printf("Failing to insert!\n");
else
{ printf("Done!\n");
print(L);
}

printf("Which place do you want to delete?\n"); //删除功能
scanf("%d",&k);
flag=Delete(L,k);
if(flag==0)
printf("Failing to delete!\n");
else
{ printf("Done!\n");
print(L);
}
} 
