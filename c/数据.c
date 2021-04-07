#include <iostream>
using namespace std;
#define MAX_VEX 20//最大顶点数
#define INFINITY 32767
#define QUEUE_SIZE (MAX_VEX+1)//队列长度
bool* visited;//访问标志数组
//定义Graph的结构
typedef struct
{
char* vexs;//顶点向量
int arcs[MAX_VEX][MAX_VEX];//邻接矩阵
int vexnum,arcnum;//图中的顶点数和弧数
}Graph;
//队列类
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
//图G中查找元素c对应的下标
int Locate(Graph G,char c)
{
int i;
for(i=0;i<G.vexnum;i++)
if(G.vexs[i]==c)
return i;
return -1;
}
//创建无向图网
void CreateUDN(Graph &G)
{
int i,j,w,s1,s2;
char a,b;
printf("输入顶点数和弧数：\n");
scanf("%d%d",&G.vexnum,&G.arcnum);
getchar();
G.vexs=(char*)malloc(G.vexnum*sizeof(char));//分配顶点数目
printf("输入%d个顶点。\n",G.vexnum);
for(i=0;i<G.vexnum;i++)
{
printf("输入顶点%d:",i);
scanf("%c",&G.vexs[i]);
getchar();
}
//初始化邻接矩阵
for(i=0;i<G.vexnum;i++)
for(j=0;j<G.vexnum;j++)
G.arcs[i][j]=INFINITY;
printf("输入%d条弧\n",G.arcnum);
for(i=0;i<G.arcnum;i++)
{
printf("输入弧%d:",i);
scanf("%c %c %d",&a,&b,&w);//输入一条弧的顶点和权重
getchar();
s1=Locate(G,a);
s2=Locate(G,b);
G.arcs[s1][s2]=G.arcs[s2][s1]=w;
}
//图G中顶点k的第一个邻接顶点
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
//图G中顶点i的第j个邻接顶点的下一个顶点
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
//深度优先遍历
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
printf("%c ",G.vexs[k]);//访问第k个顶点
for(i=FirstVex(G,k);i>=0;i=NextVex(G,k,i))
if(!visited[i])
DFS(G,i);
}
}
//广度优先遍历
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
//主函数
void main()
{
int i;
Graph G;
CreateUDN(G);
visited=(bool*)malloc(G.vexnum*sizeof(bool));
for(i=0;i<G.vexnum;i++)
visited[i]=false;
printf("深度优先遍历:\n");
DFS(G,-1);
printf("\n广度优先遍历\n");
for(i=0;i<G.vexnum;i++)
visited[i]=false;
BFS(G);
printf("\n程序结束.\n");
getchar();

