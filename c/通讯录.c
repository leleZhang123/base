#include "stdio.h"
#include "string.h"
#define Null 0
#define MAX 200
 /*输入文件每行应不超过MAX个字符*/

typedef struct node /*采用孩子兄弟双亲链表的存储结构*/
{
char name[12];
unsigned int size;
struct node *parent,*first_child,*next_sibling;
}BinTNode,*BinTree;

/* 添加新节点 */
BinTree New_BinTNode(char str[],int *I,BinTree parentArray[],int *head,int *rear)
{ int i=0;
 BinTree bt;
 bt=(BinTNode *)malloc(sizeof(BinTNode));
 bt->parent=parentArray[*head]; /*链接双亲结点确定归属目录*/
 bt->first_child=Null;
 bt->next_sibling=Null;
 if(str[*I]=='*')
 {(*rear)++; parentArray[*rear]=bt;}
 while(str[*I]!=' ')
 {
 bt->name[i]=str[*I];
 (*I)++;i++;
 }
 bt->name[i]='\0';(*I)++;
 bt->size=str[*I]-'0';(*I)++;
 while ((str[*I]!=' ')&&(str[*I]!=')')&&((*I)<strlen(str)-1)) /*条件(*I)<strlen(str)-1)是考虑到根节点没有‘ ’和')'*/
 {
 bt->size=bt->size*10+(str[*I]-'0');
 (*I)++;
 }
 return bt;
}
/* 创建数据（将输入数据转化为所采用的树结构) */
BinTree Create_BinTree(FILE *input)
{ int I=0,rear=0,head=1; /*parentArray[head]用来记录当前节点应指向的parent目录节点*/
 /*parentArray[rear]用来记录最后一个目录节点*/
 BinTree parentArray[MAX];/*parentArray[]用来记录所有的目录节点地址*/
 BinTree root,bt,pbt;
 char str[MAX];
 fgets(str,MAX,input);
 root=New_BinTNode(str,&I,parentArray,&head,&rear);
 root->parent=Null; /* 在创建根节点时其parent的赋值是随机的，这里给它赋回空 */
 while(!feof(input))
 {I=1; /*I是输入文件每行字符串中的下标，贯穿该行字符处理始末*/
 fgets(str,MAX,input);
 while(I<=(strlen(str)-1))
 {
 if(str[I]!=')')
 {
 bt=New_BinTNode(str,&I,parentArray,&head,&rear);
 parentArray[head]->first_child=bt;
 pbt=bt;
 do /*创建并链接一对括号里的所有兄弟节点*/
 {
 if(str[I]==' ')
 {
 I++;
 pbt->next_sibling=New_BinTNode(str,&I,parentArray,&head,&rear); /*创建兄弟节点*/
 pbt=pbt->next_sibling;
 }
 }while(str[I]!=')') ;
 head++; I=I+3; /* 此时遇到右括号head+1处理下一个目录；I+3跳过") (" */
 }
 else
 {head++ ; I=I+3;} /* 此时也遇到右括号 */
 }
 }
 return root;
}

/* 求目录大小 */
int SIZE(BinTree bt) /*返回当前目录左子树的大小（未加上原目录大小）*/
{ int size;
 if(bt)
 size=bt->size+SIZE(bt->first_child)+SIZE(bt->next_sibling);
 else size=0;
 return size;
}
/* 输出单个节点 */
void out(BinTree bt,FILE *output)
{ char size_str[10];
 BinTree pbt=bt->parent;
 int i=-1,j=0,k;
 int flag[11]; /*flag[i]用来控制缩进，子目录深度可以设置，目前设为11*/
 for(k=0;k<11;k++) flag[k]=0;
 if(bt->name[0]=='*') bt->size=bt->size+SIZE(bt->first_child);
 /*目录的大小为该目录本身大小及其左子树（以其第一个孩子为根的树）所有节点的size和*/
 while(pbt!=Null)
 {
 i++;
 if(pbt->next_sibling) flag[j]=1; /*输出时flag[i]=1缩进"| ?" */
 else flag[j]=0; /*输出时flag[i]=0缩进" " */
 pbt=pbt->parent;
 j++;
 }
 while(i>=0)
 {
 if(flag[i]) {printf("| ");fprintf(output,"| ");}
 else {printf(" ");fprintf(output," ");}
 i--;
 }
 printf("|_%s[%d]\n",bt->name,bt->size);
 fprintf(output,"|_%s[%d]\n",bt->name,bt->size);
}

/* 先序遍历输出整棵树 */
void OUTPUT(BinTree bt,FILE *output)
{
 if(bt)
 {
 out(bt,output);
 OUTPUT(bt->first_child,output);
 OUTPUT(bt->next_sibling,output);
 }
}
/* 主函数 */
main()
{ FILE *input,*output;
 BinTree root;
 if((input=fopen("input.txt","r"))==NULL)
 {
 printf("Cannot find the file! Strike any key to exit!");
 getch();
 exit(1);
 }
 output=fopen("output.txt","w");
 root=Create_BinTree(input);
 OUTPUT(root,output);
 getch();
 fclose(input);fclose(output);
}
