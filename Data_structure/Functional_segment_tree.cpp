//静态区间第k大
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn],x[maxn],xnum;
int rt[maxn];
int c[maxn*30],lson[maxn*30],rson[maxn*30],tot;

int build(int l,int r)
{
    int root=tot++;
    c[root]=0;
    if(l!=r)
    {
        int m=l+r>>1;
        lson[root]=build(l,m);
        rson[root]=build(m+1,r);
    }
    return root;
}
//递归版
int update(int pre,int L,int C,int l,int r)
{
    int root=tot++;
    lson[root]=lson[pre];
    rson[root]=rson[pre];
    c[root]=c[pre]+C;
    if(l!=r)
    {
        int mid=l+r>>1;
        if(L<=mid)
            lson[root]=update(lson[pre],L,C,l,mid);
        else rson[root]=update(rson[pre],L,C,mid+1,r);
    }
    return root;
}
int query(int u,int v,int l,int r,int k)
{
    if(l==r)return l;
    int mid=l+r>>1;
    int x=c[lson[v]]-c[lson[u]];
    if(x>=k)return query(lson[u],lson[v],l,mid,k);
    k-=x;
    return query(rson[u],rson[v],mid+1,r,k);

}
//非递归版
int update(int pre,int L,int C)
{
    int root=tot++,tmp=root;
    c[root]=c[pre]+C;
    int l=1,r=xnum;
    while(l<r)
    {
        int mid=l+r>>1;
        if(L<=mid)
        {
            lson[root]=tot++;rson[root]=rson[pre];
            root=lson[root];pre=lson[pre];
            r=mid;
        }
        else
        {
            rson[root]=tot++;lson[root]=lson[pre];
            root=rson[root];pre=rson[pre];
            l=mid+1;
        }
        c[root]=c[pre]+C;
    }
    return tmp;
}
int query(int u,int v,int k)
{
    int l=1,r=xnum;
    while(l<r)
    {
        int mid=l+r>>1;
        if(c[lson[v]]-c[lson[u]]>=k)
        {
            r=mid;
            v=lson[v];
            u=lson[u];
        }
        else
        {
            l=mid+1;
            k-=c[lson[v]]-c[lson[u]];
            v=rson[v];
            u=rson[u];
        }
    }
    return l;
}
int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        tot=0;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),x[i]=a[i];
        sort(x+1,x+1+n);
        xnum=unique(x+1,x+1+n)-x-1;
        rt[0]=build(1,xnum);
        for(int i=1;i<=n;i++)
        {
            int idx=lower_bound(x+1,x+1+xnum,a[i])-x;
            rt[i]=update(rt[i-1],idx,1);
        }
        while(m--)
        {
            int l,r,k;
            scanf("%d %d %d",&l,&r,&k);
            printf("%d\n",x[query(rt[l-1],rt[r],k)]);
        }
    }
    return 0;
}
/*******************************************************/
//动态区间第k大
#include<bits/stdc++.h>
using namespace std;
const int maxn=60005;
const int N=2500010;
int a[maxn],x[maxn],xnum;
int lson[N],rson[N],c[N];
int T[maxn],tot,S[maxn];
int build(int l,int r)
{
    int root=tot++;
    c[root]=0;
    if(l<r)
    {
        int m=l+r>>1;
        lson[root]=build(l,m);
        rson[root]=build(m+1,r);
    }
    return root;
}

int update(int pre,int L,int C)
{
    int newroot=tot++,tmp=newroot;
    int l=1,r=xnum;
    c[newroot]=c[pre]+C;
    while(l<r)
    {
        int m=l+r>>1;
        if(L<=m)
        {
            lson[newroot]=tot++;rson[newroot]=rson[pre];
            newroot=lson[newroot];pre=lson[pre];
            r=m;
        }
        else
        {
            rson[newroot]=tot++;lson[newroot]=lson[pre];
            newroot=rson[newroot];pre=rson[pre];
            l=m+1;
        }
        c[newroot]=c[pre]+C;
    }
    return tmp;
}

