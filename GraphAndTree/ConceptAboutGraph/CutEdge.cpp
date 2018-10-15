//边从0到tot-1，点从0到n-1
//有重边仅需要在tarjan函数加个判断
const int maxn=505;
struct Edge
{
    int u,v,next;
    Edge(int _u,int _v,int _n):u(_u),v(_v),next(_n){}
    Edge(){}
}edges[maxn*maxn];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
int DFN[maxn],LOW[maxn],id;
int n;
pair<int,int>pii[maxn*maxn];
int pcnt;
int fa[maxn];
void init()
{
    tot=0;
    id=0;
    memset(head,-1,sizeof(head));
    memset(DFN,0,sizeof(DFN));
    pcnt=0;
}
void tarjan(int u,int pre)
{
    DFN[u]=LOW[u]=++id;
    fa[u]=pre;
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
void solve()
{
    for(int i=0;i<n;i++)if(!DFN[i])
    {
        id=0;
        tarjan(i,-1);
    }
    int ans=0;
    for(int i=0;i<n;i++)
    {
        if(fa[i]==-1)continue;
        if(DFN[fa[i]]<LOW[i])
        {
            ans++;
            int themin=min(fa[i],i);
            int themax=max(fa[i],i);
            pii[pcnt++]=make_pair(themin,themax);
        }
    }
    sort(pii,pii+pcnt);
    printf("%d critical links\n",ans);
    for(int i=0;i<pcnt;i++)
        printf("%d - %d\n",pii[i].first,pii[i].second);
    puts("");
}

