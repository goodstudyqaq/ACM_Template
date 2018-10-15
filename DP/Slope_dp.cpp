//斜率dp
//打出决策表，发现决策单调就可以用了。
//hdu3507 斜率优化模板题
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=500005;
const ll inf=1e18;
ll sum[maxn];
ll dp[maxn];
int Q[maxn];
long long getup(int j,int k)
{
    return 0LL+dp[j]+1LL*sum[j]*sum[j]-dp[k]-1LL*sum[k]*sum[k];
}
long long getdown(int j,int k)
{
    return 2LL*(sum[j]-sum[k]);
}
int n,m;
ll Cal(int idx,int need)
{
    return dp[idx]+(sum[need]-sum[idx])*(sum[need]-sum[idx])+m;
}

int main()
{

    while(~scanf("%d %d",&n,&m))
    {
        ll tmp;
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&tmp);
            sum[i]=tmp;
            sum[i]+=sum[i-1];
        }
        int front=0,tail=0;
        Q[0]=0;
        for(int i=1;i<=n;i++)
        {
            while(front<tail&&getup(Q[front+1],Q[front])<=sum[i]*getdown(Q[front+1],Q[front]))front++;
            int idx=Q[front];
            dp[i]=Cal(idx,i);
            while(front<tail&&getup(i,Q[tail])*getdown(Q[tail],Q[tail-1])<=getup(Q[tail],Q[tail-1])*getdown(i,Q[tail]))tail--;
            Q[++tail]=i;
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
//******************************************************
//四边形优化
//四边形优化多用于2维dp，一般复杂度n^3，经过优化后就是n^2了。
//只要知道决策单调就可以用，s[i][j]存决策点。
//那么就有  s[i-1][j]<=s[i][j]<=s[i][j+1]和s[i][j-1]<=s[i][j]<=s[i+1][j]根据题意来用这两个式子
//poj1160
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
const int maxn=305;
const int inf=0x3f3f3f3f;
int a[maxn];
int dp[35][maxn];
int s[35][maxn];
int w[maxn][maxn];
int v,p;
void getw()
{
    for(int i=1;i<=v;i++)
    {
        w[i][i]=0;
        for(int j=i+1;j<=v;j++)
            w[i][j]=w[i][j-1]+a[j]-a[(i+j)>>1];
    }
}
int main()
{

    scanf("%d %d",&v,&p);
    for(int i=1;i<=v;i++)
        scanf("%d",&a[i]);
    getw();
    memset(dp,inf,sizeof(dp));
    for(int i=1;i<=v;i++)
    {
        s[1][i]=0;
        dp[1][i]=w[1][i];
    }
    for(int i=2;i<=p;i++)
        for(int j=v;j>=i;j--)
        {
            int tmp=inf;
            int idx;
            s[i][v+1]=v;
            for(int k=s[i-1][j];k<=s[i][j+1];k++)
            {
                if(tmp>dp[i-1][k]+w[k+1][j])
                {
                    tmp=dp[i-1][k]+w[k+1][j];
                    idx=k;
                }
            }
            dp[i][j]=tmp;
            s[i][j]=idx;
        }
    cout<<dp[p][v]<<endl;
    return 0;
}

