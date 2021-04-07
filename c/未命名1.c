#include<stdio.h>
#include<string.h>
int main ()
	{	
	char Data_change();	
	int a[4],N,i,j,size=20;
	            char c; 
	            char b[20]; 
    		       struct Tel
						{char name[20];               //名字 
						 char post[20];               //单位    
						 int telnum;                  //号码 
						 char email[20];              //email 
						} ;
					struct Tel telInfo[size];
				
					struct Tel *p;
					p=telInfo;
					printf("请查看通讯录表列：");
//					for(i=0;i<size;i++) 
					scanf("%s%s%d%s",&telInfo[i].name,&telInfo[i].post,&telInfo[i].telnum,&telInfo[i].email);//输入数据 
				     FILE* fp;//定义文件指针 	 
				
					printf("请输入字母进行以下操作：A.修改数据，B.插入数据，C.删除数据，D.显示数据，E.搜索，F.结束。\n");
					while(1==1)
					{	scanf("%c",&c);
							      if(c=='a'){       b[20]=Data_change();
								  for(i=0;i<20;i++){if(b[i]==*p->name){printf("ni");
								  }
								  }
							}else if(c=='b'){if((fp =fopen("D:\\c.txt","wb")==NULL))
					                         {printf("无法打开文件！");					                           exit(0); 
											   for(i=0;i<size;i++){
					                           fwrite(&telInfo[1],sizeof(struct Tel),20,fp);
					                           printf("%s%s%d%s",telInfo[i].name,telInfo[i].post,telInfo[i].telnum,telInfo[i].email);
											   };
											   fclose(fp);}
							}else if(c=='c'){
							}else if(c=='d'){
							}else if(c=='e'){						
							}else if(c=='f'){printf("结束。");break; 
							}
							
					}
					return 0; 
	}
char Data_change()

 {char str[20];
 int c[20];
int  a;
 printf("如果改1.姓名；2.号码。请输入：");scanf("%c",&a);
 if(a=='1'){
 printf("输入用户名：");
 scanf("%s",&str); }
 else if(a=='2'){printf("输入用户号码：");
 scanf("%d",&c);}
 
//  if((fp =fopen("D:\\c.txt","wb")==NULl);
//   {printf("无法打开文件！");}				
 return (a);
}
void Ins(){ 
					 
}	
void Del(){
}	
void Disp(){
}	
void Searsh(){
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	 
