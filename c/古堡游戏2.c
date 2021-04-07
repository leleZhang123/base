#include<stdio.h>
int main()
{void go(); 
int help();
void out();
   void north();
   void east();
  void west();
  void south();
char a,b,c;
int i,number=1000;
	printf("欢迎来到一个无聊的游戏：\n");
	printf("请输入你的要求：1.go 2.help 3.bye！！\n");
	scanf("%c",&b);
 			for(i=0;i<number;i++)
			 {
			 
				while(b=='\n'){
					scanf("%c",&a);
			     
				          if(a=='1'){go();
					}else if(a=='2'){int help();printf("起输入4，之后输入方向键！\n"); 
					
					}else if(a=='3'){out(); printf("这里没路！");  break;
					 
					}else if(a=='4') break;
					
					
					 }
			    while(a=='4'){
		          	scanf("%c",&c);
						{     if(c=='w'){ printf("这里是卧室。");east();printf("或者返回出口请向下走！"); 
						}else if(c=='a')  { printf("这里是会客厅。");south(); 
						}else if(c=='s')  {  printf("这里是书房。");north(); 
						}else if(c=='d')  {  printf("这里是食堂。");west(); 
						}else if(c=='x')  {
						out();break;}
						
				}}	
			} 
}
void go()
{

	printf("起输入数字：\n如需帮助请输入2.");
}
int help()
{
	printf("你好");
	return 0; 
}	   
void out()
{printf("这里是出口！"); 
} 
 void east()
 {
 	printf("请向东走！");
 }   void west()
 {
 	printf("请向西走！");
 }   void north()
 {
 	printf("请向北走！");
 }   void south()
 {
 	printf("请向南走！");
 }  
