//#include <stdio.h>
/*#include <stdio.h> 
int main () { 
int i, j; 
for(i = 2; i<9; i++) { 
for(j = 1; j <= i/j; j++){ 
if( !(i%j) ){ 
continue; 
} 
} 
 
    if(j > (i/j)){ 
         printf("%d ", i); 
    } 
  } 
   return 0; 
}*/
// Code file created by C Code Develop

#include <stdio.h>





int main() {
    int aim_x, aim_y, horse_x, horse_y;
    scanf("%d %d %d %d", &aim_x, &aim_y, &horse_x, &horse_y);
    int bb[][2] = {{-1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {2, 1}, {2, -1}};   
    //int bx[] = {-1, -2, 1, 2};
    //int by[] = {-1, -2, 1, 2};
    int location[21][21] = {0} ;
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            location[i][j] = 1;
        }
    }
    
    for (int i = 0 ; i < 8; i++){
        int dx = horse_x+bb[i][0];
        int dy = horse_y+bb[i][1];
        if(dx>=0&&dx<=20&&dy>=0&&dy<=20)location[dx][dy] = 0;
    } 
    location[horse_x][horse_y]=0;
    long long dp[21][21];
    dp[0][0]=0;
    
    for(int i=0;i<21;i++){if(location[i][0]!= 0)
            
            {dp[i][0] = 1;} else dp[i][0] = 0;
            if(location[0][i]!= 0)
            {dp[0][i] = 1; }else {dp[0][i]=0;}
            for(int i = 1; i <= aim_x; i++){
            
            //if(location[][j]==0){printf("0\n"); break; 
            for(int j = 1; j <= aim_y; j++ ){
            //if(location[i-1][j] == 0||location[i][j-1] == 0)continue;
            
           
            
            if(location[i][j]!= 0)
            {dp[i][j] = dp[i-1][j]+dp[i][j-1]; }
            
            }
            
            
            
                      
           
        }
         
    }
    int result=dp[aim_x][aim_y];
    printf("%d",result);  
    
    return 0;
}
