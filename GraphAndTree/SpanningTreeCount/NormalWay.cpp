/*无向图时D为度数矩阵，A为邻接矩阵，C=D-A，再将c的行和列都减1，
*求行列式即为生成树个数。
*有向图时，求树形图个数，对于D(度数矩阵)来说，当有边(u,v)D[v][v]++,
*对于A(邻接矩阵)来说，当有边(u,v)A[u][v]++。而C=D-A，后面操作一样。
*对于有重边的图同样的处理方式，但现在A[i][j]代表边的个数。
*/
#include<bits/stdc++.h>
using namespace std;
#define map Map
typedef long long ll;
typedef long double ld;
const ld eps = 1e-10;
const int maxn = 305;
const int mod = 10007;
int sgn(ld x)
{
    if (fabs(x) < eps)return 0;
    else if (x > 0)return 1;
    return -1;
}
struct M
{
    int n, m;
    ll a[maxn][maxn];
    M(int _n = 0) { n = m = _n;memset(a, 0, sizeof(a)); }
    M(int _n, int _m) { n = _n, m = _m;memset(a, 0, sizeof(a)); }
    void mem(int _n = 0) { n = m = _n, memset(a, 0, sizeof(a)); }
    void mem(int _n, int _m) { n = _n, m = _m;memset(a, 0, sizeof(a)); }
    void pri()
    {
        for (int i = 1;i <= n;i++)
        {
            for (int j = 1;j <= m;j++)cout << a[i][j] << ' ';
            cout << endl;
        }
    }
    friend M operator*(M a, M b)
    {
        M c;
        for (int k = 1;k <= a.m;k++)
            for (int i = 1;i <= a.n;i++)
                for (int j = 1;j <= b.m;j++)
                    c.a[i][j] += a.a[i][k] * b.a[k][j];
        return c;
    }
    friend M operator-(M a, M b)
    {
        for (int i = 1;i <= a.n;i++)
            for (int j = 1;j <= a.m;j++)
                a.a[i][j] -= b.a[i][j];
        return a;
    }
    void make_I(int _n)
    {
        n = m = _n;
        memset(a, 0, sizeof(a));
        for (int i = 1;i <= n;i++)a[i][i] = 1;
    }
    //行列式高精度
    long double mat[maxn][maxn], tmp[maxn];
    long double det()
    {
        long double ans = 1;
        for (int i = 1;i <= n;i++) for (int j = 1;j <= m;j++) mat[i][j] = a[i][j];
        for (int i = 1;i <= n;i++)
        {
            int pos = i;
            while (fabs(mat[pos][i])<eps&&pos<n) ++pos;
            if (fabs(mat[pos][i])<eps) return 0;
            if (pos^i)
            {
                copy(mat[pos] + 1, mat[pos] + 1 + m + 1, tmp + 1);
                copy(mat[i] + 1, mat[i] + 1 + m + 1, mat[pos] + 1);
                copy(tmp + 1, tmp + 1 + m + 1, mat[i] + 1);
            }
            ans *= mat[i][i];
            for (int j = i + 1;j <= n;j++)
            {
                long double p = mat[j][i] / mat[i][i];
                for (int k = i;k <= m;k++) mat[j][k] -= mat[i][k] * p;
            }
        }
        return ans;
    }
    //行列式辗转相除法
    ll det(ll mod)
    {
        ll ret = 1;
        for (int i = 1;i <= n;i++)
        {
            if (a[i][i] < 0)
            {
                ret = -ret;
                for (int k = i;k <= n;k++)a[i][k] = -a[i][k];
            }
            for (int j = i + 1;j <= n;j++)
            {
                for (int k = i;k <= n;k++)a[i][k] %= mod, a[j][k] %= mod;
                while (a[j][i])
                {
                    if (a[j][i] < 0)
                    {
                        ret = -ret;
                        for (int k = i;k <= n;k++)a[j][k] = -a[j][k];
                    }
                    ll t = a[i][i] / a[j][i];
                    for (int k = i;k <= n;k++)a[i][k] = (a[i][k] - t*a[j][k]) % mod;
                    for (int k = i;k <= n;k++)swap(a[i][k], a[j][k]);
                    ret = -ret;
                }
            }
            if (a[i][i] == 0)return 0;
            ret = ret*a[i][i] % mod;
        }
        return (ret + mod) % mod;
    }
}A, C, D;
struct node
{
    int x, y;
    node(int _x,int _y):x(_x),y(_y){}
    node(){}
}nodes[maxn];
double map[maxn][maxn];
int N, R;
double dist(int a, int b)
{
    double x = nodes[a].x - nodes[b].x;
    double y = nodes[a].y - nodes[b].y;
    return sqrt(x*x + y*y);
}
vector<int>V[maxn];
bool check(int a, int b)
{
    for(auto it:V[a])if(it!=b)
        if (!sgn(map[a][it] + map[it][b] - map[a][b]))
            return 0;
    return 1;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {

        scanf("%d %d", &N, &R);
        for (int i = 1;i <= N;i++)V[i].clear();
        A.mem(N);
        C.mem(N);
        D.mem(N);
        int x, y;
        for (int i = 1;i <= N;i++)
        {
            scanf("%d %d", &x, &y);
            nodes[i] = node(x, y);
        }
        for(int i=1;i<=N;i++)
            for (int j = i+1;j <= N;j++)if (i != j)
            {
                double tmp = dist(i, j);
                map[i][j] = map[j][i] = tmp;
                if (tmp <= R)
                    V[i].push_back(j), V[j].push_back(i);
            }

        for(int i=1;i<=N;i++)
            for (int j = i + 1;j <= N;j++)if (map[i][j] <= R)
            {
                if (check(i, j))
                {
                    A.a[i][j] = A.a[j][i] = 1;
                    D.a[i][i]++;
                    D.a[j][j]++;
                }
            }

        for (int i = 1;i <= N;i++)
            for (int j = 1;j <= N;j++)
                C.a[i][j] = D.a[i][j] - A.a[i][j];
        //C.pri();
        C.n--;C.m--;
        int ans = C.det(mod);
        printf("%d\n", ans == 0 ? -1 : ans);
    }
}
