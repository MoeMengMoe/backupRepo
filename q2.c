# include <stdio.h>
int * intarray(int howlarge){
    int myarray[howlarge];
    for(int i=0;i<howlarge;i++){
        myarray[i]=i;
    }
    return myarray;
}
int main(){
    int *p=intarray(2);
    for(int i=0;i<2;i++){
        printf("%d",p[i]);
    }
    return 0;
}