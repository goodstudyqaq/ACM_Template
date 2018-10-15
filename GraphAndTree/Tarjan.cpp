//点从1到n，边从0到tot-1
//时间复杂度O(n+m)
const int maxn=105;
const int maxm=maxn*maxn;
struct Edge
{
    int u,v,next;
    Edge(int _u,int _v,int _n):u(_u),v(_v),next(_n){}
    Edge(){}
}edges[maxm];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
int DFN[maxn],LOW[maxn],vis[maxn],id;//vis代表是否在堆栈中
int belong[maxn],cnt;//belong数组的值从1到cnt，cnt为强连通的个数
int stack[maxn],tot1;
void tarjan(int u)
{
    DFN[u]=LOW[u]=++id;
    stack[tot1++]=u;
    vis[u]=1;
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].v;
        if(!DFN[v])
        {
            tarjan(v);
            LOW[u]=min(LOW[u],LOW[v]);
        }
        else if(vis[v])//在堆栈中才能是连通的
            LOW[u]=min(LOW[u],DFN[v]);
    }
    if(LOW[u]==DFN[u])
    {
        cnt++;
        int v;
        do
        {
            v=stack[tot1-1];
            vis[v]=0;
            belong[v]=cnt;
            tot1--;
        }while(v!=u);
    }
}
void solve(int N)
{
    memset(DFN,0,sizeof(DFN));
    cnt=0;
    for(int i=1;i<=N;i++)if(!DFN[i])
    {
        id=0;
        tarjan(i);
    }
}
