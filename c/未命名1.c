#include<stdio.h>
#include<string.h>
int main ()
	{	
	char Data_change();	
	int a[4],N,i,j,size=20;
	            char c; 
	            char b[20]; 
    		       struct Tel
						{char name[20];               //���� 
						 char post[20];               //��λ    
						 int telnum;                  //���� 
						 char email[20];              //email 
						} ;
					struct Tel telInfo[size];
				
					struct Tel *p;
					p=telInfo;
					printf("��鿴ͨѶ¼���У�");
//					for(i=0;i<size;i++) 
					scanf("%s%s%d%s",&telInfo[i].name,&telInfo[i].post,&telInfo[i].telnum,&telInfo[i].email);//�������� 
				     FILE* fp;//�����ļ�ָ�� 	 
				
					printf("��������ĸ�������²�����A.�޸����ݣ�B.�������ݣ�C.ɾ�����ݣ�D.��ʾ���ݣ�E.������F.������\n");
					while(1==1)
					{	scanf("%c",&c);
							      if(c=='a'){       b[20]=Data_change();
								  for(i=0;i<20;i++){if(b[i]==*p->name){printf("ni");
								  }
								  }
							}else if(c=='b'){if((fp =fopen("D:\\c.txt","wb")==NULL))
					                         {printf("�޷����ļ���");					                           exit(0); 
											   for(i=0;i<size;i++){
					                           fwrite(&telInfo[1],sizeof(struct Tel),20,fp);
					                           printf("%s%s%d%s",telInfo[i].name,telInfo[i].post,telInfo[i].telnum,telInfo[i].email);
											   };
											   fclose(fp);}
							}else if(c=='c'){
							}else if(c=='d'){
							}else if(c=='e'){						
							}else if(c=='f'){printf("������");break; 
							}
							
					}
					return 0; 
	}
char Data_change()

 {char str[20];
 int c[20];
int  a;
 printf("�����1.������2.���롣�����룺");scanf("%c",&a);
 if(a=='1'){
 printf("�����û�����");
 scanf("%s",&str); }
 else if(a=='2'){printf("�����û����룺");
 scanf("%d",&c);}
 
//  if((fp =fopen("D:\\c.txt","wb")==NULl);
//   {printf("�޷����ļ���");}				
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	 
