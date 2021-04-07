#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
struct record 
{  
char name[20];
 char phone[20]; 
char post[40]; 
char e_mail[30]; }
TelInfo[500];
int num=0;//�ⲿ����numΪ�ļ��еļ�¼�� 
FILE *fp; 
void mainmenu();//���˵� 
void newrecord();//�����¼ 
void searchmenu();//��ѯ�˵� 
void searchbyname();//��������ѯ 
void searchbyphone();//���绰��ѯ 
void deletemenu();//ɾ���˵� 
void deleteall();//ɾ������  
void showall();//��ʾ���� 
void readfromfile();//��ȡ�ļ� 
void writetofile();//д���ļ�  
void deletebyname();//������ɾ�� 
void main() 
{ 
readfromfile(); 
while (1) 
{ 
mainmenu(); 
} 
} 
void readfromfile()//���ļ����� 
{ 
if((fp=fopen("TelInfo.bin","rb"))==NULL) 
{ 
printf("\n\t\tͨѶ¼�ļ�������"); 
if ((fp=fopen("TelInfo.bin","wb"))==NULL) 
{ 
printf("\n\t\t����ʧ��"); 
exit(0); 
} 
else 
{ 
printf("\n\t\tͨѶ¼�ļ��ѽ���"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
exit(0); 
} 
fseek(fp,0,2); /*�ļ�λ��ָ���ƶ����ļ�ĩβ*/ 
if (ftell(fp)>0) /*�ļ���Ϊ��*/ 
{ 
rewind(fp); /*�ļ�λ��ָ���ƶ����ļ���ʼλ��*/ 
for (num=0;!feof(fp) && fread(&TelInfo[num],sizeof(struct record),1,fp);num++); 
printf("\n\t\t�ļ�����ɹ�"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
printf("\n\t\t�ļ�����ɹ�"); 
printf("\n\t\tͨѶ¼�ļ������κμ�¼"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
void mainmenu()//���˵� 
{ 
char choic; 
system("cls"); 
printf("\n\t\t******************** ���˵� ********************"); 
printf("\n\t\t*********** 1-�����¼ 2-��ѯ�˵� ************"); 
printf("\n\t\t*********** 3-ɾ���˵� 4-��ʾ����************"); 
printf("\n\t\t***********  5-�����˳� 6-�������˳�***********"); 
printf("\n\t\t************************************************"); 
printf("\n\t\t��ѡ��"); 
choic=getch(); 
switch (choic) 
{ 
case '1':newrecord();break; 
case '2':searchmenu();break; 
case '3':deletemenu();break;  
case '4':showall();break; 
case '5':writetofile();break; 
case '6':exit(0);  
default:mainmenu(); 
} 
} 
void searchmenu()//��ѯ�˵� 
{ 
char choic; 
system("cls"); 
printf("\n\t\t******************* ��ѯ�˵� *******************"); 
printf("\n\t\t********** 1-��ʾ����  ************"); 
printf("\n\t\t********** 2-��������ѯ3-���绰��ѯ ************"); 
printf("\n\t\t********** 4-�������˵� ************"); 
printf("\n\t\t************************************************"); 
printf("\n\t\t��ѡ��"); 
choic=getch(); 
switch (choic) 
{ 
case '1':showall();break; 
case '2':searchbyname();break; 
case '3':searchbyphone();break; 
case '4':mainmenu();break; 
} 
} 
void deletemenu()//ɾ���˵� 
{ 
char choic; 
if(num==0) 
{ 
printf("\n\t\t�Բ����ļ������κμ�¼"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
system("cls"); 
printf("\n\t\t******************* ɾ���˵� *******************"); 
printf("\n\t\t*********** 1-ɾ������ ***********"); 
printf("\n\t\t*********** 2-�������˵� ***********"); 
printf("\n\t\t************************************************"); 
printf("\n\t\t��ѡ��"); 
choic=getch(); 
switch (choic) 
{ 
case '1':deleteall();break; 
case '2':mainmenu();break; 
default:mainmenu();break; 
} 
} 
void deleteall()//ɾ������ 
{ 
printf("\n\t\tȷ��ɾ��?(y/n)"); 
if (getch()=='y') 
{ 
fclose(fp); 
if ((fp=fopen("TelInfo.bin","wb"))==NULL) 
{ 
printf("\n\t\t���ܴ��ļ���ɾ��ʧ��"); 
readfromfile(); 
} 
num=0; 
printf("\n\t\t��¼��ɾ������������������˵�"); 
getch(); 
return; 
} 
else 
return; 
} 
void newrecord()//�����¼ 
{ 
printf("\n\t\t**************** ������ѧ����Ϣ ****************\n"); 
printf("\n\t\t��������:"); 
scanf("%s",&TelInfo[num].name); 
printf("\n\t\t����绰����:"); 

scanf("%s",&TelInfo[num].phone); 
printf("\n\t\t�����ַ:"); 
scanf("%s",&TelInfo[num].post); 

printf("\n\t\t����e-mail:"); 
scanf("%s",&TelInfo[num].e_mail); 
num++; 
printf("\n\t\t�Ƿ�������?(Y/N):"); 
if (getch()=='y') 
newrecord(); 
return; 
} 
void showall()//��ʾ���� 
{ 
int i; 
system("cls"); 
if(num!=0) 
{ 
printf("\n\t\t*************** ����ΪͨѶ¼������Ϣ************"); 
for (i=0;i<num;i++) 
{ 
printf("\n\t\t������ %s",TelInfo[i].name); 
printf("\n\t\t�绰�� %s",TelInfo[i].phone); 
printf("\n\t\t��ַ�� %s",TelInfo[i].post); 

printf("\n\t\te-mail��%s",TelInfo[i].e_mail); 

printf("\t\t"); 
if (i+1<num) 
{ 
printf("\n\t\t__________________________"); 
system("pause"); 
} 
} 
printf("\n\t\t************************************************"); 
} 
else 
printf("\n\t\tͨѶ¼�����κμ�¼"); 
printf("\n\t\t��������������˵���"); 
getch(); 
return; 
} 
void searchbyphone() 
{ 
int mark=0; 
int i; 
int a=0; 
printf("\n\t\t****************** ���绰���� ******************"); 
char phone[10]; 
printf("\n\t\t���������:"); 
scanf("%s",phone); 
for(i=0;i<num;i++) 
{ 
if (strcmp(TelInfo[i].phone,phone)==0) 
{ 
printf("\n\t\t************** �����������ҵ�ѧ����Ϣ **********"); 
printf("\n\t\t������ %s",TelInfo[i].name); 
printf("\n\t\t�绰�� %s",TelInfo[i].phone); 
printf("\n\t\t��ַ�� %s",TelInfo[i].post); 
printf("\n\t\te-mail��%s",TelInfo[i].e_mail); 
printf("\n\t\t************************************************"); 
printf("\n\t\t��������������˵���"); 
mark++; 
getch(); 
return; 
} 
} 
if (mark==0) 
{ 
printf("\n\t\tû�и�ѧ������Ϣ"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
} 
void searchbyname()//��������ѯ 
{ 
int mark=0; 
int i; 
int a=0; 
printf("\n\t\t***************** ���������� *******************"); 
char name[20]; 
printf("\n\t\t����������:"); 
scanf("%s",name); 
for(i=a;i<num;i++) 
{ 
if (strcmp(TelInfo[i].name,name)==0) 
{ 
printf("\n\t\t************* �����������ҵ�ѧ����Ϣ ***********"); 
printf("\n\t\t������ %s",TelInfo[i].name); 
printf("\n\t\t�绰�� %s",TelInfo[i].phone); 
printf("\n\t\t��ַ�� %s",TelInfo[i].post); 
printf("\n\t\te-mail��%s",TelInfo[i].e_mail); 
printf("\n\t\t************************************************"); 
mark++; 
if ((i+1)<num) 
{ 
printf("\n\t\t�Ƿ����������ͬ���ֵ�ѧ����Ϣ��(y/n)"); 
if (getch()=='y') 
{ 
a=i; 
continue; 
} 
else 
return; 
} 
else 
{ 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
} 
} 
if(mark!=0) 
{ 
printf("\n\t\tû����ͬ������ѧ����¼"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
else 
{ 
printf("\n\t\tû����ͬ������ѧ����¼"); 
printf("\n\t\t��������������˵�"); 
getch(); 
return; 
} 
} 
void writetofile()//д���ļ� 
{ 
int i; 
if ((fp=fopen("TelInfo.bin","wb"))==NULL) 
{ 
printf("\n\t\t�ļ���ʧ��"); 
} 
for (i=0;i<num;i++) 
{ 
if (fwrite(&TelInfo[i],sizeof(struct record),1,fp)!=1) 
{ 
printf("\n\t\tд���ļ�����!\n"); 
} 
} 
fclose(fp); 
printf("\n\t\tͨѶ¼�ļ��ѱ���"); 
printf("\n\t\t��������˳�����\n\t\t"); 
exit(0); 
} 

