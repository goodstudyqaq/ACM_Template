//zkw费用流
//对于二分图类型的比较高效
const int maxn=1010;
const int maxm=50050;
const int inf=0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow,cost;
    Edge(int _t,int _next,int _cap,int _flow,int _cost):
        to(_t),next(_next),cap(_cap),flow(_flow),cost(_cost){}
    Edge(){}
}edges[maxm];
struct ZKW_MinCostMaxFlow
{
    int head[maxn],tot;
    int cur[maxn];
    int dis[maxn];
    bool vis[maxn];
    int ss,tt,N;//源点,汇点,和点的总个数(编号是0到N-1),不需要额外赋值,调用会直接赋值。
    int min_cost,max_flow;
    void init()
    {
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
    int aug(int u,int flow)
    {
        if(u==tt)return flow;
        vis[u]=1;
        for(int i=cur[u];~i;i=edges[i].next)
        {
            int v=edges[i].to;
            if(edges[i].cap>edges[i].flow&&!vis[v]&&dis[u]==dis[v]+edges[i].cost)
            {
                int tmp=aug(v,min(flow,edges[i].cap-edges[i].flow));
                edges[i].flow+=tmp;
                edges[i^1].flow-=tmp;
                cur[u]=i;
                if(tmp)return tmp;
            }
        }
        return 0;
    }
    bool modify_label()
    {
        int d=inf;
        for(int u=0;u<N;u++)
            if(vis[u])
                for(int i=head[u];~i;i=edges[i].next)
                {
                    int v=edges[i].to;
                    if(edges[i].cap>edges[i].flow&&!vis[v])
                        d=min(d,dis[v]+edges[i].cost-dis[u]);
                }
        if(d==inf)return false;
        for(int i=0;i<N;i++)
            if(vis[i])
        {
            vis[i]=false;
            dis[i]+=d;
        }
        return true;
    }
    pair<int,int>mincostmaxflow(int start,int end,int n)
    {
        ss=start,tt=end,N=n;
        min_cost=max_flow=0;
        for(int i=0;i<n;i++)dis[i]=0;
        while(1)
        {
            for(int i=0;i<n;i++)cur[i]=head[i];
            while(1)
            {
                for(int i=0;i<n;i++)vis[i]=false;
                int tmp=aug(ss,inf);
                if(tmp==0)break;
                max_flow+=tmp;
                min_cost+=tmp*dis[ss];
            }
            if(!modify_label())break;
        }
        return make_pair(min_cost,max_flow);
    }
}solve;
