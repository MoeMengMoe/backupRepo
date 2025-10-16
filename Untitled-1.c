#include <stdio.h>
int GetLargestNum(int * inputarray,int quan){
    int largestnum =inputarray[0] ;  // you should initialise it with array[0] because the num will be random!
    for (int i = 0;i< quan;i++){//remember to use : but not , in for!!!  also i< quan coz  array is cal from 0!
        if (inputarray[i] > largestnum){
            largestnum =   inputarray[i];
        }
    }
    return largestnum;


}
int main(){
    int myarray[]={12,32,282,39,0};
    int quan =sizeof(myarray)/sizeof(int);
    int output=GetLargestNum(myarray,quan);
    printf("%d",output);//this is printf not scanf


}