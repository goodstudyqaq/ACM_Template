/*
F(n)和f(n)是定义在非负整数集合的两个函数，并且满足F\left(n\right)=\sum_{d|n}f\left(d\right)，那么f\left(n\right)=\sum_{\left\{d|n\right\}}\mu\left(d\right)F\left(n/d\right)
如果是F\left(n\right)=\sum_{n|d}f\left(d\right),那么f\left(n\right)=\sum_{\left\{n|d\right\}}\mu\left(d/n\right)F\left(d\right)
*/
//latex显示不出来。。
const int MAXN=1000000;
bool check[MAXN+10];
int prime[MAXN+10];
int mu[MAXN+10];
void Moblus()
{
    mu[1]=1;
    int tot=0;
    for(int i=2;i<=MAXN;i++)
    {
        if(!check[i])
        {
            prime[tot++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(i*prime[j]>MAXN)break;
            check[i*prime[j]]=true;
            if(i%prime[j]==0)
            {
                mu[i*prime[j]]=0;
                break;
            }
            else
                mu[i*prime[j]]=-mu[i];
        }
    }
}
/***************************************************/
////洛谷求φ 和μ的前缀和
//n小于maxn^{2/3}时线性筛预处理，否则记忆化搜索，单次计算时间复杂度O(n^{2/3})
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define N 5001000
using namespace std;
template<typename T>inline void read(T &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}
bool vis[N];
int mu[N],sum1[N];
long long phi[N],sum2[N];
int cnt,prim[N];
int e,e1;
tr1::unordered_map<long long,long long>w1;
tr1::unordered_map<int,int>w;
void get(int maxn)
{
    phi[1]=mu[1]=1;
    for(int i=2;i<=maxn;i++)
    {
        if(!vis[i])
        {
            prim[++cnt]=i;
            mu[i]=-1;phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&prim[j]*i<=maxn;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)
            {
                phi[i*prim[j]]=phi[i]*prim[j];
                break;
            }
            else mu[i*prim[j]]=-mu[i],phi[i*prim[j]]=phi[i]*(prim[j]-1);
        }
    }
    for(int i=1;i<=maxn;i++)sum1[i]=sum1[i-1]+mu[i],sum2[i]=sum2[i-1]+phi[i];
}
int djsmu(int x)
{
    if(x<=5000000)return sum1[x];
    if(w[x])return w[x];
    int ans=1;
    for(int l=2,r;l<=x;l=r+1)
    {
        r=x/(x/l);
        ans-=(r-l+1)*djsmu(x/l);
    }
    return w[x]=ans;
}
long long djsphi(long long x)
{
    if(x<=5000000)return sum2[x];
    if(w1[x])return w1[x];
    long long ans=x*(x+1)/2;
    for(long long l=2,r;l<=x;l=r+1)
    {
        r=x/(x/l);
        ans-=(r-l+1)*djsphi(x/l);
    }
    return w1[x]=ans;
}
int main()
{
    int t;
    read(t);
    get(5000000);
    while(t--)
    {
        static int n;
        read(n);
        printf("%lld %d\n",djsphi(n),djsmu(n));
    }
    return 0;
}
