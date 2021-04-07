#include "stdio.h"
#include "string.h"
#define Null 0
#define MAX 200
 /*�����ļ�ÿ��Ӧ������MAX���ַ�*/

typedef struct node /*���ú����ֵ�˫������Ĵ洢�ṹ*/
{
char name[12];
unsigned int size;
struct node *parent,*first_child,*next_sibling;
}BinTNode,*BinTree;

/* ����½ڵ� */
BinTree New_BinTNode(char str[],int *I,BinTree parentArray[],int *head,int *rear)
{ int i=0;
 BinTree bt;
 bt=(BinTNode *)malloc(sizeof(BinTNode));
 bt->parent=parentArray[*head]; /*����˫�׽��ȷ������Ŀ¼*/
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
 while ((str[*I]!=' ')&&(str[*I]!=')')&&((*I)<strlen(str)-1)) /*����(*I)<strlen(str)-1)�ǿ��ǵ����ڵ�û�С� ����')'*/
 {
 bt->size=bt->size*10+(str[*I]-'0');
 (*I)++;
 }
 return bt;
}
/* �������ݣ�����������ת��Ϊ�����õ����ṹ) */
BinTree Create_BinTree(FILE *input)
{ int I=0,rear=0,head=1; /*parentArray[head]������¼��ǰ�ڵ�Ӧָ���parentĿ¼�ڵ�*/
 /*parentArray[rear]������¼���һ��Ŀ¼�ڵ�*/
 BinTree parentArray[MAX];/*parentArray[]������¼���е�Ŀ¼�ڵ��ַ*/
 BinTree root,bt,pbt;
 char str[MAX];
 fgets(str,MAX,input);
 root=New_BinTNode(str,&I,parentArray,&head,&rear);
 root->parent=Null; /* �ڴ������ڵ�ʱ��parent�ĸ�ֵ������ģ�����������ؿ� */
 while(!feof(input))
 {I=1; /*I�������ļ�ÿ���ַ����е��±꣬�ᴩ�����ַ�����ʼĩ*/
 fgets(str,MAX,input);
 while(I<=(strlen(str)-1))
 {
 if(str[I]!=')')
 {
 bt=New_BinTNode(str,&I,parentArray,&head,&rear);
 parentArray[head]->first_child=bt;
 pbt=bt;
 do /*����������һ��������������ֵܽڵ�*/
 {
 if(str[I]==' ')
 {
 I++;
 pbt->next_sibling=New_BinTNode(str,&I,parentArray,&head,&rear); /*�����ֵܽڵ�*/
 pbt=pbt->next_sibling;
 }
 }while(str[I]!=')') ;
 head++; I=I+3; /* ��ʱ����������head+1������һ��Ŀ¼��I+3����") (" */
 }
 else
 {head++ ; I=I+3;} /* ��ʱҲ���������� */
 }
 }
 return root;
}

/* ��Ŀ¼��С */
int SIZE(BinTree bt) /*���ص�ǰĿ¼�������Ĵ�С��δ����ԭĿ¼��С��*/
{ int size;
 if(bt)
 size=bt->size+SIZE(bt->first_child)+SIZE(bt->next_sibling);
 else size=0;
 return size;
}
/* ��������ڵ� */
void out(BinTree bt,FILE *output)
{ char size_str[10];
 BinTree pbt=bt->parent;
 int i=-1,j=0,k;
 int flag[11]; /*flag[i]����������������Ŀ¼��ȿ������ã�Ŀǰ��Ϊ11*/
 for(k=0;k<11;k++) flag[k]=0;
 if(bt->name[0]=='*') bt->size=bt->size+SIZE(bt->first_child);
 /*Ŀ¼�Ĵ�СΪ��Ŀ¼�����С�����������������һ������Ϊ�����������нڵ��size��*/
 while(pbt!=Null)
 {
 i++;
 if(pbt->next_sibling) flag[j]=1; /*���ʱflag[i]=1����"| ?" */
 else flag[j]=0; /*���ʱflag[i]=0����" " */
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

/* ���������������� */
void OUTPUT(BinTree bt,FILE *output)
{
 if(bt)
 {
 out(bt,output);
 OUTPUT(bt->first_child,output);
 OUTPUT(bt->next_sibling,output);
 }
}
/* ������ */
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
