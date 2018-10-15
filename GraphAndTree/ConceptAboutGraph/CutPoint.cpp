//边从0到tot-1，点从1到N
//如果有重边的话，在tarjan函数自己加上判断函数即可。
//不管是有向图还是无向图，LOW数组都不能代表点所在的连通分量。
const int maxn=105;
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
int DFN[maxn],LOW[maxn],id;
int N;
bool chose[maxn];
int fa[maxn];
void tarjan(int u,int pre)
{
    fa[u]=pre;
    DFN[u]=LOW[u]=++id;
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].v;
        if(!DFN[v])
        {
            tarjan(v,u);
            LOW[u]=min(LOW[u],LOW[v]);
        }
        else if(v!=pre)
            LOW[u]=min(LOW[u],DFN[v]);
    }
}
void init()
{
    id=0;
    tot=0;
    memset(head,-1,sizeof(head));
    memset(DFN,0,sizeof(DFN));
    memset(LOW,0,sizeof(LOW));
    memset(chose,0,sizeof(chose));
}
void solve()
{
    tarjan(1,0);
    int rootnum=0;
    for(int i=1;i<=N;i++)
    {
        if(fa[i]==1)rootnum++;
        else if(LOW[i]>=DFN[fa[i]])
            chose[fa[i]]=1;
    }
    int ans=0;
    for(int i=2;i<=N;i++)
        if(chose[i])
            ans++;
    if(rootnum>1)
        ans++;
    printf("%d\n",ans);
}
//
