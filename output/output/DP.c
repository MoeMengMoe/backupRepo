// # include <stdio.h>
// typedef struct{
//     int x;
//     int y;
//     int blocked;
// }location;
// typedef struct{
//     int location;
//     int y;
//     int blocked;
// }blocked;


// void GetBlocked(int horse[][2],int blockedlocation[8][2]){
//     location blocked;

//     int blockedlocation[8][2];
//     int blockedArea[8][2]={{+2,+1},{-2,+1},{+1,+2},{-1,+2},{+2,-1},{-2,-1},{+1,-2},{-1,-2}};
//     for(int i=0;i<8;i++){
//         blockedlocation[i][0]=horse[i][0]+blockedArea[i][0];
//         blockedlocation[i][1]=horse[i][1]+blockedArea[i][1];
            
//         }
        
//     }
// int wayNum(int x,int y){
//     for(int i=0;i<8;i++){
        
//     }        
// }


// int main(){
//     int horse[1][2],aim[1][2],blockedlocation[8][2];
//     scanf("%d %d %d %d",&aim[0][0],&aim[0][1],&horse[0][0],&horse[0][1]);
//     GetBlocked(horse,blockedlocation);




// }
#include <stdio.h>

int dp(int x,int y,int blocked[][21]){
    if(blocked[x][y]){return 0;}
    if(x==0&&y==0){return 1;}
    if(x==0&&y==1){return 1;}
    if(x==1&&y==0){return 1;}
    if(x>=0 &&y>=0){
        int sum=dp(x-1,y,blocked)+dp(x,y-1,blocked);
        return sum;
    }
    
}

int main(){
    int aim_x,aim_y,horse_x,horse_y,num;
    
    scanf("%d %d %d %d",&aim_x,&aim_y,&horse_x,&horse_y);
    int blockedArea[8][2]={{+2,+1},{-2,+1},{+1,+2},{-1,+2},{+2,-1},{-2,-1},{+1,-2},{-1,-2}};
    int blocked[21][21]={0};
    blocked[horse_x][horse_y]=1;
    for(int i=0;i<8;i++){
        int nx =horse_x+blockedArea[i][0];
        int ny=horse_y+blockedArea[i][1];
        if(nx<=20&&ny<=20&&nx>=0&&ny>=0){
            blocked[nx][ny]=1;
        }
    }

    num=dp(aim_x,aim_y,blocked);
    printf("%d",num);


}