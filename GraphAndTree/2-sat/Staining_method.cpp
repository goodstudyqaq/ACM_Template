//染色法(可以得到字典序最小的解)
#include<bits/stdc++.h>
using namespace std;
const int MAXN=20020;
const int MAXM=100010;
struct Edge
{
    int to,nxt;
}edges[MAXM];
int head[MAXN],tot;
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    edges[tot].to=v;edges[tot].nxt=head[u];head[u]=tot++;
}
bool vis[MAXN];//染色标记,为true表示选择
int S[MAXN],top;//栈
bool dfs(int u)
{
    if(vis[u^1])return false;
    if(vis[u])return true;
    vis[u]=1;
    S[top++]=u;
    for(int i=head[u];~i;i=edges[i].nxt)
        if(!dfs(edges[i].to))
            return false;
    return true;
}
bool Twosat(int n)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i+=2)
    {
        if(vis[i]||vis[i^1])continue;
        top=0;
        if(!dfs(i))
        {
            while(top)vis[S[--top]]=false;
            if(!dfs(i^1))return false;
        }
    }
    return true;
}
int main()
{
    int n,m;
    int u,v;
    while(~scanf("%d %d",&n,&m))
    {
        init();
        while(m--)
        {
            scanf("%d %d",&u,&v);
            u--;v--;
            addedge(u,v^1);
            addedge(v,u^1);
        }
        if(Twosat(2*n))
        {
            for(int i=0;i<2*n;i++)
                if(vis[i])printf("%d\n",i+1);
        }
        else printf("NIE\n");
    }
    return 0;
}

