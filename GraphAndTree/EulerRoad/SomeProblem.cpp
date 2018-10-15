//Poj 2337
//给出n个小写字母组成的单词，要求将n个单词连接起来
//使得前一个单词的最后一个字母和后一个单词的第一个字母相同。输出字典序最小的解。
//代码好丑。。
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<stdio.h>
using namespace std;
struct Edge
{
    int to,next;
    int index;
    bool flag;
    Edge(int _t,int _n,int _i,bool _f=false):to(_t),next(_n),index(_i),flag(_f) {}
    Edge() {}
} edges[2010];
int head[30],tot;
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int index)
{
    edges[tot]=Edge(v,head[u],index);
    head[u]=tot++;
}
string str[1010];
int in[30],out[30];
int cnt;
int ans[1010];
void dfs(int u)
{
    for(int i=head[u]; ~i; i=edges[i].next)
        if(!edges[i].flag)
        {
            edges[i].flag=true;//防止环
            dfs(edges[i].to);
            ans[cnt++]=edges[i].index;
        }
}
int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0; i<n; i++)
            cin>>str[i];
        sort(str,str+n);
        init();
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        int start=100;
        for(int i=n-1; i>=0; i--)
        {
            int u=str[i][0]-'a';
            int v=str[i][str[i].length()-1]-'a';
            addedge(u,v,i);
            out[u]++;
            in[v]++;
            if(u<start)start=u;
            if(v<start)start=v;
        }
        int cc1=0,cc2=0;
        for(int i=0; i<26; i++)
        {
            //cout<<out[i]<<' '<<in[i]<<endl;
            if(out[i]-in[i]==1)
            {
                cc1++;
                start=i;
            }
            else if(out[i]-in[i]==-1)
                cc2++;
            else if(out[i]-in[i]!=0)
                cc1=3;
        }
        //cout<<cc1<<' '<<cc2<<endl;
        if(!((cc1==0&&cc2==0)||(cc1==1&&cc2==1)))
        {
            printf("***\n");
            continue;
        }
        cnt=0;
        dfs(start);
        if(cnt!=n)
        {
            puts("***");
            continue;
        }
        for(int i=cnt-1; i>=0; i--)
        {
            cout<<str[ans[i]];
            if(i>0)printf(".");
            else puts("");
        }
    }
    return 0;
}
/*************************************************/
//SGU 101
//N个多米诺骨牌，每个骨牌左右两侧分别有一个0~6的整数（骨牌可以旋转以调换其左右两数），
//求一种把这些骨牌从左到右排列的方案，使得所有相邻的两数字相等（即左边骨牌右侧的数字等于右边骨牌左侧的数字）。
//输入 第一行是一个整数N(1 ≤ N ≤ 100)，表示骨牌的数量。接下来的N行描述每块骨牌，每块左右两边有不同的点数。
//输出 如果无法安排，输出“No solution”。如果可能，输出任何一种，每行有一个数字，和“+”或“-”，前者代表不旋转，后者代表旋转。
#include<bits/stdc++.h>
using namespace std;
struct Edge
{
    int to,next;
    int index;
    int dir;
    bool flag;
    Edge(int _t,int _n,int _idx,int _dir,bool _f)
    :to(_t),next(_n),index(_idx),dir(_dir),flag(_f){}
    Edge(){}
}edges[220];
int head[10],tot;
void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
}
void addedge(int u,int v,int index)
{
    edges[tot]=Edge(v,head[u],index,0,0);
    head[u]=tot++;
    edges[tot]=Edge(u,head[v],index,1,0);
    head[v]=tot++;
}
int du[10];
vector<int>ans;
void dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].next)
        if(!edges[i].flag)
        {
            edges[i].flag=true;
            edges[i^1].flag=true;
            dfs(edges[i].to);
            ans.push_back(i);
        }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        init();
        int u,v;
        memset(du,0,sizeof(du));
        for(int i=1;i<=n;i++)
        {
            scanf("%d %d",&u,&v);
            addedge(u,v,i);
            du[u]++;
            du[v]++;
        }
        int s=-1;
        int cnt=0;
        for(int i=0;i<=6;i++)
        {
            if(du[i]&1){cnt++;s=i;}
            if(du[i]>0&&s==-1)
                s=i;
        }
        bool ff=true;
        if(cnt!=0&cnt!=2)
        {
            puts("No solution");
            continue;
        }
        ans.clear();
        //cout<<s<<endl;
        dfs(s);
        if(ans.size()!=n)
        {
            puts("No solution");
            continue;
        }
        for(int i=0;i<ans.size();i++)
        {
            printf("%d ",edges[ans[i]].index);
            if(edges[ans[i]].dir==0)printf("-\n");
            else printf("+\n");
        }
    }
    return 0;
}
/*************************************************/
//混合图判欧拉回路
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 210;
//最大流ISAP部分
const int MAXM = 20100;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow;
}edge[MAXM];
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],pre[MAXN],cur[MAXN];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0)
{
    edge[tol].to = v;
    edge[tol].cap = w;
    edge[tol].next = head[u];
    edge[tol].flow = 0;
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = rw;
    edge[tol].next = head[v];
    edge[tol].flow = 0;
    head[v] = tol++;
}
int sap(int start,int end,int N)
{
    memset(gap,0,sizeof(gap));
    memset(dep,0,sizeof(dep));
    memcpy(cur,head,sizeof(head));
    int u = start;
    pre[u] = -1;
    gap[0] = N;
    int ans = 0;
    while(dep[start] < N)
    {
        if(u == end)
        {
            int Min = INF;
            for(int i = pre[u]; i != -1;i = pre[edge[i^1].to])
                if(Min > edge[i].cap - edge[i].flow)
                    Min = edge[i].cap - edge[i].flow;
            for(int i = pre[u];i != -1;i = pre[edge[i^1].to])
            {
                edge[i].flow += Min;
                edge[i^1].flow -= Min;
            }
            u = start;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u];i != -1;i = edge[i].next)
        {
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u])
            {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if(flag)
        {
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u];i != -1;i = edge[i].next)
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
            {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if(!gap[dep[u]])return ans;
        dep[u] = Min+1;
        gap[dep[u]]++;
        if(u != start)u = edge[pre[u]^1].to;
    }
    return ans;
}
//the end of 最大流部分

