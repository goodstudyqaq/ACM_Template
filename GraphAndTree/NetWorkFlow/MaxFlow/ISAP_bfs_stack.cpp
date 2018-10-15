//ISAP + bfs初始化 + 栈优化
const int maxn=100010;
const int maxm=400010;
const int inf=0x3f3f3f3f;
//
struct Edge
{
    int to,next,cap,flow;
    Edge(int _t,int _n,int _c,int _f):to(_t),next(_n),cap(_c),flow(_f){}
    Edge(){}
}edge[maxm];
int head[maxn],tot;
int gap[maxn],dep[maxn],cur[maxn];
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw=0)
{
    edge[tot]=Edge(v,head[u],w,0);
    head[u]=tot++;
    edge[tot]=Edge(u,head[v],rw,0);
    head[v]=tot++;
}
int Q[maxn];
void BFS(int start,int end)
{
    memset(dep,-1,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0]=1;
    int front=0,rear=0;
    dep[end]=0;
    Q[rear++]=end;
    while(front!=rear)
    {
        int u=Q[front++];
        for(int i=head[u];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dep[v]!=-1)continue;
            Q[rear++]=v;
            dep[v]=dep[u]+1;
            gap[dep[v]]++;
        }
    }
}
int S[maxn];
int sap(int start,int end,int N)//第三个参数为点的总数
{
    BFS(start,end);
    memcpy(cur,head,sizeof(head));
    int top=0;
    int u=start;
    int ans=0;
    while(dep[start]<N)
    {
        if(u==end)
        {
            int Min=inf;
            int inser;
            for(int i=0;i<top;i++)
                if(Min>edge[S[i]].cap-edge[S[i]].flow)
                {
                    Min=edge[S[i]].cap-edge[S[i]].flow;
                    inser=i;
                }
            for(int i=0;i<top;i++)
            {
                edge[S[i]].flow+=Min;
                edge[S[i]^1].flow-=Min;
            }
            ans+=Min;
            top=inser;
            u=edge[S[top]^1].to;
            continue;
        }
        bool flag=false;
        int v;
        for(int i=cur[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].to;
            if(edge[i].cap-edge[i].flow&&dep[v]+1==dep[u])
            {
                flag=true;
                cur[u]=i;
                break;
            }
        }
        if(flag)
        {
            S[top++]=cur[u];
            u=v;
            continue;
        }
        int Min=N;
        for(int i=head[u];~i;i=edge[i].next)
            if(edge[i].cap-edge[i].flow&&dep[edge[i].to]<Min)
            {
                Min=dep[edge[i].to];
                cur[u]=i;
            }
        gap[dep[u]]--;
        if(!gap[dep[u]])return ans;
        dep[u]=Min+1;
        gap[dep[u]]++;
        if(u!=start)u=edge[S[--top]^1].to;
    }
    return ans;
}
//
