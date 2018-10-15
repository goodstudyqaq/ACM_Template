#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const LL INF=1e18;
const int MAXN=1e5+5;
int head[MAXN],head1[MAXN];
LL dis[MAXN];
bool vis[MAXN];
int n,m,tot,st,en,k;

struct Edge
{
    int u,v,nxt,nxt1;
    LL c;
    Edge(){}
    Edge(int _u,int _v,LL _c):u(_u),v(_v),c(_c){}
}e[MAXN*2];

struct qnode
{
    int v;
    LL c;
    qnode(){}
    qnode(int _v,LL _c):v(_v),c(_c){}
    bool operator < (const qnode& rhs) const
    {
        return c+dis[v]>rhs.c+dis[rhs.v];
    }
};

void addedge(int u,int v,LL c)
{
    e[tot]=Edge(u,v,c);
    e[tot].nxt=head[u];head[u]=tot;
    e[tot].nxt1=head1[v];head1[v]=tot++;
}

void dij(int src)
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) dis[i]=INF;
    dis[src]=0;
    priority_queue<qnode> que;
    que.push(qnode(src,0));
    while(!que.empty())
    {
        qnode pre=que.top(); que.pop();
        if(vis[pre.v]) continue;
        vis[pre.v]=true;
        for(int i=head1[pre.v];i!=-1;i=e[i].nxt1)
        {
            if(dis[e[i].u]>dis[pre.v]+e[i].c)
            {
                dis[e[i].u]=dis[pre.v]+e[i].c;
                que.push(qnode(e[i].u,0));
            }
        }
    }
}

LL a_star(int src)
{
    priority_queue<qnode> que;
    que.push(qnode(src,0));
    k--;
    while(!que.empty())
    {
        qnode pre=que.top();que.pop();
        if(pre.v==en)
        {
            if(k) k--;
            else return pre.c;
        }
        for(int i=head[pre.v];i!=-1;i=e[i].nxt)
            que.push(qnode(e[i].v,pre.c+e[i].c));
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(head1,-1,sizeof(head1));
        tot=0;
        for(int i=0;i<m;i++)
        {
            int u,v;LL c;
            scanf("%d%d%lld",&u,&v,&c);
            addedge(u,v,c);
            addedge(v,u,c);
        }
        st=1,en=n;k=2;
        dij(en);
        if(st==en) k++;
        printf("%lld\n",a_star(st));
    }
    return 0;
}
