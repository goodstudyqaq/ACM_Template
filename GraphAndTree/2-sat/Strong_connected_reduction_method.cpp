//强连通缩点法(拓扑排序只能得到任意解)
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<queue>
#include<vector>

using namespace std;
const int maxn=1010;
const int maxm=100010;
struct Edge
{
    int to,nxt;
}edges[maxm];
int head[maxn],tot;
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    edges[tot].to=v;edges[tot].nxt=head[u];head[u]=tot++;
}
int LOW[maxn],DFN[maxn],Stack[maxn],Belong[maxn];//Belong数组的值 1~scc
int Index,top;
int scc;
bool Instack[maxn];
int num[maxn];
void Tarjan(int u)
{
    int v;
    LOW[u]=DFN[u]=++Index;
    Stack[top++]=u;
    Instack[u]=true;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        v=edges[i].to;
        if(!DFN[v])
        {
            Tarjan(v);
            if(LOW[u]>LOW[v])LOW[u]=LOW[v];
        }
        else if(Instack[v]&&LOW[u]>DFN[v])
            LOW[u]=DFN[v];
    }
    if(LOW[u]==DFN[u])
    {
        scc++;
        do
        {
            v=Stack[--top];
            Instack[v]=false;
            Belong[v]=scc;
            num[scc]++;
        }
        while(v!=u);
    }
}

bool solvable(int n)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,0,sizeof(Instack));
    memset(num,0,sizeof(num));
    Index=scc=top=0;
    for(int i=0;i<n;i++)
        if(!DFN[i])Tarjan(i);
    for(int i=0;i<n;i+=2)
    {
        if(Belong[i]==Belong[i^1])return 0;
    }
    return 1;
}
//****************************************
//拓扑排序求任意一组解部分
queue<int>q1,q2;
vector<vector<int> >dag;//缩点后的逆向DAG图
char color[maxn];//染色，为'R'是选择的
int indeg[maxn];//入度
int cf[maxn];
void solve(int n)
{
    dag.assign(scc+1,vector<int>()); //assign(n,m)将n个m放入vector里面
    memset(indeg,0,sizeof(indeg));
    memset(color,0,sizeof(color));
    for(int u=0;u<n;u++)
        for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(Belong[u]!=Belong[v])
        {
            dag[Belong[v]].push_back(Belong[u]);
            indeg[Belong[u]]++;
        }
    }
    for(int i=0;i<n;i+=2)
        cf[Belong[i]]=Belong[i^1],cf[Belong[i^1]]=Belong[i];
    while(!q1.empty())q1.pop();
    while(!q2.empty())q2.pop();
    for(int i=1;i<=scc;i++)
        if(indeg[i]==0)
        q1.push(i);
    while(!q1.empty())
    {
        int u=q1.front();
        q1.pop();
        if(color[u]==0)
        {
            color[u]='R';
            color[cf[u]]='B';
        }
        int sz=dag[u].size();
        for(int i=0;i<sz;i++)
        {
            indeg[dag[u][i]]--;
            if(indeg[dag[u][i]]==0)
                q1.push(dag[u][i]);
        }
    }
}

int change(char s[])
{
    int ret=0;
    int i=0;
    while(s[i]>='0'&&s[i]<='9')
    {
        ret*=10;
        ret+=s[i]-'0';
        i++;
    }
    if(s[i]=='w')return 2*ret;
    else return 2*ret+1;
}

int main()
{
    int n,m;
    char s1[10],s2[10];
    while(~scanf("%d %d",&n,&m))
    {
        if(n==0&&m==0)break;
        init();
        while(m--)
        {
            scanf("%s %s",s1,s2);
            int u=change(s1);
            int v=change(s2);
            addedge(u,v^1);
            addedge(v,u^1);
        }
        addedge(0,1);
        if(solvable(2*n))
        {
            solve(2*n);
            for(int i=1;i<n;i++)
            {
                if(color[Belong[2*i]]==color[Belong[0]])printf("%dw",i);
                else printf("%dh",i);
                if(i<n-1)printf(" ");
                else puts("");
            }
        }
        else puts("bad luck");
    }
    return 0;
}
