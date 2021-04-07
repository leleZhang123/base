#include <stdio.h>
#include<stdlib.h>
#define maxsize 50
typedef struct
{
int data[maxsize];
int last;
}Sequenlist;

Sequenlist * InitList () //����˳���
{
Sequenlist * L ;
L= (Sequenlist *) malloc( sizeof(Sequenlist) );
L->last =0;
return(L);
}

Sequenlist * creat() //����һ���о������ݵ�˳���
{
Sequenlist * L; int i=1,n;
L=InitList( );
printf("���������,��0����\n");
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
int Length (Sequenlist * L) //���ĳ��� 
{
return (L->last); 
}

int GetData (Sequenlist * L, int i ) //��ȡ��i��Ԫ��
{
if ( i >=1 && i <=L->last)
return (L->data[i]);
else
{
printf ("���� i ������\n");
return 0;
}

} 
int Find (Sequenlist *L, int x ) // ����Ԫ��x
{
int i=1;
while ( i <=L->last && L->data[i] != x )
i++;
if ( i <=L->last )
return (i);
else
return (0);
}
int Insert ( Sequenlist * L, int x, int i ) //��ĳһλ�ò�������
{
int j;
//�ڱ��е� i ��λ�ò�����Ԫ�� x
if (i < 1|| i > L->last +1|| L->last == maxsize)
return 0; //���벻�ɹ�
else {
for ( j=L->last; j >=i; j-- )
{ L->data[j+1] = L->data[j]; }
L->data[i] = x; L->last++;
return 1; //����ɹ�
}
}
int Delete ( Sequenlist *L, int i ) //ɾ��ĳһλ�õ�����
{
//�ڱ���ɾ���ڵ�i
int j;
if ( i <1 || i >L->last) return 0;
for ( j=i+1; j <=L->last; j++ )
L->data[j-1] =L->data[j];
L->last=L->last -1;
return 1; //�ɹ�ɾ��

}
void print(Sequenlist *L) //��ӡ����
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

printf("Which number do you want to find?\n"); //���ҹ���
scanf("%d",&i);
value=Find(L,i+1);
if(value!=0)
printf("The location is %d\n",value);
else
printf("There is no such number!\n");

printf("Which place do you want to insert?\n"); //���빦��
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

printf("Which place do you want to delete?\n"); //ɾ������
scanf("%d",&k);
flag=Delete(L,k);
if(flag==0)
printf("Failing to delete!\n");
else
{ printf("Done!\n");
print(L);
}
} 
