//数位dp
//hdu2089 不要62 数位dp模板
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
const int maxn=10;
int dp[maxn][maxn];
int a[maxn];

int dfs(int d,int pre,bool limit,bool lead)
{
    if(d==-1)return 1;
    if(!limit&&!lead&&~dp[d][pre])return dp[d][pre];
    int End=limit?a[d]:9;
    int res=0;
    for(int i=0;i<=End;i++)if(i!=4)
    {
        if(pre==6&&i==2)continue;
        res+=dfs(d-1,i,limit&&i==End,lead&&!i);
    }
    if(!limit&&!lead)dp[d][pre]=res;
    return res;
}

int solve(int num)
{
    int cnt=0;
    while(num)
    {
        a[cnt++]=num%10;
        num/=10;
    }
    return dfs(cnt-1,0,true,true);
}

int main()
{
    int n,m;
    memset(dp,-1,sizeof(dp));
    while(~scanf("%d %d",&n,&m)&&n)
    {
        printf("%d\n",solve(m)-solve(n-1));
    }
    return 0;
}
