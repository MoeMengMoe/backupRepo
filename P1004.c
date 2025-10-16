#include<stdio.h>
int  max(int p1,int p2){
    if(p1>p2)return p1;else  return p2;}

int main(){
    int n;
    scanf("%d",&n);
    int dp[n][n];
    int grip[n][n];
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dp[i][j]=0;
            grip[i][j]=0;
        }
    }
    while(1){
        int x,y,num;
        scanf("%d %d %d",&x,&y,&num);
        grip[x][y]=num;
        if(x==0&&y==0&&num==0)break;
    }
    for(int i=0;i<n;i++){
        dp[0][i]=grip[0][i]+dp[0][i-1];
        dp[i][0]=grip[i][0]+dp[i-1][0];
    }
    
    
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1])+grip[i][j];
            if(dp[i-1][j]>dp[i][j-1])grip[i-1][j]=0;else grip[i][j-1]=0;
            
        }
    }

    int sum =dp[n-1][n-1];
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1])+grip[i][j];
            
            
        }
    }
    sum +=dp[n-1][n-1];
    printf("%d",sum);
    return 0;
}
//wrong 
//wrong 
//wrong 贪心错误：第一次走“最大路径”不一定能让两次总和最大。
//破坏原始数据：修改 grip 后，第二次走的数据已经不对。
//无法回溯：你不能决定哪条路径该让哪条路。