//

struct Query
{
    int kind;
    int l,r,k;
}qs[10005];
int n;
#define lowbit(x) x&-x
void add(int i,int x,int val)
{
    while(i<=n)
    {
        S[i]=update(S[i],x,val);
        i+=lowbit(i);
    }
}
int used[maxn];
int query(int x)
{
    int res=0;
    while(x)
    {
        res+=c[lson[used[x]]];
        x-=lowbit(x);
    }
    return res;
}
int query(int u,int v,int k)
{
    int left_root=T[u];
    int right_root=T[v];
    for(int i=u;i;i-=lowbit(i))
        used[i]=S[i];
    for(int i=v;i;i-=lowbit(i))
        used[i]=S[i];
    int l=1,r=xnum;
    while(l<r)
    {
        int m=l+r>>1;
        int tmp=c[lson[right_root]]-c[lson[left_root]]+query(v)-query(u);
        if(tmp>=k)
        {
            for(int i=u;i;i-=lowbit(i))used[i]=lson[used[i]];
            for(int i=v;i;i-=lowbit(i))used[i]=lson[used[i]];
            left_root=lson[left_root];right_root=lson[right_root];
            r=m;
        }
        else
        {
            k-=tmp;
            for(int i=u;i;i-=lowbit(i))used[i]=rson[used[i]];
            for(int i=v;i;i-=lowbit(i))used[i]=rson[used[i]];
            left_root=rson[left_root];right_root=rson[right_root];
            l=m+1;
        }
    }
    return l;
}

int main()
{
    int Tcas;
    scanf("%d",&Tcas);
    while(Tcas--)
    {
        tot=0;
        int m;
        scanf("%d %d",&n,&m);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),x[i]=a[i];
        xnum=n;
        /*sort(x+1,x+1+n);
        xnum=unique(x+1,x+1+n)-x-1;
        T[0]=build(1,xnum);
        for(int i=1;i<=n;i++)
        {
            int idx=lower_bound(x+1,x+1+n,a[i])-x;
            T[i]=update(T[i-1],idx,1);
        }*/
        char s[3];
        int l,r,k;
        for(int i=1;i<=m;i++)
        {
            scanf("%s",s);
            if(s[0]=='Q')
            {
                qs[i].kind=0;
                scanf("%d %d %d",&l,&r,&k);
                qs[i].l=l,qs[i].r=r,qs[i].k=k;
            }
            else
            {
                qs[i].kind=1;
                scanf("%d %d",&l,&r);
                qs[i].l=l,qs[i].r=r;
                x[++xnum]=r;
            }
        }
        sort(x+1,x+1+xnum);
        xnum=unique(x+1,x+1+xnum)-x-1;
        T[0]=build(1,xnum);
        for(int i=1;i<=n;i++)
        {
            int idx=lower_bound(x+1,x+1+xnum,a[i])-x;
            T[i]=update(T[i-1],idx,1);
            S[i]=T[0];
        }
        for(int i=1;i<=m;i++)
        {
            if(qs[i].kind==0)
            {
                printf("%d\n",x[query(qs[i].l-1,qs[i].r,qs[i].k)]);
            }
            else
            {
                int idx=lower_bound(x+1,x+1+xnum,a[qs[i].l])-x;
                add(qs[i].l,idx,-1);
                idx=lower_bound(x+1,x+1+xnum,qs[i].r)-x;
                add(qs[i].l,idx,1);
                a[qs[i].l]=qs[i].r;
            }
        }
    }
    return 0;
}
/*******************************************************/
//一般写法
//hdu4348
//一个长度为n的数组，4种操作 C l r d区间[l,r]都加1，当前时间戳加1 Q l r 查询当前时间戳[l,r]的所有数的和 H l r t 查询时间戳t区间[l,r]的和 B t将当前时间戳置为t.
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
long long a[maxn];
int lson[maxn*20],rson[maxn*20];
long long sum[maxn*20];
long long add[maxn*20];
int T[maxn],tot;

