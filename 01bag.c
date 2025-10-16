/*0-1 bag problem 给定 
 个物品，第 
 个物品的重量为 
、价值为 
 ，和一个容量为 
 的背包。每个物品只能选择一次，问在限定背包容量下能放入物品的最大价值。*/
#include<stdio.h>
int max(int x,int y){ return (x > y) ? x : y;}


int main(){
    int n,cap;
    scanf("%d",&n);
    scanf("%d",&cap);
    int val[n];
    int wgt[n];
    int dp[n][cap+1];
    for(int i=0;i<n;i++){
        scanf("%d %d",&val[i],&wgt[i]);
    }

    dp[0][0]=0;
   
    

    for(int i =1;i<n;i++){
        for(int j=1;j<=cap;j++){
            if(j<wgt[i])dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-wgt[i]]+val[i]);
        }
    }
    printf("%d",dp[n-1][cap]);
    return 0;
}