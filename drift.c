#include <stdio.h>
#include <stdlib.h>

int typein(int x, int y, int n, int m) {
    if(x >= 0 && x <= n && y >= 0 && y <= m){
return 1;}
   else{
return 0;}
    
}

long long path(int n, int m, int control[21][21]) {
    long long out[21][21] = {0};
    
    if (control[0][0] || control[n][m]) {
        return 0;
    }
    
    out[0][0] = 1; 
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (control[i][j]) {
                out[i][j] = 0;
                continue;
            }
            if (i > 0) out[i][j] += out[i-1][j];
            if (j > 0) out[i][j] += out[i][j-1];
        }
    }
    return out[n][m];
}

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    
    int control[21][21] = {0};
    control[x][y] = 1;
    int horsec[8][2] = {{1,2}, {1,-2}, {-1,2}, {-1,-2},
                      {2,1}, {2,-1}, {-2,1}, {-2,-1}};
    
    for (int i = 0; i < 8; i++) {
        int nx = x + horsec[i][0];
        int ny = y + horsec[i][1];
        if (typein(nx, ny, n, m)) {
            control[nx][ny] = 1;
        }
    }
    
    long long result = path(n, m, control);
    printf("%lld\n", result);
    return 0;
}