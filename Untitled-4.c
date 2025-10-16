#include<stdio.h>
int main(){
    // int n=5;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=i;j++){
    //         printf("*");
    //     }
    //     printf("\n");
    // }
 
    // return 0;
    int n =5;
    for(int i=1;i<=n;i++){//可以写对称

        if(i*2>=n)break;
        for(int j=0;j<i;j++){
            printf("*");
        }
        for(int j=0;j<n-2*i;j++){
            printf(" ");

        }
        for(int j=0;j<i;j++){
            printf("*");
        }
        printf("\n");
        
    }
    for(int i=0;i<n;i++){
        printf("*");
    }
}