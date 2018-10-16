/*hdu4408
*如何计算最小生成树个数呢？
*首先我们回顾一下kruskal算法。
*kruskal算法首先将边按照边权排序，假设边权先有一堆c1，然后c2，然后c3…(c1< c2< c3).
*我们首先会算c1的结果，而计算c2时，前面的结果实际和现在算c2是互不干扰的。
*也就是说，我们在计算最小生成树时，可以把它分成若干个阶段。
*在算c1阶段时，我们可以算它的生成树个数，然后再算c2时，再算它的生成树个数，然后相乘就是答案了。
*自己手动操作一下就能理解了。
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld eps = 1e-10;
const int maxn = 105;
const int maxm = 1005;
const int mod = 1e9;
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
}A, C;
struct Edge
{
    int u, v, dist;
    Edge(int _u, int _v, int _d) :u(_u), v(_v), dist(_d) {}
    Edge() {}
    bool operator<(const Edge &b)const
    {
        return dist < b.dist;
    }
}edges[maxm];
int n, m, p;
int find(int a, int *f) { return a == f[a] ? a : f[a] = find(f[a], f); }
int f[maxn], ka[maxn];
bool vis[maxn];
vector<int>V[maxn];
ll matrix_tree()
{
    for (int i = 1;i <= n;i++)if (vis[i])
        V[find(i, ka)].push_back(i);
    memset(vis, 0, sizeof(vis));
    ll ans = 1;
    for (int i = 1;i <= n;i++)if (V[i].size())
    {
        int Size = V[i].size();
        C.mem(Size);
        for (int j = 0;j<Size;j++)
            for (int k = j + 1;k < Size;k++)
            {
                int u = V[i][j], v = V[i][k];
                C.a[j + 1][k + 1] = 0 - A.a[u][v];
                C.a[k + 1][j + 1] = 0 - A.a[v][u];
                C.a[j + 1][j + 1] += A.a[u][v];
                C.a[k + 1][k + 1] += A.a[u][v];
            }
        C.n--, C.m--;
        ans = ans*C.det(p) % p;
        V[i].clear();
    }

    for (int i = 1;i <= n;i++)
        f[find(i, f)] = find(i, ka);
    return ans;
}
void solve()
{
    sort(edges + 1, edges + 1 + m);
    for (int i = 1;i <= n;i++)f[i] = ka[i] = i;
    int now = edges[1].dist;
    int u, v, fu, fv;
    ll ans = 1;
    for (int i = 1;i <= m;i++)
    {
        u = edges[i].u, v = edges[i].v;
        fu = find(u, f), fv = find(v, f);
        if (fu != fv)
        {
            ka[find(fu, ka)] = find(fv, ka);
            A.a[fu][fv]++;
            A.a[fv][fu]++;
            vis[fu] = 1, vis[fv] = 1;
        }
        if (i == m || now != edges[i + 1].dist)
        {
            ans = ans*matrix_tree() % p;
            now = edges[i + 1].dist;
        }
    }
    for (int i = 2;i <= n;i++)if (ka[i] != ka[i - 1])ans = 0;
    printf("%lld\n", ans%p);
}
int main()
{

    while (~scanf("%d %d %d", &n, &m, &p) && n)
    {
        A.mem(n);
        int u, v, dis;
        for (int i = 1;i <= m;i++)
        {
            scanf("%d %d %d", &u, &v, &dis);
            edges[i] = Edge(u, v, dis);
        }
        solve();
    }
}
