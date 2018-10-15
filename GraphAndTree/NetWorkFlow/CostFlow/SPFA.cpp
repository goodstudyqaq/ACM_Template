//SPFA版费用流
//下标从0到N-1
//最小费用最大流，求最大费用只需取相反数，结果取相反数即可。
const int maxn=10000;
const int maxm=100000;
const int inf=0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow,cost;
    Edge(int _t,int _n,int _c,int _f,int _cost):to(_t),next(_n),cap(_c),flow(_f),cost(_cost){}
    Edge(){}
}edges[maxm];
int head[maxn],tot;
int pre[maxn],dis[maxn];
bool vis[maxn];
int N;
void init(int n)
{
    N=n;
    tot=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost)
{
    edges[tot]=Edge(v,head[u],cap,0,cost);
    head[u]=tot++;
    edges[tot]=Edge(u,head[v],0,0,-cost);
    head[v]=tot++;
}
bool spfa(int s,int t)
{
    queue<int>q;
    for(int i=0;i<N;i++)
    {
        dis[i]=inf;
        vis[i]=false;
        pre[i]=-1;
    }
    dis[s]=0;
    vis[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].next)
        {
            int v=edges[i].to;
            if(edges[i].cap>edges[i].flow&&dis[v]>dis[u]+edges[i].cost)
            {
                dis[v]=dis[u]+edges[i].cost;
                pre[v]=i;
                if(!vis[v])
                {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t]==-1)return 0;
    return 1;
}
int minCostMaxflow(int s,int t,int &cost)
{
    int flow=0;
    cost=0;
    while(spfa(s,t))
    {
        int Min=inf;
        for(int i=pre[t];~i;i=pre[edges[i^1].to])
        {
            if(Min>edges[i].cap-edges[i].flow)
                Min=edges[i].cap-edges[i].flow;
        }
        for(int i=pre[t];~i;i=pre[edges[i^1].to])
        {
            edges[i].flow+=Min;
            edges[i^1].flow-=Min;
            cost+=edges[i].cost*Min;
        }
        flow+=Min;
    }
    return flow;
}
