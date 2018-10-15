//点从1到n
const int maxn=10010;
struct Edge
{
    int u,v,next;
    Edge(int _u,int _v,int _nxt):u(_u),v(_v),next(_nxt){}
    Edge(){}
}edges[maxn*maxn];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
int dp[maxn][30];
int dep[maxn];
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
    memset(dep,0,sizeof(dep));
}
void dfs(int u,int pre,int d)
{
    dep[u]=d;
    dp[u][0]=pre;
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].v;
        if(v==pre)continue;
        dfs(v,u,d+1);
    }
}
void rmq(int n)//参数为点的个数
{
    for(int i=1;i<20;i++)
        for(int j=1;j<=n;j++)
    {
        if((1<<i)>dep[j])continue;
        int k=dp[j][i-1];dp[j][i]=dp[k][i-1];
    }
}
int query(int x,int y)
{
    if(dep[x]>dep[y])swap(x,y);
    for(int j=19;j>=0&&dep[x]!=dep[y];j--)
    {
        if(dep[y]-(1<<j)<dep[x])continue;
        y=dp[y][j];
    }
    if(x==y)return x;
    for(int j=19;j>=0;j--)
    {
        if(dep[x]-(1<<j)<0||dp[x][j]==dp[y][j])continue;
        x=dp[x][j],y=dp[y][j];
    }
    return dp[x][0];
}
