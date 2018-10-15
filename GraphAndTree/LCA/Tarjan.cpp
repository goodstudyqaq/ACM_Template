//Tarjan离线求LCA
//poj 1470
//时间复杂度 O(n+Q)
//下标从1到n
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>

using namespace std;
const int maxn=1010;
const int maxq=500010;

//并查集部分
int F[maxn];
int find(int x)
{
    if(F[x]==x)return x;
    return F[x]=find(F[x]);
}
void bing(int u,int v)
{
    int t1=find(u);
    int t2=find(v);
    if(t1!=t2)
        F[t2]=t1;
}
//***********************
bool vis[maxn];//访问标记
struct Edge
{
    int to,next;
    Edge(int _t,int _nxt):to(_t),next(_nxt){}
    Edge(){}
}edges[maxn*2];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(v,head[u]);
    head[u]=tot++;
}
struct Query
{
    int q,next;
    int index;//查询编号
    Query(int _q,int _nxt,int _idx):q(_q),next(_nxt),index(_idx){}
    Query(){}
}query[maxq*2];
int answer[maxq];//存储最后的查询结果，下标从0到Q-1
int h[maxq],tt;
int Q;

void add_query(int u,int v,int index)
{
    query[tt]=Query(v,h[u],index);
    h[u]=tt++;
    query[tt]=Query(u,h[v],index);
    h[v]=tt++;
}
void init(int n)
{
    tot=0;
    memset(head,-1,sizeof(head));
    tt=0;
    memset(h,-1,sizeof(h));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)F[i]=i;
}
void LCA(int u)
{
    vis[u]=1;
    for(int i=head[u];~i;i=edges[i].next)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        LCA(v);
        bing(u,v);//这里一定不能写反
    }
    for(int i=h[u];~i;i=query[i].next)
    {
        int v=query[i].q;
        if(vis[v])
            answer[query[i].index]=find(v);
    }
}
bool flag[maxn];
int Count_num[maxn];
int main()
{
    int n;
    int u,v,k;
    while(~scanf("%d",&n))
    {
        init(n);
        memset(flag,0,sizeof(flag));
        for(int i=1;i<=n;i++)
        {
            scanf("%d:(%d)",&u,&k);
            while(k--)
            {
                scanf("%d",&v);
                flag[v]=true;
                addedge(u,v);
                addedge(v,u);
            }
        }
        scanf("%d",&Q);
        for(int i=0;i<Q;i++)
        {
            char ch;
            cin>>ch;
            scanf("%d %d)",&u,&v);
            add_query(u,v,i);
        }
        int root;
        for(int i=1;i<=n;i++)
            if(!flag[i])
            {
                root=i;
                break;
            }
        LCA(root);
        memset(Count_num,0,sizeof(Count_num));
        for(int i=0;i<Q;i++)Count_num[answer[i]]++;
        for(int i=1;i<=n;i++)
            if(Count_num[i]>0)
                printf("%d:%d\n",i,Count_num[i]);
    }
    return 0;
}
