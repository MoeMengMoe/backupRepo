#include <stdio.h>
#include <string.h>
int minimum(int a,int b){if (a<=b){return a;}else {return b;}}//arguments are defined with char which means string not array
void CheckArraySame(char array1[],char array2[]){//dont forget to change here
    char *p1=array1;//pointer -->arrayname no[]
    char *p2=array2;
    if (strlen(array1)!=strlen(array2)){printf("not equal");return;}//you can just compare if it is \0 
    int n=minimum(strlen(array1),strlen(array2));
    for (int i=0;i<n;i++){
        if (*p1==*p2){//you forget to change the position of p1 p2 here!
            p1 ++;
            p2 ++;
            continue;
        }
        else
        {
            printf("not equal");
            return;
        }
    }
    printf("equal");

}
int main(){
    char str1[]="hell0";
    char str2[]="hello";
    CheckArraySame(str1,str2);
    return 0;
}