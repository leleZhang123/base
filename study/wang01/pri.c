# include<stdio.h>
int main(){
    for( int i =1;i<=5;i++){
        if(i%2){
            printf("$");
        }else{
            printf("@");
        }
    }
    return 0;
}