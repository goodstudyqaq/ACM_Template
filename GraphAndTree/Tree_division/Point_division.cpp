//基于点的分治
//poj1741 求树上两点距离小于k的对数
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<stdio.h>
using namespace std;
const int maxn=1e4+5;
typedef pair<int,int>pii;
vector<pii>V[maxn];
//重心
int f[maxn];
int rt;
int vis[maxn];
int sz[maxn];
int cntnode;
int ans;
void dfs(int u,int pre)
{
    sz[u]=1;
    for(int i=0;i<V[u].size();i++)
    {
        int v=V[u][i].first;
        if(v==pre||vis[v])continue;
        dfs(v,u);
        sz[u]+=sz[v];
        f[u]=max(f[u],sz[v]);
    }
    f[u]=max(f[u],cntnode-sz[u]);
    if(f[u]<f[rt])rt=u;
}
//
int d[maxn];
int deep[maxn],dp;
int n,k;
void dfs2(int u,int pre,int w)
{
    d[u]=w;
    deep[++dp]=d[u];
    for(int i=0;i<V[u].size();i++)
    {
        int v=V[u][i].first,tw=V[u][i].second;
        if(v==pre||vis[v])continue;
        dfs2(v,u,w+tw);
    }
}

int cal(int u,int w)
{
    int res=0;
    dp=0;
    dfs2(u,0,w);
    sort(deep+1,deep+1+dp);
    for(int i=1,r=dp;i<r;i++)
    {
        while(r>=1&&deep[r]+deep[i]>k)r--;
        if(r<i)break;
        res+=r-i;
    }
    return res;
}

void solve(int u)
{
    ans+=cal(u,0);//先计算以该点为树的贡献
    vis[u]=1;
    for(int i=0;i<V[u].size();i++)
    {
        int v=V[u][i].first,w=V[u][i].second;
        if(vis[v])continue;
        ans-=cal(v,w);//减去在同一颗树下的贡献
        memset(f,0,sizeof(f));
        rt=0;
        f[rt]=maxn;
        cntnode=sz[v];
        dfs(v,u);
        solve(rt);
    }

}
//
int main()
{
    while(~scanf("%d %d",&n,&k))
    {
        ans=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)V[i].clear();
        if(n==0&&k==0)break;
        for(int i=1,u,v,w;i<n;i++)
        {
            scanf("%d %d %d",&u,&v,&w);
            V[u].push_back(pii(v,w));
            V[v].push_back(pii(u,w));
        }
        //cntnode 树下节点个数 先求出重心
        cntnode=n;
        memset(f,0,sizeof(f));
        f[0]=maxn;
        rt=0;
        dfs(1,0);
        //
        solve(rt);
        printf("%d\n",ans);
    }
    return 0;
}
