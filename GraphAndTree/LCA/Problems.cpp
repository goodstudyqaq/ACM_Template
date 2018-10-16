//lca+动态询问树上两个点的距离
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
#define time te
//
int f[maxn];
int find(int a)
{
    return a==f[a]?a:f[a]=find(f[a]);
}
typedef pair<int,int>pii;
vector<pii>V[maxn];
void add_Edge(int u,int v,int w)
{
    V[u].push_back(pii(v,w));
    V[v].push_back(pii(u,w));
}
int su,sv,sw;
//
long long d[maxn];
int dp[maxn][20];
int dep[maxn];
int l[maxn],r[maxn];
int time;
void dfs(int u,int pre,long long dis)
{
    d[u]=dis;
    dp[u][0]=pre;
    ++time;
    l[u]=time;
    for(int i=0;i<V[u].size();i++)
    {
        pii x=V[u][i];
        int v=x.first,w=x.second;
        if(v==pre)continue;
        dep[v]=dep[u]+1;
        dfs(v,u,dis+w);
    }
    r[u]=time;
}

void rmq(int n)
{
    for(int i=1;i<20;i++)
        for(int j=1;j<=n;j++)
        {
            if((1<<i)>dep[j])continue;
            int k=dp[j][i-1];dp[j][i]=dp[k][i-1];
        }
}

int query(int x,int y)
{
    if(dep[x]>dep[y])swap(x,y);
    for(int j=19;j>=0&&dep[x]!=dep[y];j--)
    {
        if(dep[y]-(1<<j)<dep[x])continue;
        y=dp[y][j];
    }

    if(x==y)return x;
    for(int j=19;j>=0;j--)
    {
        if(dep[x]-(1<<j)<0||dp[x][j]==dp[y][j])continue;
        x=dp[x][j],y=dp[y][j];
    }
    return dp[x][0];
}
//
#define lowbit(x) x&-x
long long sum[maxn];
void add(int x,int val)
{
    while(x<maxn)
    {
        sum[x]+=val;
        x+=lowbit(x);
    }
}
long long query(int x)
{
    long long res=0;
    while(x)
    {
        res+=sum[x];
        x-=lowbit(x);
    }
    return res;
}
vector<pair<pii,int> >V2;

void update(int l,int r,int v)
{
    add(l,v);
    add(r+1,-v);
}

long long getdis(int u,int v)
{
    long long res=0;
    int lca=query(u,v);
    res+=d[u]+query(l[u]);
    res+=d[v]+query(l[v]);
    res-=2LL*(d[lca]+query(l[lca]));
    return res;
}

void outdis(int u,int v)
{
    long long res=getdis(u,v);
    res=min(res,getdis(u,su)+getdis(v,sv)+sw);
    res=min(res,getdis(u,sv)+getdis(v,su)+sw);
    printf("%lld\n",res);
}

int main()
{
    //cout<<(1<<20);
    //freopen("input.txt","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int N,Q;
        scanf("%d %d",&N,&Q);
        time=0;
        V2.clear();
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=N;i++)f[i]=i,V[i].clear();
        int u,v,w;
        for(int i=1;i<=N;i++)
        {
            scanf("%d %d %d",&u,&v,&w);
            int fu=find(u),fv=find(v);
            if(fu!=fv)
                add_Edge(u,v,w),f[fu]=fv;
            else
                su=u,sv=v,sw=w;
            V2.push_back(make_pair(pii(u,v),w));
        }
        if(su>sv)swap(su,sv);
        dfs(1,0,0);
        rmq(N);
        int opt,X,Y;
        while(Q--)
        {
            scanf("%d %d %d",&opt,&X,&Y);
            if(opt==0)
            {
                X--;
                pair<pii,int> tmp=V2[X];
                //tuple<int,int,int> tmp=V2[X];
                u=tmp.first.first,v=tmp.first.second,w=tmp.second;
                if(u>v)swap(u,v);
                if(u==su&&v==sv)
                    sw=Y;
                else
                {
                    if(dp[u][0]==v)
                    {
                        update(l[u],r[u],Y-w);
                        V2[X].second=Y;
                    }
                    else
                    {
                        update(l[v],r[v],Y-w);
                        V2[X].second=Y;
                    }
                }
            }
            else
                outdis(X,Y);
        }
    }
    return 0;
}
