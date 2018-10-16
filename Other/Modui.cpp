//莫队模板
//len取sqrt(n)
int len;
struct Query
{
    int L,R,block;
    int idx;
    Query(int l,int r,int i):L(l),R(r),idx(i)
    {
        block=L/len;
    }
    Query(){}
    bool operator<(const Query &b)const
    {
        if(block!=b.block)return block<b.block;
        return R<b.R;
    }
};
Query q[maxm];
/*****************************************************/
//树上莫队
//找路径中不同数的个数
#include<bits/stdc++.h>
using namespace std;
#define stack stk
const int maxn=4e4+5;
struct Edge
{
    int u,v,nxt;
    Edge(int u,int v,int nxt):u(u),v(v),nxt(nxt){}
    Edge(){}
}edges[maxn*2];
int head[maxn],tot;
void addedge(int u,int v)
{
    edges[tot]=Edge(u,v,head[u]);
    head[u]=tot++;
}
//
int K;
int belong[maxn],cnt;
int dfn[maxn],dfs_cnt;
struct Query
{
    int u,v,id;
    bool operator<(const Query &b)const
    {
        if(belong[u]==belong[b.u])return dfn[v]<dfn[b.v];
        return belong[u]<belong[b.u];
    }
}querys[100005];
//
int dp[maxn][20];
int stack[maxn],top;
int dep[maxn];
int dfs(int u,int pre)//分块函数
{
    dfn[u]=++dfs_cnt;
    int size=0;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].v;
        if(v==pre)continue;
        dp[v][0]=u;
        dep[v]=dep[u]+1;
        size+=dfs(v,u);
        if(size>=K)
        {
            cnt++;
            for(int j=1;j<=size;j++)
                belong[stack[top--]]=cnt;
            size=0;
        }
    }
    stack[++top]=u;
    return size+1;
}
void RMQ(int n)
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
int ans;
int used[maxn];
int p[maxn];
int c[maxn];
int cc[maxn];
void work(int u,int v,int lca)
{
    while(u!=lca)
    {
        if(!used[u]){p[c[u]]++,used[u]=1;if(p[c[u]]==1)ans++;}
        else {p[c[u]]--,used[u]=0;if(p[c[u]]==0)ans--;}
        u=dp[u][0];
    }
    while(v!=lca)
    {
        if(!used[v]){p[c[v]]++,used[v]=1;if(p[c[v]]==1)ans++;}
        else {p[c[v]]--,used[v]=0;if(p[c[v]]==0)ans--;}
        v=dp[v][0];
    }
}
int Ans[100005];
int main()
{
    memset(head,-1,sizeof(head));
    int n,m;
    scanf("%d %d",&n,&m);
    K=sqrt(1.0*n);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]),cc[i]=c[i];
    sort(cc+1,cc+1+n);
    int cnum=unique(cc+1,cc+1+n)-cc-1;
    for(int i=1;i<=n;i++)c[i]=lower_bound(cc+1,cc+1+cnum,c[i])-cc;
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    int tmp=dfs(1,0);
    if(tmp)
    {
        for(int i=1;i<=tmp;i++)
            belong[stack[top--]]=tot;
    }
    RMQ(n);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d %d",&u,&v);
        querys[i].u=u,querys[i].v=v;
        querys[i].id=i;
    }
    sort(querys+1,querys+1+m);
    int lca=query(querys[1].u,querys[1].v);
    work(querys[1].u,querys[1].v,lca);
    if(!used[lca]){p[c[lca]]++,used[lca]=1;if(p[c[lca]]==1)ans++;}
    else {p[c[lca]]--,used[lca]=0;if(p[c[lca]]==0)ans--;}
    Ans[querys[1].id]=ans;
    if(!used[lca]){p[c[lca]]++,used[lca]=1;if(p[c[lca]]==1)ans++;}
    else {p[c[lca]]--,used[lca]=0;if(p[c[lca]]==0)ans--;}
    for(int i=2;i<=m;i++)
    {
        work(querys[i-1].u,querys[i].u,query(querys[i-1].u,querys[i].u));
        work(querys[i-1].v,querys[i].v,query(querys[i-1].v,querys[i].v));
        lca=query(querys[i].u,querys[i].v);
        if(!used[lca]){p[c[lca]]++,used[lca]=1;if(p[c[lca]]==1)ans++;}
        else{p[c[lca]]--,used[lca]=0;if(p[c[lca]]==0)ans--;}
        Ans[querys[i].id]=ans;
        if(!used[lca]){p[c[lca]]++,used[lca]=1;if(p[c[lca]]==1)ans++;}
        else{p[c[lca]]--,used[lca]=0;if(p[c[lca]]==0)ans--;}
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",Ans[i]);
    return 0;
}
/****************************************************************/
//可修改莫队(O(n^{3/4}t^{1/3}))
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
int a[maxn],col_cnt[1000005];
struct node
{
    int p,pre,w;
}cg[maxn];
struct Query
{
    int l,r,t,idx;
}Q[maxn];
int block;
bool cmp(const Query &a,const Query &b)
{
    if(a.l/block!=b.l/block)return a.l/block<b.l/block;
    if(a.r/block!=b.r/block)return a.r/block<b.r/block;
    return a.t<b.t;
}
int Ans[maxn];
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    int cnum=0,qnum=0;
    char s[3];
    int l,r;
    for(int i=1;i<=m;i++)
    {
        scanf("%s",s);
        if(s[0]=='R')
        {
            ++cnum;
            scanf("%d %d",&cg[cnum].p,&cg[cnum].w);
            cg[cnum].pre=a[cg[cnum].p];
            a[cg[cnum].p]=cg[cnum].w;
        }
        else
        {
            scanf("%d %d",&l,&r);
            Q[++qnum].l=l,Q[qnum].r=r,Q[qnum].t=cnum,Q[qnum].idx=qnum;
        }
    }
    block=ceil(exp((log(n)+log(qnum))/3));
    for(int i=cnum;i>=1;i--)a[cg[i].p]=cg[i].pre;
    sort(Q+1,Q+1+qnum,cmp);
    int ans=0;
    l=0,r=0;
    int t=0;
    for(int i=1;i<=m;i++)
    {
        while(Q[i].l<l){col_cnt[a[--l]]++;if(col_cnt[a[l]]==1)ans++;}
        while(Q[i].l>l){col_cnt[a[l]]--;if(col_cnt[a[l]]==0)ans--;l++;}
        while(Q[i].r>r){col_cnt[a[++r]]++;if(col_cnt[a[r]]==1)ans++;}
        while(Q[i].r<r){col_cnt[a[r]]--;if(col_cnt[a[r]]==0)ans--;r--;}
        while(Q[i].t<t)
        {
            int pla=cg[t].p;
            if(l<=pla&&pla<=r){col_cnt[a[pla]]--;if(col_cnt[a[pla]]==0)ans--;}
            a[pla]=cg[t--].pre;
            if(l<=pla&&pla<=r){col_cnt[a[pla]]++;if(col_cnt[a[pla]]==1)ans++;}
        }
        while(Q[i].t>t)
        {
            int pla=cg[++t].p;
            if(l<=pla&&pla<=r){col_cnt[a[pla]]--;if(col_cnt[a[pla]]==0)ans--;}
            a[pla]=cg[t].w;
            if(l<=pla&&pla<=r){col_cnt[a[pla]]++;if(col_cnt[a[pla]]==1)ans++;}
        }
        Ans[Q[i].idx]=ans;
    }
    for(int i=1;i<=qnum;i++)printf("%d\n",Ans[i]);
}
