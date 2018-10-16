//去掉桥，其余的连通分支就是边双连通分支。一个有桥的连通图要变成边双连通图的话，把双连通子图收缩为一个点，形成一棵树。需要加的边为(leaf+1)/2(leaf为叶子结点个数)
//POJ3177
//点下标从1到n
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
const int maxn=5005;
const int maxm=5005;
struct Edge
{
    int u,v,next;
    Edge(int _u,int _v,int _nxt):u(_u),v(_v),next(_nxt){}
    Edge(){}
}edges[maxm*2];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
int DFN[maxn],LOW[maxn],fa[maxn],id;
void tarjan(int u,int pre)
{
    DFN[u]=LOW[u]=++id;
    fa[u]=pre;
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].v;
        if(v==pre)continue;
        if(!DFN[v])
        {
            tarjan(v,u);
            LOW[u]=min(LOW[u],LOW[v]);
        }
        else
        {
            LOW[u]=min(LOW[u],DFN[v]);
        }
    }
}
int deg[maxn];
int n,m;
int f[maxn];
int find(int a){return a==f[a]?a:f[a]=find(f[a]);}
void solve()
{
    int ans=0;
    tarjan(1,0);
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=2;i<=n;i++)
    {
        int u=fa[i],v=i;
        if(DFN[u]<LOW[v])continue;
        int fu=find(u),fv=find(v);
        f[fv]=fu;
    }
    for(int i=2;i<=n;i++)
    {
        int u=fa[i],v=i;
        int fu=find(u),fv=find(v);
        if(fu!=fv)
            deg[fu]++,deg[fv]++;
    }
    for(int i=1;i<=n;i++)
        if(deg[i]==1)
            ans++;
    printf("%d\n",(ans+1)/2);
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    solve();
}
