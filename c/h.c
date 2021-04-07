#include<stdio.h>
int main(){
	FILE*fp1,*fp2;
	fp1=fopen("file.dat","r");
	fp2=fopen("file.dat","w");
	 while(!foef(fp1)) putchar(getc(fp1));
	 putchar(10);
	 rewind(fp1);
	 while(!foef(fp1)) putc(getc(fp1),fp2);
	fclose(fp1);
	fclose(fp2);
	return 0; 
}
