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
	printf("��ӭ����һ�����ĵ���Ϸ��\n");
	printf("���������Ҫ��1.go 2.help 3.bye����\n");
	scanf("%c",&b);
 			for(i=0;i<number;i++)
			 {
			 
				while(b=='\n'){
					scanf("%c",&a);
			     
				          if(a=='1'){go();
					}else if(a=='2'){int help();printf("������4��֮�����뷽�����\n"); 
					
					}else if(a=='3'){out(); printf("����û·��");  break;
					 
					}else if(a=='4') break;
					
					
					 }
			    while(a=='4'){
		          	scanf("%c",&c);
						{     if(c=='w'){ printf("���������ҡ�");east();printf("���߷��س����������ߣ�"); 
						}else if(c=='a')  { printf("�����ǻ������");south(); 
						}else if(c=='s')  {  printf("�������鷿��");north(); 
						}else if(c=='d')  {  printf("������ʳ�á�");west(); 
						}else if(c=='x')  {
						out();break;}
						
				}}	
			} 
}
void go()
{

	printf("���������֣�\n�������������2.");
}
int help()
{
	printf("���");
	return 0; 
}	   
void out()
{printf("�����ǳ��ڣ�"); 
} 
 void east()
 {
 	printf("�����ߣ�");
 }   void west()
 {
 	printf("�������ߣ�");
 }   void north()
 {
 	printf("�����ߣ�");
 }   void south()
 {
 	printf("�������ߣ�");
 }  
