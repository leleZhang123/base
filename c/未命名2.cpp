#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define INCREMENT 10

#define OK 1
#define ERROR 0

 typedef int Status;
 typedef int ElemType;

 typedef struct
 {
    ElemType *data; //节点数据
    int length; //顺序表长度
    int size; //顺序表大小
 }SqList;

//初始化
Status InitList(SqList *L)
{
    L->data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
    if(!L->data) return ERROR;
    L->length = 0;
    L->size = MAXSIZE;
    return OK;
}
//根据位置返回元素
Status GetElem(SqList *L,int pos,ElemType* e)
{
    if(pos<1||pos>L->length) return ERROR;
    (*e) = L->data[pos-1];
    return OK;
}
Status ListEmpty(SqList *L)
{
    return L->length == 0?1:0;
}

//根据位置插入元素
Status Insert(SqList *L,int pos,ElemType e)
{
    ElemType* newBase;
    int i = 0;
    if(pos < 1||pos > L->length+1)
        return ERROR;
    if(L->length >= L->size)
    {
        newBase = (ElemType *)realloc(L->data,(L->size+INCREMENT)*sizeof(ElemType));
        L->data = newBase;
        L->size+=INCREMENT;
    }
    for(i=L->length-1;i>=pos-1;i--)
        L->data[i+1] = L->data[i]; //后移
    L->data[pos-1] = e;
    L->length++;
    return OK;
}

//创建
Status Create(SqList *L,int n)
{
    ElemType e;
    int i = 0;
    while(i < n)
    {
        scanf("%d",&e);
        Insert(L,i+1,e);
        i++;
    }
    return OK;
}

//根据位置删除元素
Status DeleteAccordToPos(SqList *L,int pos,ElemType* e)
{
    int i = 0;
    if(!L->data) return ERROR;
    if(pos < 1||pos > L->length)
        return ERROR;
    (*e) = L->data[pos-1];
    for(i = pos-1;i < L->length;++i)
        L->data[i] = L->data[i+1];
    L->length--;
    return OK;
}
//遍历
Status Traverse(SqList *L)
{
    int i = 0;
    while(i < L->length)
    {
        printf("%d ",L->data[i]);
        i++;
    }
    printf("\n");
    return OK;
}


