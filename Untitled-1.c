# include <stdio.h>
void drawstars(int aim){
    int i,s;
    for(i=1;i<=aim;i++){//for loops need  ;   to divide each sentence,not ,
        for(s=1;s<=i;s++){
            printf("*在");

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