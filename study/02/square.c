#include<stdio.h>
int main(){
    int j = 0;
    //循环四次
    for(int i=0;i<4;i++){
        j = i*2;
        //j的值为:0,2,4,6
        while(j--){
            printf(" ");
        }
        //输出*****
        printf("*****\n");
    }
    return 0;
}
/*
结果为:
*****
  *****
    *****
      *****

*/
