//三维前缀和
const int maxn=10;
int a[maxn][maxn][maxn];
int sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return a[x2][y2][z2] - a[x1 - 1][y2][z2] - a[x2][y1 - 1][z2] -
           a[x2][y2][z1 - 1] + a[x1 - 1][y1 - 1][z2] + a[x1 - 1][y2][z1 - 1] +
           a[x2][y1 - 1][z1 - 1] - a[x1 - 1][y1 - 1][z1 - 1];
}
void init(int n) {
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            for (int t = 1; t <= n; t++) a[i][k][t] += a[i - 1][k][t];
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            for (int t = 1; t <= n; t++) a[i][k][t] += a[i][k - 1][t];
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            for (int t = 1; t <= n; t++) a[i][k][t] += a[i][k][t - 1];
}
