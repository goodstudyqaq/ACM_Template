//给定一棵树，节点有黑白两种颜色，有正负边权。两种操作
//1,反转某个节点的颜色
//2,询问两个白点的最大距离
//spoj-QTREE4
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
const int maxm=2*maxn;
const int inf=0x3f3f3f3f;
typedef pair<int,int>pii;
vector<pii>V[maxn];

struct Edge
{
    int u,v,w,nxt;
    bool flag;
Edge(int u,int v,int w,int nxt,bool flag):
u(u),v(v),w(w),nxt(nxt),flag(flag) {}
    Edge() {}
} edges[maxm];
int head[maxn],tot;
void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
}
void addedge(int u,int v,int w)
{
    edges[tot]=Edge(u,v,w,head[u],0);
    head[u]=tot++;
}
void add_Edge(int u,int v,int w)
{
    addedge(u,v,w);
    addedge(v,u,w);
}
int node_num;
void dfs(int u,int pre)
{
    int fa=0;
    for(int i=0; i<V[u].size(); i++)
    {
        int v=V[u][i].first,w=V[u][i].second;
        if(v==pre)continue;
        if(fa==0)
        {
            add_Edge(u,v,w);
            fa=u;
        }
        else
        {
            int k=++node_num;
            add_Edge(fa,k,0);
            add_Edge(k,v,w);
        }
        dfs(v,u);
    }
}
int sz[maxn];
void dfs1(int u,int pre)
{
    sz[u]=1;
    for(int i=head[u]; ~i; i=edges[i].nxt)
    {
        int v=edges[i].v;
        if(v==pre||edges[i].flag)continue;
        dfs1(v,u);
        sz[u]+=sz[v];
    }
}

pii dfs2(int u,int pre,int tt)
{
    pii res(inf,-1);
    for(int i=head[u]; ~i; i=edges[i].nxt)
    {
        int v=edges[i].v;
        if(v==pre||edges[i].flag)continue;
        int tmp=max(sz[v],tt-sz[v]);
        if(res.first>tmp)
            res=pii(tmp,i);
        pii it=dfs2(v,u,tt);
        if(res.first>it.first)
            res=it;
    }
    return res;
}
struct node
{
    int t,f,d;
    node(int t,int f,int d):t(t),f(f),d(d) {}
    node() {}
};
vector<node>V2[maxn];
struct node2
{
    int u,w;
    node2(int u,int w):u(u),w(w) {}
    node2() {}
    bool operator<(const node2 &b)const
    {
        return w<b.w;
    }
};
priority_queue<node2>q[maxn][2];
int N;
void dfs3(int u,int pre,int t,int f,int d)
{
    if(u<=N)
    {
        V2[u].push_back(node(t,f,d));
        q[t][f].push(node2(u,d));
    }
    for(int i=head[u]; ~i; i=edges[i].nxt)
    {
        int v=edges[i].v;
        if(v==pre||edges[i].flag)continue;
        dfs3(v,u,t,f,d+edges[i].w);
    }
}
int Mx[maxn];
int cc[maxn];
bool black[maxn];
int bnum;
int LC[maxn],RC[maxn];
void update(int u)
{
    while(!q[u][0].empty())
    {
        if(black[q[u][0].top().u])
            q[u][0].pop();
        else break;
    }
    while(!q[u][1].empty())
    {
        if(black[q[u][1].top().u])
            q[u][1].pop();
        else break;
    }
    if(q[u][0].size()==0||q[u][1].size()==0)Mx[u]=0;
    else
    Mx[u]=max(0,q[u][0].top().w+q[u][1].top().w+cc[u]);
    if(LC[u])Mx[u]=max(Mx[u],Mx[LC[u]]);
    if(RC[u])Mx[u]=max(Mx[u],Mx[RC[u]]);
}

int cnt;
int cal(int u)
{
    //找出中心边
    dfs1(u,0);
    pii tmp=dfs2(u,0,sz[u]);
    if(tmp.second==-1)return 0;
    
    edges[tmp.second].flag=edges[tmp.second^1].flag=1;
    int t=++cnt;
    cc[t]=edges[tmp.second].w;
    dfs3(edges[tmp.second].u,0,t,0,0);
    dfs3(edges[tmp.second].v,0,t,1,0);
    LC[t]=cal(edges[tmp.second].u);
    RC[t]=cal(edges[tmp.second].v);
    update(t);
    return t;
}

int main()
{
    init();
    scanf("%d",&N);
    for(int i=1,u,v,w; i<N; i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        V[u].push_back(pii(v,w));
        V[v].push_back(pii(u,w));
    }
    //重构树
    node_num=N;
    dfs(1,0);
    cal(1);
    
    int Q;
    scanf("%d",&Q);
    char s[3];
    while(Q--)
    {
        scanf("%s",s);
        if(s[0]=='A')
        {
            if(bnum==N)puts("They have disappeared.");
            else printf("%d\n",Mx[1]);
        }
        else
        {
            int a;
            scanf("%d",&a);
            if(black[a])
            {
                black[a]=0;
                bnum--;
                for(int i=V2[a].size()-1; i>=0; i--)
                {
                    node tmp=V2[a][i];
                    q[tmp.t][tmp.f].push(node2(a,tmp.d));
                    update(tmp.t);
                }
            }
            else
            {
                black[a]=1;
                bnum++;
                for(int i=V2[a].size()-1; i>=0; i--)
                {
                    node tmp=V2[a][i];
                    update(tmp.t);
                }
            }
        }
    }
    return 0;
}
