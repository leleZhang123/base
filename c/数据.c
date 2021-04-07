#include <iostream>
using namespace std;
#define MAX_VEX 20//��󶥵���
#define INFINITY 32767
#define QUEUE_SIZE (MAX_VEX+1)//���г���
bool* visited;//���ʱ�־����
//����Graph�Ľṹ
typedef struct
{
char* vexs;//��������
int arcs[MAX_VEX][MAX_VEX];//�ڽӾ���
int vexnum,arcnum;//ͼ�еĶ������ͻ���
}Graph;
//������
class Queue
{
public:
int front,rear;
int* base;
public:
void InitQUeue();
void EnQueue(int e);
void DeQueue(int &e);
};
void Queue::InitQUeue()
{
base=(int*)malloc(QUEUE_SIZE*sizeof(int));
front=rear=0;
}
void Queue::EnQueue(int e)

{
base[rear]=e;
rear=(rear+1)%QUEUE_SIZE;
}
void Queue::DeQueue(int& e)
{
e=base[front];
front=(front+1)%QUEUE_SIZE;
}
//ͼG�в���Ԫ��c��Ӧ���±�
int Locate(Graph G,char c)
{
int i;
for(i=0;i<G.vexnum;i++)
if(G.vexs[i]==c)
return i;
return -1;
}
//��������ͼ��
void CreateUDN(Graph &G)
{
int i,j,w,s1,s2;
char a,b;
printf("���붥�����ͻ�����\n");
scanf("%d%d",&G.vexnum,&G.arcnum);
getchar();
G.vexs=(char*)malloc(G.vexnum*sizeof(char));//���䶥����Ŀ
printf("����%d�����㡣\n",G.vexnum);
for(i=0;i<G.vexnum;i++)
{
printf("���붥��%d:",i);
scanf("%c",&G.vexs[i]);
getchar();
}
//��ʼ���ڽӾ���
for(i=0;i<G.vexnum;i++)
for(j=0;j<G.vexnum;j++)
G.arcs[i][j]=INFINITY;
printf("����%d����\n",G.arcnum);
for(i=0;i<G.arcnum;i++)
{
printf("���뻡%d:",i);
scanf("%c %c %d",&a,&b,&w);//����һ�����Ķ����Ȩ��
getchar();
s1=Locate(G,a);
s2=Locate(G,b);
G.arcs[s1][s2]=G.arcs[s2][s1]=w;
}
//ͼG�ж���k�ĵ�һ���ڽӶ���
int FirstVex(Graph G,int k)
{
if(k>=0&&k<G.vexnum)
{
for(int i=0;i<G.vexnum;i++)
if(G.arcs[k][i]!=INFINITY)
return i;
}
return -1;
}
//ͼG�ж���i�ĵ�j���ڽӶ������һ������
int NextVex(Graph G,int i,int j)
{
if(i>=0&&i<G.vexnum&&j>=0&&j<G.vexnum)
{
for(int k=j+1;k<G.vexnum;k++)
if(G.arcs[i][k]!=INFINITY)
return k;
}
return -1;
}
//������ȱ���
void DFS(Graph G,int k)
{
int i;
if(k==-1)
{
for(i=0;i<G.vexnum;i++)
if(!visited[i])
DFS(G,i);
}
else
{
visited[k]=true;
printf("%c ",G.vexs[k]);//���ʵ�k������
for(i=FirstVex(G,k);i>=0;i=NextVex(G,k,i))
if(!visited[i])
DFS(G,i);
}
}
//������ȱ���
void BFS(Graph G)
{
int i,k,w;
Queue Q;
Q.InitQUeue();
for(i=0;i<G.vexnum;i++)
{
if(!visited[i])
{
visited[i]=true;
printf("%c ",G.vexs[i]);
Q.EnQueue(i);
while(Q.front!=Q.rear)
{
Q.DeQueue(k);
for(w=FirstVex(G,k);w>=0;w=NextVex(G,k,w))
if(!visited[w])
{
printf("%c ",G.vexs[w]);
visited[w]=true;
Q.EnQueue(w);
}
}
}
}

}
//������
void main()
{
int i;
Graph G;
CreateUDN(G);
visited=(bool*)malloc(G.vexnum*sizeof(bool));
for(i=0;i<G.vexnum;i++)
visited[i]=false;
printf("������ȱ���:\n");
DFS(G,-1);
printf("\n������ȱ���\n");
for(i=0;i<G.vexnum;i++)
visited[i]=false;
BFS(G);
printf("\n�������.\n");
getchar();

