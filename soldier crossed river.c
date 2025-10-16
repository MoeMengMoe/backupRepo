#include <stdio.h>

int main() {
    int aim_x, aim_y, horse_x, horse_y;
    scanf("%d %d %d %d", &aim_x, &aim_y, &horse_x, &horse_y);

    // 使用二维数组标记马的8个控制方向偏移量
    int offset[8][2] = {
        {-2, -1}, // 左上
        {-2, 1},  // 右上
        {-1, -2}, // 左上
        {-1, 2},  // 右上
        {1, -2},  // 左下
        {1, 2},   // 右下
        {2, -1},  // 左下
        {2, 1}    // 右下
    };

    // 棋盘：1=可通行，0=不可通行
    int location[21][21];

    // 1. 初始化为可通行
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            location[i][j] = 1;
        }
    }

    // 2. 标记马的位置和控制点
    location[horse_x][horse_y] = 0;
    for (int i = 0; i < 8; i++) {
        int mx = horse_x + offset[i][0];
        int my = horse_y + offset[i][1];
        if (mx >= 0 && mx <= 20 && my >= 0 && my <= 20) {
            location[mx][my] = 0;
        }
    }

    // 3. dp[i][j]: 从(0,0)到(i,j)的路径数
    long long dp[21][21] = {0};

    // 4. 起点
    if (location[0][0] == 1) {
        dp[0][0] = 1;
    }

    // 5. 第一列 (j=0)
    for (int i = 1; i <= aim_x; i++) {
        if (location[i][0] == 1) {
            dp[i][0] = dp[i-1][0];  // 只能从上方来
        } else {
            dp[i][0] = 0;
        }
    }

    // 6. 第一行 (i=0)
    for (int j = 1; j <= aim_y; j++) {
        if (location[0][j] == 1) {
            dp[0][j] = dp[0][j-1];  // 只能从左方来
        } else {
            dp[0][j] = 0;
        }
    }

    // 7. 填表
    for (int i = 1; i <= aim_x; i++) {
        for (int j = 1; j <= aim_y; j++) {
            if (location[i][j] == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

    // 8. 输出
    printf("%lld\n", dp[aim_x][aim_y]);

    return 0;
}



