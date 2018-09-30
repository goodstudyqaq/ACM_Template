//一般形式的dijkstra(复杂度O(n^2))
//下标从1到n
int Map[1005][1005];
bool vis[1005];
int d[1005];
const int inf = 0x3f3f3f3f;
void dijkstra(int s,int n)
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)d[i]=(i==s?0:inf);
    for(int i=0;i<n;i++)
    {
        int x,m=inf;
        for(int y=1;y<=n;y++)if(!vis[y]&&d[y]<=m)m=d[x=y];
        vis[x]=1;
        for(int y=1;y<=n;y++)d[y]=min(d[y],d[x]+Map[x][y]);
    }
}
//

//一般形式的bellman-ford(复杂度为O(VE))
//顶点下标从1到n，边大小为m，下标从0到m-1
//存在负环时返回false
const int maxn=55;
const int maxm=maxn*maxn;
const int inf=0x3f3f3f3f;
struct Edge
{
    int u,v,dist;
    Edge(int _u,int _v,int _d):u(_u),v(_v),dist(_d) {}
    Edge() {}
} edges[maxm];
int d[maxn];
bool bellman_ford(int s,int n,int m)
{
    for(int i=1; i<=n; i++)d[i]=(i==s?0:inf);
    for(int k=0; k<n-1; k++)
    {
        bool flag=false;
        for(int i=0; i<m; i++)
        {
            int u=edges[i].u,v=edges[i].v;
            if(d[v]>d[u]+edges[i].dist)
            {
                d[v]=d[u]+edges[i].dist;
                flag=true;
            }
        }
        if(!flag)return true;
    }
    for(int j=0;j<m;j++)
        if(d[edges[j].v]>d[edges[j].u]+edges[j].dist)
            return 0;
    return 1;
}
//
