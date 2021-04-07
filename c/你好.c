#include <stdio.h>  
#include <stdlib.h> 
 
#define LIST_INIT_SIZE  5  //线性表初始长度 
#define LISTINCREMENT  5  //线性表每次扩充长度 
 
#define OK        1
#define ERROR      0 
 
//线性表结构体 
typedef struct SqList{   
  int *elem; 
  int len; 
  int size; 
}; 
 
//初始化线性表 
int InitList_Sq(struct SqList *L){ 
  //使用malloc函数，申请一段连续的存储空间 
  L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int)); 
  if(!L->elem)exit(0); 
  L->len=0; 
  L->size = LIST_INIT_SIZE; 
  return OK; 
} 
 
//向线性表中插入数据 
int ListInsert_Sq(struct SqList *L,int i,int e){ 
  if(i<1||i>L->len+1) return ERROR; 
  if(L->len>=L->size){ 
    //使用realloc函数，在原本的基地址上申请更大的存储空间 
    int *newbase = (int *)realloc(L->elem,(LIST_INIT_SIZE + LISTINCREMENT) * sizeof(int)); 
    //如果申请空间失败则结束程序 
    if(!newbase)exit(0); 
    L->size += LISTINCREMENT; 
  } 
  int *q = &(L->elem[i-1]); 
  int *p; 
  for(p=&L->elem[L->len-1];p>=q;--p) 
    *(p+1)=*p; 
  *q=e; 
  ++L->len; 
  return OK; 
} 
 
//删除线性表中的数据 
int ListDelete_Sq(struct SqList *L,int i,int *e){ 
  if(i<1||i>L->len) return ERROR; 
  int *p=&(L->elem[i-1]); 
  *e=*p; 
  int q= L->elem + L->len-1; 
  for(++p;p<=q;++p) 
    *(p-1)=*p; 
  L->len--; 
  return OK; 
} 
 
//输出线性表中的数据 
int ListShow_Sq(struct SqList *L,char* s){ 
  printf("%s",s); 
  int i; 
  for(i=0;i<L->len;i++){ 
    printf("%d ",L->elem[i]); 
  } 
  putchar('\n'); 
} 
 
void main(){ 
  int i; 
  struct SqList L; 
   
  //初始化线性表 
  InitList_Sq(&L); 
   
  //输入数据 
  int n; 
  printf("预先输入的原始数据个数是："); 
  scanf("%d",&n); 
  printf("请线性表中%d个原始数据：",n); 
  for(i=0;i<n;i++){ 
    int t; 
    scanf("%d",&t); 
    ListInsert_Sq(&L,L.len+1,t); 
  } 
  ListShow_Sq(&L,"原始数据："); 
   
  //定义插入/删除操作时位置和数值参数 
  int s,v; 
   
  //插入操作 
  printf("请输入数据插入的位置s 和数值v ："); 
  scanf("%d%d",&s,&v); 
  printf("%s",ListInsert_Sq(&L,s,v)?"插入成功.\n":"插入失败.\n");
  ListShow_Sq(&L,"插入后："); 
   
  //删除操作 
  printf("请输入数据删除的位置s ："); 
  scanf("%d",&s); 
  if(ListDelete_Sq(&L,s,&v)) 
    printf("删除成功.删除的数据是：%d\n",v); 
  else 
    printf("删除失败.位置有误."); 
  ListShow_Sq(&L,"删除后："); 
 
  system("pause"); 
} 
