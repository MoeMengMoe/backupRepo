#include <stdio.h>
int main(){
    float num1,num2;
    char add;
    scanf("%f%c%f",&num1,&add,&num2);
    switch(add){
        case '+':
        printf("%.2f",num1+num2);
        break;
        case '*':
        printf("%.2f",num1*num2);
        break;
        case '/':
        printf("%.2f",num1/num2);
        break;
        case '-':
        printf("%.2f",num1-num2);
        break;
        default :
        printf("error\n");
        break;
    }
 
   return 0;
}