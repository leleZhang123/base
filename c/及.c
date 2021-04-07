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
int num=0;//外部变量num为文件中的纪录数 
FILE *fp; 
void mainmenu();//主菜单 
void newrecord();//插入纪录 
void searchmenu();//查询菜单 
void searchbyname();//按姓名查询 
void searchbyphone();//按电话查询 
void deletemenu();//删除菜单 
void deleteall();//删除所有  
void showall();//显示所有 
void readfromfile();//读取文件 
void writetofile();//写入文件  
void deletebyname();//按姓名删除 
void main() 
{ 
readfromfile(); 
while (1) 
{ 
mainmenu(); 
} 
} 
void readfromfile()//从文件导入 
{ 
if((fp=fopen("TelInfo.bin","rb"))==NULL) 
{ 
printf("\n\t\t通讯录文件不存在"); 
if ((fp=fopen("TelInfo.bin","wb"))==NULL) 
{ 
printf("\n\t\t建立失败"); 
exit(0); 
} 
else 
{ 
printf("\n\t\t通讯录文件已建立"); 
printf("\n\t\t按任意键进入主菜单"); 
getch(); 
return; 
} 
exit(0); 
} 
fseek(fp,0,2); /*文件位置指针移动到文件末尾*/ 
if (ftell(fp)>0) /*文件不为空*/ 
{ 
rewind(fp); /*文件位置指针移动到文件开始位置*/ 
for (num=0;!feof(fp) && fread(&TelInfo[num],sizeof(struct record),1,fp);num++); 
printf("\n\t\t文件导入成功"); 
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
printf("\n\t\t文件导入成功"); 
printf("\n\t\t通讯录文件中无任何纪录"); 
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
void mainmenu()//主菜单 
{ 
char choic; 
system("cls"); 
printf("\n\t\t******************** 主菜单 ********************"); 
printf("\n\t\t*********** 1-插入纪录 2-查询菜单 ************"); 
printf("\n\t\t*********** 3-删除菜单 4-显示所有************"); 
printf("\n\t\t***********  5-保存退出 6-不保存退出***********"); 
printf("\n\t\t************************************************"); 
printf("\n\t\t请选择："); 
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
void searchmenu()//查询菜单 
{ 
char choic; 
system("cls"); 
printf("\n\t\t******************* 查询菜单 *******************"); 
printf("\n\t\t********** 1-显示所有  ************"); 
printf("\n\t\t********** 2-按姓名查询3-按电话查询 ************"); 
printf("\n\t\t********** 4-返回主菜单 ************"); 
printf("\n\t\t************************************************"); 
printf("\n\t\t请选择："); 
choic=getch(); 
switch (choic) 
{ 
case '1':showall();break; 
case '2':searchbyname();break; 
case '3':searchbyphone();break; 
case '4':mainmenu();break; 
} 
} 
void deletemenu()//删除菜单 
{ 
char choic; 
if(num==0) 
{ 
printf("\n\t\t对不起，文件中无任何纪录"); 
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
system("cls"); 
printf("\n\t\t******************* 删除菜单 *******************"); 
printf("\n\t\t*********** 1-删除所有 ***********"); 
printf("\n\t\t*********** 2-返回主菜单 ***********"); 
printf("\n\t\t************************************************"); 
printf("\n\t\t请选择："); 
choic=getch(); 
switch (choic) 
{ 
case '1':deleteall();break; 
case '2':mainmenu();break; 
default:mainmenu();break; 
} 
} 
void deleteall()//删除所有 
{ 
printf("\n\t\t确认删除?(y/n)"); 
if (getch()=='y') 
{ 
fclose(fp); 
if ((fp=fopen("TelInfo.bin","wb"))==NULL) 
{ 
printf("\n\t\t不能打开文件，删除失败"); 
readfromfile(); 
} 
num=0; 
printf("\n\t\t纪录已删除，按任意键返回主菜单"); 
getch(); 
return; 
} 
else 
return; 
} 
void newrecord()//插入纪录 
{ 
printf("\n\t\t**************** 请输入学生信息 ****************\n"); 
printf("\n\t\t输入姓名:"); 
scanf("%s",&TelInfo[num].name); 
printf("\n\t\t输入电话号码:"); 

scanf("%s",&TelInfo[num].phone); 
printf("\n\t\t输入地址:"); 
scanf("%s",&TelInfo[num].post); 

printf("\n\t\t输入e-mail:"); 
scanf("%s",&TelInfo[num].e_mail); 
num++; 
printf("\n\t\t是否继续添加?(Y/N):"); 
if (getch()=='y') 
newrecord(); 
return; 
} 
void showall()//显示所有 
{ 
int i; 
system("cls"); 
if(num!=0) 
{ 
printf("\n\t\t*************** 以下为通讯录所有信息************"); 
for (i=0;i<num;i++) 
{ 
printf("\n\t\t姓名： %s",TelInfo[i].name); 
printf("\n\t\t电话： %s",TelInfo[i].phone); 
printf("\n\t\t地址： %s",TelInfo[i].post); 

printf("\n\t\te-mail：%s",TelInfo[i].e_mail); 

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
printf("\n\t\t通讯录中无任何纪录"); 
printf("\n\t\t按任意键返回主菜单："); 
getch(); 
return; 
} 
void searchbyphone() 
{ 
int mark=0; 
int i; 
int a=0; 
printf("\n\t\t****************** 按电话查找 ******************"); 
char phone[10]; 
printf("\n\t\t请输入号码:"); 
scanf("%s",phone); 
for(i=0;i<num;i++) 
{ 
if (strcmp(TelInfo[i].phone,phone)==0) 
{ 
printf("\n\t\t************** 以下是您查找的学生信息 **********"); 
printf("\n\t\t姓名： %s",TelInfo[i].name); 
printf("\n\t\t电话： %s",TelInfo[i].phone); 
printf("\n\t\t地址： %s",TelInfo[i].post); 
printf("\n\t\te-mail：%s",TelInfo[i].e_mail); 
printf("\n\t\t************************************************"); 
printf("\n\t\t按任意键返回主菜单："); 
mark++; 
getch(); 
return; 
} 
} 
if (mark==0) 
{ 
printf("\n\t\t没有改学生的信息"); 
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
} 
void searchbyname()//按姓名查询 
{ 
int mark=0; 
int i; 
int a=0; 
printf("\n\t\t***************** 按姓名查找 *******************"); 
char name[20]; 
printf("\n\t\t请输入姓名:"); 
scanf("%s",name); 
for(i=a;i<num;i++) 
{ 
if (strcmp(TelInfo[i].name,name)==0) 
{ 
printf("\n\t\t************* 以下是您查找的学生信息 ***********"); 
printf("\n\t\t姓名： %s",TelInfo[i].name); 
printf("\n\t\t电话： %s",TelInfo[i].phone); 
printf("\n\t\t地址： %s",TelInfo[i].post); 
printf("\n\t\te-mail：%s",TelInfo[i].e_mail); 
printf("\n\t\t************************************************"); 
mark++; 
if ((i+1)<num) 
{ 
printf("\n\t\t是否继续查找相同名字的学生信息：(y/n)"); 
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
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
} 
} 
if(mark!=0) 
{ 
printf("\n\t\t没有相同姓名的学生纪录"); 
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
else 
{ 
printf("\n\t\t没有相同姓名的学生纪录"); 
printf("\n\t\t按任意键返回主菜单"); 
getch(); 
return; 
} 
} 
void writetofile()//写入文件 
{ 
int i; 
if ((fp=fopen("TelInfo.bin","wb"))==NULL) 
{ 
printf("\n\t\t文件打开失败"); 
} 
for (i=0;i<num;i++) 
{ 
if (fwrite(&TelInfo[i],sizeof(struct record),1,fp)!=1) 
{ 
printf("\n\t\t写入文件错误!\n"); 
} 
} 
fclose(fp); 
printf("\n\t\t通讯录文件已保存"); 
printf("\n\t\t按任意键退出程序\n\t\t"); 
exit(0); 
} 