int build(int l,int r)
{
    int root=tot++;
    add[root]=0;
    if(l==r)
    {
        sum[root]=a[l];
        return root;
    }
    int m=l+r>>1;
    lson[root]=build(l,m);
    rson[root]=build(m+1,r);
    sum[root]=sum[lson[root]]+sum[rson[root]];
    return root;
}

void pushup(int rt,int l,int r)
{
    int ls=lson[rt],rs=rson[rt];
    int len=r-l+1;
    sum[rt]=sum[ls]+sum[rs]+add[ls]*(len-len/2)+add[rs]*(len/2);
}

int update(int root,int L,int R,int C,int l,int r)
{
    int newroot=tot++;
    add[newroot]=add[root];
    if(L<=l&&r<=R)
    {
        lson[newroot]=lson[root];
        rson[newroot]=rson[root];
        add[newroot]=add[root]+C;
        sum[newroot]=sum[root];
        return newroot;
    }
    int m=l+r>>1;
    if(L<=m)
        lson[newroot]=update(lson[root],L,R,C,l,m);
    else lson[newroot]=lson[root];
    if(R>m)
        rson[newroot]=update(rson[root],L,R,C,m+1,r);
    else rson[newroot]=rson[root];
    pushup(newroot,l,r);
    return newroot;
}

long long query(int root,int L,int R,int l,int r,long long a)
{

    if(L<=l&&r<=R)
    {
        return sum[root]+(add[root]+a)*(r-l+1);
    }
    int m=l+r>>1;
    long long ans=0;
    if(L<=m)ans+=query(lson[root],L,R,l,m,a+add[root]);
    if(R>m)ans+=query(rson[root],L,R,m+1,r,a+add[root]);
    return ans;
}

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        tot=0;
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        T[0]=build(1,n);
        int t=0;
        char s[3];
        while(m--)
        {
            scanf("%s",s);
            if(s[0]=='C')
            {
                int l,r,d;
                scanf("%d %d %d",&l,&r,&d);
                T[++t]=update(T[t-1],l,r,d,1,n);
            }
            else if(s[0]=='Q')
            {
                int l,r;
                scanf("%d %d",&l,&r);
                printf("%lld\n",query(T[t],l,r,1,n,0));
            }
            else if(s[0]=='H')
            {
                int l,r,_t;
                scanf("%d %d %d",&l,&r,&_t);
                printf("%lld\n",query(T[_t],l,r,1,n,0));
            }
            else
            {
                scanf("%d",&t);
                tot=T[t+1];
            }
        }
    }
    return 0;
}

/******************************************************/
//区间不同数
#include<bits/stdc++.h>
using namespace std;
/*
 * 给出一个序列，查询区间内有多少个不相同的数
 */
