#include <stdio.h>


// int main() {
//     int aim_x, aim_y, horse_x, horse_y;
//     scanf("%d %d %d %d", &aim_x, &aim_y, &horse_x, &horse_y);
//     int bb[][2] = {{-1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {2, 1}, {2, -1}};   
//     //int bx[] = {-1, -2, 1, 2};
//     //int by[] = {-1, -2, 1, 2};
//     int location[21][21] = {0} ;
//     for(int i = 0; i < 21; i++){
//         for(int j = 0; j < 21; j++){
//             location[i][j] = 1;
//         }
//     }
    
//     for (int i = 0 ; i < 8; i++){
//         int dx = horse_x+bb[i][0];
//         int dy = horse_y+bb[i][1];
//         if(dx>=0&&dx<=20&&dy>=0&&dy<=20)location[dx][dy] = 0;
//     } 
//     location[horse_x][horse_y]=0;
//     long long dp[21][21];
//     dp[0][0]=0;
    
//     for(int i=0;i<21;i++){if(location[i][0]!= 0)
            
//             {dp[i][0] = 1;} else dp[i][0] = 0;
//             if(location[0][i]!= 0)
//             {dp[0][i] = 1; }else {dp[0][i]=0;}
//             for(int i = 1; i <= aim_x; i++){
            
//             //if(location[][j]==0){printf("0\n"); break; 
//             for(int j = 1; j <= aim_y; j++ ){
//             //if(location[i-1][j] == 0||location[i][j-1] == 0)continue;
            
           
            
//             if(location[i][j]!= 0)
//             {dp[i][j] = dp[i-1][j]+dp[i][j-1]; }
            
//             }
            
            
            
                      
           
//         }
         
//     }
//     int result=dp[aim_x][aim_y];
//     printf("%d",result);  
    
//     return 0;
// }
int main() {
    int aim_x, aim_y, horse_x, horse_y;
    scanf("%d %d %d %d", &aim_x, &aim_y, &horse_x, &horse_y);


    int offset[8][2] = {{-2, -1}, {-2, 1},   {-1, -2}, {-1, 2},   {1, -2},   {1, 2},   {2, -1},  {2, 1}    
    };

    
    int location[21][21];

    
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            location[i][j] = 1;
        }
    }

   
    location[horse_x][horse_y] = 0;
    for (int i = 0; i < 8; i++) {
        int mx = horse_x + offset[i][0];
        int my = horse_y + offset[i][1];
        if (mx >= 0 && mx <= 20 && my >= 0 && my <= 20) {
            location[mx][my] = 0;
        }
    }

    
    int dp[21][21] = {0};

   
    if (location[0][0] == 1) {
        dp[0][0] = 1;
    }

    
    for (int i = 1; i <= aim_x; i++) {
        if (location[i][0] == 1) {
            dp[i][0] = dp[i-1][0];  
        } else {
            dp[i][0] = 0;
        }
    }

  
    for (int j = 1; j <= aim_y; j++) {
        if (location[0][j] == 1) {
            dp[0][j] = dp[0][j-1];  
        } else {
            dp[0][j] = 0;
        }
    }

 
    for (int i = 1; i <= aim_x; i++) {
        for (int j = 1; j <= aim_y; j++) {
            if (location[i][j] == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

 
    printf("%d\n", dp[aim_x][aim_y]);

    return 0;
}



