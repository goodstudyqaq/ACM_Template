//点从0开始
//时间复杂度O(VE)
//邻接矩阵形式
const int maxn=510;
int uN,vN;//u,v的数目，使用前必须赋值
int g[maxn][maxn];
int cx[maxn],cy[maxn];
bool used[maxn];
bool dfs(int u)
{
    for(int v=0;v<vN;v++)if(g[u][v]&&!used[v])
    {
        used[v]=true;
        if(cy[v]==-1||dfs(cy[v]))
        {
            cy[v]=u;
            cx[u]=v;
            return 1;
        }
    }
    return 0;
}
int hungary()
{
    int res=0;
    memset(cy,-1,sizeof(cy));
    memset(cx,-1,sizeof(cx));
    for(int u=0;u<uN;u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}
/*******************************************/
//邻接表形式
//点从0到uN-1
const int maxn=5010
const int maxm=50010;
struct Edge
{
    int u,v,next;
    Edge(int _u,int _v,int _nxt):u(_u),v(_v),next(_nxt){}
    Edge(){}
}edges[maxm];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
int cx[maxn],cy[maxn];
int used[maxn];
int uN;
bool dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].v;
        if(!used[v])
        {
            used[v]=1;
            if(cy[v]==-1||dfs(cy[v]))
            {
                cy[v]=u;
                cx[u]=v;
                return 1;
            }
        }
    }
    return 0;
}
int hungary()
{
    int res=0;
    memset(cx,-1,sizeof(cx));
    memset(cy,-1,sizeof(cy));
    for(int u=0;u<uN;u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}

