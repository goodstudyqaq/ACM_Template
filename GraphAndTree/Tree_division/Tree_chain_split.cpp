//树链剖分
//给你一颗树，现在有两个操作，一种是改变某条边的权值，一种是查询点u到//v之间的路径的最大边权。
//spoj-QTREE
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+5;
const int inf=0x3f3f3f3f;
struct edge{int u,v,w;}edges[maxn];
typedef pair<int,int>pii;
vector<pii>V[maxn];

//
int dep[maxn];
int fa[maxn];
int sz[maxn];
int son[maxn];
int val[maxn];
void dfs(int u,int f,int d,int va)
{
    val[u]=va;
    fa[u]=f;
    dep[u]=d;
    sz[u]=1;
    son[u]=0;
    int ma=-inf;
    for(int i=0,v,w;i<V[u].size();i++)
    {
        v=V[u][i].first;
        w=V[u][i].second;
        if(v==f)continue;
        dfs(v,u,d+1,w);
        sz[u]+=sz[v];
        if(ma<sz[v])
            son[u]=v,ma=sz[v];
    }
}
int id[maxn];
int top[maxn];
int _id;
void dfs2(int u,int pre,int t)
{
    top[u]=t;
    id[u]=++_id;
    if(son[u])dfs2(son[u],u,t);
    for(int i=0,v;i<V[u].size();i++)
    {
        v=V[u][i].first;
        if(v==pre||v==son[u])continue;
        dfs2(v,u,v);
    }
}

//
#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
int ma[maxn<<2];
void update(int L,int C,int l,int r,int rt)
{
    if(l==r)
    {
        ma[rt]=C;
        return;
    }
    int m=l+r>>1;
    if(L<=m)update(L,C,ls);
    else update(L,C,rs);
    ma[rt]=max(ma[rt<<1],ma[rt<<1|1]);
}

int query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
        return ma[rt];
    int m=l+r>>1;
    int res=-inf;
    if(L<=m)res=max(res,query(L,R,ls));
    if(R>m)res=max(res,query(L,R,rs));
    return res;
}
int n;
void solve(int x,int y)
{
    int ans=-inf;
    int kx=top[x],ky=top[y];
    while(kx!=ky)
    {
        if(dep[kx]<dep[ky])
        {
            swap(x,y);
            swap(kx,ky);
        }
        int l=id[top[x]],r=id[x];
        ans=max(ans,query(l,r,1,n,1));
        x=fa[kx];
        kx=top[x];
    }
    if(x==y)
    {
        printf("%d\n",ans);
        return;
    }
    if(dep[x]>dep[y])
        swap(x,y);
    int l=id[son[x]],r=id[y];
    ans=max(ans,query(l,r,1,n,1));
    printf("%d\n",ans);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)V[i].clear();
        _id=0;
        for(int i=1,u,v,w;i<n;i++)
        {
            scanf("%d %d %d",&u,&v,&w);
            edges[i].u=u;edges[i].v=v;edges[i].w=w;
            V[u].push_back(pii(v,w));
            V[v].push_back(pii(u,w));
        }
        dfs(1,-1,1,-inf);
        dfs2(1,0,1);
        for(int i=1;i<=n;i++)
        {
            int L=id[i],_val=val[i];
            update(L,_val,1,n,1);
        }
        char s[10];
        int x,y;
        while(~scanf("%s",s))
        {
            if(s[0]=='D')break;
            scanf("%d %d",&x,&y);
            if(s[0]=='Q')
                solve(x,y);
            else
            {
                int u=edges[x].u,v=edges[x].v;
                if(fa[u]==v)update(id[u],y,1,n,1);
                else update(id[v],y,1,n,1);
            }
        }
        if(T)puts("");
    }
    return 0;
}
