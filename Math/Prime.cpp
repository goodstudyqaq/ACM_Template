//素数筛
//时间复杂度O(nloglogn)
bool is[maxn];
int prm[maxn], id;
void init()
{
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	int k = 0;
	prm[k++] = 2;
	for (int i = 4;i < maxn;i+=2)is[i] = 0;
	int e = (int)sqrt(0.0 + maxn) + 1;
	int i;
	for (i = 3;i < e;i += 2)if(is[i])
	{
		prm[k++] = i;
		for (int s = 2 * i, j = i*i;j < maxn;j += s)
			is[j] = 0;
	}
	for (;i < maxn;i += 2)if (is[i])prm[k++] = i;
	id = k;
}
//***************************************************
//时间复杂度O(n)
bool is[maxn];
int prm[maxn], id;
void init()
{
    int k = 0;
    memset(is,1,sizeof(is));
    is[0] = is[1] = 0;
    for(int i = 2; i < maxn; ++i) {
        if(is[i]) prm[k++] = i;
        for(int j = 0; j < k && (i*prm[j] < maxn); ++j) {
            is[i*prm[j]] = 0;
            if(i % prm[j] == 0) break;
        }
    }
id=k;
}
/****************************************************/
//大区间素数筛取
//poj2689
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
int small[maxn], prime[maxn];
long long a, b;
void segment_sieve()
{
    for (int i = 0;(ll)i*i <= b;i++)small[i] = 0;
    for (int i = 0;i <= b - a;i++)prime[i] = 0;

    for (int i = 2;(ll)i*i <= b;i++)
    {
        if (!small[i])
        {
            for (int j = i*i;(ll)j*j <= b;j += i)small[j] = 1;
            for (ll j = (a + i-1) / i*i;j <= b;j += i)
            {
                if (j == i)continue;
                prime[j - a] = 1;
            }
        }
    }
}
int main()
{
    while(~scanf("%lld %lld",&a,&b))
    {
        segment_sieve();
        int befidx=-1;
        long long Min=1e6+10,miidx;
        long long Max=0,maidx;
        if(a==1)prime[0]=1; //这句话一定不能忘
        for(int i=0;i<=b-a;i++)if(!prime[i])
        {
            if(befidx==-1)
            {
                befidx=i;
                continue;
            }
            if(i-befidx<Min)
            {
                Min=i-befidx;
                miidx=i;
            }
            if(i-befidx>Max)
            {
                Max=i-befidx;
                maidx=i;
            }
            befidx=i;
        }
        if(Max==0)
            puts("There are no adjacent primes.");
        else
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n",miidx-Min+a,miidx+a,maidx-Max+a,maidx+a);
    }
}
/*************************************************************/
//素数筛取和合数分解
const int maxn=10000;
bool is[maxn];
int prm[maxn], id;
void init()
{
    int k = 0;
    memset(is,1,sizeof(is));
    is[0] = is[1] = 0;
    for(int i = 2; i < maxn; ++i)
    {
        if(is[i]) prm[k++] = i;
        for(int j = 0; j < k && (i*prm[j] < maxn); ++j)
        {
            is[i*prm[j]] = 0;
            if(i % prm[j] == 0) break;
        }
    }
    id=k;
}
long long factor[100][2];
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

