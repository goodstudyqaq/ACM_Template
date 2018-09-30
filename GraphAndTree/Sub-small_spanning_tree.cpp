//Prim版本(无重边的时候才能用)
//点下标从1到n
//Max[i][j]来表示MST中i到j最大边权
//求完后，直接枚举所有不在MST中的边，替换最大边权的边，更新答案
const int maxn=105;
const int inf=0x3f3f3f3f;
int map[maxn][maxn];
int lowcost[maxn];
int closest[maxn];
bool used[maxn][maxn];
bool vis[maxn];
int Max[maxn][maxn];
int prim(int n)
{
    memset(lowcost,inf,sizeof(lowcost));
    memset(closest,0,sizeof(closest));
    memset(used,0,sizeof(used));
    memset(vis,0,sizeof(vis));
    memset(Max,0,sizeof(Max));
    lowcost[1]=0;
    vis[1]=1;
    closest[1]=1;
    int num=0,ans=0;
    int nownode=1;
    while(num<n-1)
    {
        int Mincost=inf,theidx;
        for(int i=1;i<=n;i++)
        {
            if(vis[i])
            {
                if(i==nownode)continue;
                Max[i][nownode]=Max[nownode][i]=max(Max[i][closest[nownode]],lowcost[nownode]);
            }
            else
            {
                if(lowcost[i]>map[i][nownode])
                {
                    lowcost[i]=map[i][nownode];
                    closest[i]=nownode;
                }
                if(Mincost>lowcost[i])
                {
                    Mincost=lowcost[i];
                    theidx=i;
                }
            }
        }
        ans+=Mincost;
        num++;
        nownode=theidx;
        vis[nownode]=1;
        used[theidx][closest[theidx]]=used[closest[theidx]][theidx]=1;
    }
    for(int i=1;i<=n;i++)if(i!=nownode)
        Max[i][nownode]=Max[nownode][i]=max(Max[i][closest[nownode]],lowcost[nownode]);
    return ans;
}
void solve(int n,int num)//num为最小生成树的权值
{
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)if(!used[i][j])
    {
        int ans=num-Max[i][j]+map[i][j];
        if(ans==num)
        {
            puts("Not Unique!");
            return ;
        }
    }
    printf("%d\n",num);
}
//
//Kruskal版
//边从0到tot-1
//点从1到n
const int maxn = 105;
const int maxm = 205;
const int inf = 0x3f3f3f3f;
struct Edge
{
    int u, v, dis;
    bool vis;

    Edge(int _u, int _v, int _d) :u(_u), v(_v), dis(_d) { vis = 0; }
    Edge(){}
    bool operator<(const Edge &b)const
    {
        return dis < b.dis;
    }
}edges[maxm];
int tot;
int n, m;
vector<int>node[maxn];
void addedge(int u, int v, int dis)
{
    edges[tot++] = Edge(u, v, dis);
}
int f[maxn];
int find(int a)
{
    return a == f[a] ? a : f[a] = find(f[a]);
}
int Max[maxn][maxn];
int Kruskal()
{
    sort(edges, edges + tot);
    for (int i = 1;i <= n;i++)
        f[i] = i, node[i].clear(), node[i].push_back(i);
    memset(Max, 0, sizeof(Max));
    int ans = 0, tot1 = 0;
    for (int i = 0;i < tot;i++)
    {
        if (tot1 == n - 1)break;
        int u = edges[i].u, v = edges[i].v, dis = edges[i].dis;
        int fu = find(u), fv = find(v);
        if (fu != fv)
        {
            edges[i].vis = 1;
            tot1++;
            ans += dis;
            f[fv] = fu;
            //cout << find(fu) << endl;
            int Sizefu = node[fu].size();
            int Sizefv = node[fv].size();
            for (int j = 0;j < Sizefu;j++)
                for (int k = 0;k < Sizefv;k++)
                    Max[node[fu][j]][node[fv][k]] = Max[node[fv][k]][node[fu][j]] = dis;
            //int tmp[105];
            //for (int j = 0;j < Sizefu;j++)
                //tmp[j] = node[fu][j];
            for (int j = 0;j < Sizefv;j++)
                node[fu].push_back(node[fv][j]);
            //for (int j = 0;j < Sizefu;j++)
                //node[fv].push_back(tmp[j]);
        }
    }
    if (tot1 != n - 1)return -1;
    return ans;
}
int solve(int num)
{
    int ans = inf;
    for (int i = 0;i <tot;i++)
        if (!edges[i].vis)
            ans = min(ans, num - Max[edges[i].u][edges[i].v] + edges[i].dis);
    if (ans == inf)
        return -1;
    return ans;
}
//
