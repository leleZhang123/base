#include<stdio.h>
#include<math.h>
void base(int);
void numberTrap(int);
void cir(int,int,int);
void main(){
    int i=1,j=1;
    int n;
    printf("input number:");
    scanf("%d",&n);
    base(n);
    numberTrap(n);
    cir(n,i,j);
}
//基本格式:1 1 2 3 5 8 13 21 ......
//基本写法
void base(int n){
    int i,j,sum,k;
    i=1,j=1;
    printf("%d %d ",i,j);
    for(k=1;k<=n-2;k++)
    {
        sum = i+j;
        i=j;
        j=sum;
        printf("%d ",sum);
    }  
    printf("\n");
}

/*
数组方式
*/
void numberTrap(int n){
    int a[10]= {0};
    int sum,i;
    a[0]=a[1]=1;
    for(i=2;i<n;i++){
       a[i]= a[i-1]+a[i-2];  
    }
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

}




/*
递归方式
*/
void cir(int n,int i,int j){
    int sum;
    if(n==0||n==1){
        printf("%d %d ",i,j);
        sum = i+j;
    }else{
        cir(n-2,i,j);
        sum +=j;
        printf("%d ",sum);
    }
}