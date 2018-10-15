//点从1开始，坐标到nL,右边到nR
//时间复杂度O(sqrt(n)*E)
const int maxn=605;
const int maxm=1805;
const int inf=0x3f3f3f3f;
struct Edge
{
    int u,v,next;
    Edge(int _u,int _v,int _nxt):u(_u),v(_v),next(_nxt) {}
    Edge() {}
} edges[maxm];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
int nL,nR;
int cx[maxn],cy[maxn];
int dx[maxn],dy[maxn];
bool used[maxn];
int dis;
bool bfs()
{
    dis=inf;
    queue<int>Q;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=1; i<=nL; i++)if(cx[i]==-1)
            Q.push(i),dx[i]=0;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if(dx[u]>dis)break;
        for(int i=head[u]; ~i; i=edges[i].next)
        {
            int v=edges[i].v;
            if(dy[v]==-1)
            {
                dy[v]=dx[u]+1;
                if(cy[v]==-1)dis=dy[v];
                else
                {
                    dx[cy[v]]=dy[v]+1;
                    Q.push(cy[v]);
                }
            }
        }
    }
    return dis!=inf;
}
int find(int u)
{
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].v;
        if(!used[v]&&dy[v]==dx[u]+1)
        {
            used[v]=1;
            if(cy[v]!=-1&&dy[v]==dis)continue;
            else if(cy[v]==-1||find(cy[v]))
            {
                cx[u]=v;
                cy[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
int MaxMatch()
{
    int res=0;
    memset(cx,-1,sizeof(cx));
    memset(cy,-1,sizeof(cy));
    while(bfs())
    {
        memset(used,0,sizeof(used));
        for(int i=1;i<=nL;i++)
        {
            if(cx[i]==-1)
                res+=find(i);
        }
    }
    return res;
}
//
