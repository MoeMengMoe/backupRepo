#include <stdio.h>
#include <string.h>

/**
 * @brief 记忆化递归计算向右/向下的有效路径数
 * @param x 当前位置的x坐标（向下为正方向）
 * @param y 当前位置的y坐标（向右为正方向）
 * @param blocked 阻塞位置数组（1=阻塞，0=可通行）
 * @param memo 记忆化数组（存储已计算的路径数，避免重复递归）
 * @return 当前位置到起点的有效路径数
 */
int dp(int x, int y, int blocked[21][21], int memo[21][21]) {
    // 1. 越界（x<0或y<0）或当前位置被阻塞，路径数为0
    if (x < 0 || y < 0 || blocked[x][y] == 1) {
        return 0;
    }
    // 2. 到达起点(0,0)，只有1条路径（自身）
    if (x == 0 && y == 0) {
        return 1;
    }
    // 3. 若已计算过当前位置的路径数，直接返回缓存结果（优化效率）
    if (memo[x][y] != -1) {
        return memo[x][y];
    }
    // 4. 路径数 = 上方位置(x-1,y)的路径数（向下走一步到当前） + 左方位置(x,y-1)的路径数（向右走一步到当前）
    int path_count = dp(x - 1, y, blocked, memo) + dp(x, y - 1, blocked, memo);
    // 5. 缓存当前位置的路径数，避免后续重复计算
    memo[x][y] = path_count;
    return path_count;
}

int main() {
    int aim_x, aim_y, horse_x, horse_y;
    // 输入：终点坐标(aim_x, aim_y) 、 马的初始位置(horse_x, horse_y)
    // 注意：坐标范围建议在0~20之间（数组维度为21x21）
    scanf("%d %d %d %d", &aim_x, &aim_y, &horse_x, &horse_y);
    
    // 初始化阻塞数组（21x21，足够覆盖常见坐标范围，0=可通行，1=阻塞）
    int blocked[21][21] = {0};
    // 马的8个攻击方向（阻塞位置的偏移量）
    int horse_attack_dirs[8][2] = {
        {2, 1}, {-2, 1}, {1, 2}, {-1, 2},  // 上4个方向
        {2, -1}, {-2, -1}, {1, -2}, {-1, -2} // 下4个方向
    };
    
    // 计算并标记马周围的阻塞位置（仅标记在棋盘范围内的位置）
    for (int i = 0; i < 8; i++) {
        // 阻塞位置 = 马的位置 + 攻击方向偏移量
        int block_x = horse_x + horse_attack_dirs[i][0];
        int block_y = horse_y + horse_attack_dirs[i][1];
        // 确保阻塞位置在【起点(0,0)到终点(aim_x,aim_y)】的范围内
        if (block_x >= 0 && block_x <= aim_x && block_y >= 0 && block_y <= aim_y) {
            blocked[block_x][block_y] = 1; // 标记为阻塞
        }
    }
    
    // 特殊情况：若起点(0,0)或终点(aim_x,aim_y)被阻塞，直接输出0（无有效路径）
    if (blocked[0][0] == 1 || blocked[aim_x][aim_y] == 1) {
        printf("0\n");
        return 0;
    }
    
    // 初始化记忆化数组（-1表示未计算，用memset快速赋值）
    int memo[21][21];
    memset(memo, -1, sizeof(memo));
    
    // 计算从(0,0)到(aim_x,aim_y)的有效路径数
    int total_paths = dp(aim_x, aim_y, blocked, memo);
    printf("有效路径数：%d\n", total_paths);
    
    return 0;
}