int in[MAXN],out[MAXN];//每个点的出度和入度

int main()
{
    int T;
    int n,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        init();
        int u,v,w;
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            out[u]++; in[v]++;
            if(w == 0)//双向
                addedge(u,v,1);
        }
        bool flag = true;
        for(int i = 1;i <= n;i++)
        {
            if(out[i] - in[i] > 0)
                addedge(0,i,(out[i] - in[i])/2);
            else if(in[i] - out[i] > 0)
                addedge(i,n+1,(in[i] - out[i])/2);
            if((out[i] - in[i]) & 1)
                flag = false;
        }
        if(!flag)
        {
            printf("impossible\n");
            continue;
        }
        sap(0,n+1,n+2);
        for(int i = head[0]; i != -1;i = edge[i].next)
            if(edge[i].cap > 0 && edge[i].cap > edge[i].flow)
            {
                flag = false;
                break;
            }
        if(flag)printf("possible\n");
        else printf("impossible\n");
    }
    return 0;
}
/****************************************************/
//混合图(判断欧拉路径)
//hdu3472
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30;
//最大流部分
const int MAXM = 10000;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow;
}edge[MAXM];
int tol;
int head[MAXN];
int gap[MAXN], dep[MAXN], pre[MAXN], cur[MAXN];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0)
{
    edge[tol].to = v;
    edge[tol].cap = w;
    edge[tol].next = head[u];
    edge[tol].flow = 0;
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = rw;
    edge[tol].next = head[v];
    edge[tol].flow = 0;
    head[v] = tol++;
}
int sap(int start,int end,int N)
{
    memset(gap,0,sizeof(gap));
    memset(dep,0,sizeof(dep));
    memcpy(cur,head,sizeof(head));
    int u = start;
    pre[u] = -1;
    gap[0] = N;
    int ans = 0;
    while(dep[start] < N)
    {
        if(u == end)
        {
            int Min = INF;
            for(int i = pre[u];i != -1;i = pre[edge[i^1].to])
                if(Min > edge[i].cap - edge[i].flow)
                    Min = edge[i].cap - edge[i].flow;
            for(int i = pre[u]; i != -1;i = pre[edge[i^1].to])
            {
                edge[i].flow += Min;
                edge[i^1].flow -= Min;
            }
            u = start;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u]; i != -1;i = edge[i].next)
        {
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u])
            {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if(flag)
        {
            u = v;
            continue;
        }

        int Min = N;
        for(int i = head[u];  i != -1;i = edge[i].next)
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
            {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]] --;
        if(!gap[dep[u]])return ans;
        dep[u] = Min+1;
        gap[dep[u]]++;
        if(u != start) u = edge[pre[u]^1].to;
    }
    return ans;
}

int in[30],out[30];
int F[30];
int find(int x)
{
    if(F[x] == -1)return x;
    else return F[x] = find(F[x]);
}
void bing(int u,int v)
{
    int t1 = find(u), t2 = find(v);
    if(t1 != t2)F[t1] = t2;
}
char str[100];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,n;
    scanf("%d",&T);
    int iCase = 0;
    while(T--)
    {
        iCase++;
        scanf("%d",&n);
        memset(F,-1,sizeof(F));
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        init();
        int k;
        int s = -1;
        while(n--)
        {
            scanf("%s%d",str,&k);
            int len = strlen(str);
            int u = str[0] - 'a';
            int v = str[len-1] - 'a';
            out[u]++;
            in[v]++;
            s = u;
            if(k == 1)
                addedge(u,v,1);
            bing(u,v);
        }
        bool flag = true;
        int cnt = 0;
        int s1 = -1, s2 = -1;
        for(int i = 0;i < 26;i++)
            if(in[i] || out[i])
            {
                if(find(i) != find(s))
                {
                    flag = false;
                    break;
                }
                if((in[i] + out[i])&1)
                {
                    cnt++;
                    if(s1 == -1)s1 = i;
                    else s2 = i;
                }
            }
        if(cnt != 0 && cnt != 2)flag = false;
        if(!flag)
        {
            printf("Case %d: Poor boy!\n",iCase);
            continue;
        }
        if(cnt == 2)
        {
            out[s1]++;
            in[s2]++;
            addedge(s1,s2,1);
        }
        for(int i = 0;i < 26;i++)
        {
            if(out[i] - in[i] > 0)
                addedge(26,i,(out[i] - in[i])/2);
            else if(in[i] - out[i] > 0)
                addedge(i,27,(in[i] - out[i])/2);
        }
        sap(26,27,28);
        for(int i = head[26];i != -1;i = edge[i].next)
            if(edge[i].cap > 0 && edge[i].cap > edge[i].flow)
            {
                flag = false;
                break;
            }
        if(flag)printf("Case %d: Well done!\n",iCase);
        else printf("Case %d: Poor boy!\n",iCase);
    }
    return 0;
}

