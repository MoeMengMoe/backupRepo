# include <stdio.h>
void drawstars(int aim){
    int i,s;
    for(i=1;i<=aim;i++){//for loops need  ;   to divide each sentence,not ,
        for(s=1;s<=i;s++){
            printf("*");

        }
        //if(s==i){
            printf("\n");
        //}
    }
}
int main(){
    int aim;
    scanf("%d",&aim);
    drawstars(aim);
}