const int MAXN = 30010;
const int M = MAXN * 100;
int n,q,tot;
int a[MAXN];
int T[M],lson[M],rson[M],c[M];
int build(int l,int r)
{
    int root = tot++;
    c[root] = 0;
    if(l != r)
    {
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}
int update(int root,int pos,int val)
{
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = n;
    while(l < r)
    {
        int mid = (l+r)>>1;
        if(pos <= mid)
        {
            lson[newroot] = tot++; rson[newroot] = rson[root];
            newroot = lson[newroot]; root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = tot++; lson[newroot] = lson[root];
            newroot = rson[newroot]; root = rson[root];
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int query(int root,int pos)
{
    int ret = 0;
    int l = 1, r = n;
    while(pos < r)
    {
        int mid = (l+r)>>1;
        if(pos <= mid)
        {
            r = mid;
            root = lson[root];
        }
        else
        {
            ret += c[lson[root]];
            root = rson[root];
            l = mid+1;
        }
    }
    return ret + c[root];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d",&n) == 1)
    {
        tot = 0;
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        T[n+1] = build(1,n);
        map<int,int>mp;
        for(int i = n;i>= 1;i--)
        {
            if(mp.find(a[i]) == mp.end())
            {
                T[i] = update(T[i+1],i,1);
            }
            else
            {
                int tmp = update(T[i+1],mp[a[i]],-1);
                T[i] = update(tmp,i,1);
            }
            mp[a[i]] = i;
        }
        scanf("%d",&q);
        while(q--)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",query(T[l],r));
        }
    }
    return 0;
}
/****************************************************/
//区间lcm
/*
把每个数分解成质数形式，如有p^{a1}，那么加入p^1,p^2,p^3..p^{a1},每个权值为p，然后求区间不同数的积
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=30010;
const int M=maxn*100;
int n,q,tot;
int a[maxn];
int T[M],lson[M],rson[M],c[M];
int build(int l,int r)
{
    int root=tot++;
    c[root]=0;
    if(l!=r)
    {
        int mid=l+r>>1;
        lson[root]=build(l,mid);
        rson[root]=build(mid+1,r);
    }
    return root;
}
int update(int root,int pos,int val,int l,int r)
{
    int newroot=tot++;
    lson[newroot]=lson[root];
    rson[newroot]=rson[root];
    if(l==r)
    {
        c[newroot]=c[root]+val;
        return newroot;
    }
    if(l!=r)
    {
        int mid=l+r>>1;
        if(pos<=mid)
            lson[newroot]=update(lson[root],pos,val,l,mid);
        else rson[newroot]=update(rson[root],pos,val,mid+1,r);
    }
    c[newroot]=c[lson[newroot]]*c[rson[newroot]];
    return newroot;
}
int query(int root,int L,int R,int l,int r)
{
    if(L<=l&&r<=R)
        return c[root];
    int m=l+r>>1;
    int res=1;
    if(L<=m)res*=query(lson[root],L,R,l,m);
    if(R>m)res*=query(rson[root],L,R,m+1,r);
    return res;
}
//
bool is[maxn];
int prm[maxn],id;
void init()
{
    int k=0;
    memset(is,1,sizeof(is));
    is[0]=is[1]=0;
    for(int i=2;i<maxn;i++)
    {
        if(is[i])prm[k++]=i;
        for(int j=0;j<k&&(i*prm[j]<maxn);j++)
        {
            is[i*prm[j]]=0;
            if(i%prm[j]==0)break;
        }
    }
    id=k;
}
int factor[100][2];
int fatCnt;
int getFactors(long long x)
{
    fatCnt=0;
    long long tmp=x;
    for(int i=0;prm[i]<=tmp/prm[i];i++)
    {
        factor[fatCnt][1]=0;
        if(tmp%prm[i]==0)
        {
            factor[fatCnt][0]=prm[i];
            while(tmp%prm[i]==0)
            {
                factor[fatCnt][1]++;
                tmp/=prm[i];
            }
            fatCnt++;
        }
    }
    if(tmp!=1)
    {
        factor[fatCnt][0]=tmp;
        factor[fatCnt++][1]=1;
    }
    return fatCnt;
}
int main()
{
    init();
    int n;
    scanf("%d",&n);
    tot=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    T[n+1]=build(1,n);
    map<int,int>mp;
    for(int i=n;i>=1;i--)
    {
        if(a[i]==1)
        {
            T[i]=update(T[i+1],i,1,1,n);
            continue;
        }
        T[i]=T[i+1];
        int fat=getFactors(a[i]);
        int num=0;
        for(int j=0;j<fat;j++)
        {
            int it=factor[j][0];
            num+=it*factor[j][1];
            for(int k=0;k<factor[j][1];k++,it*=factor[j][0])
            {
                if(mp.find(it)!=mp.end())
                    T[i]=update(T[i],mp[it],-factor[j][0],1,n);
                mp[it]=i;
            }
        }
        T[i]=update(T[i],i,num,1,n);
    }
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        printf("%d\n",query(T[l],l,r,1,n));
    }
    return 0;
}


