//整数拆分
//将n拆分成多个正整数之和，问有多少种拆法？ 
//如5=1+1+1+1+1=1+1+1+2=1+1+3=1+4=5=1+2+2=2+3.共7种
//方法： 五边形数定理(分拆数)
//直接公式：f[n]=∑(-1)^(k-1)*(f[n-k*(3*k-1)/2]+f[n-k*(3*k+1)/2]) 
//            其中n-k*(3*k-1)/2>=0,n-k*(3*k+1)/2>=0； 
//        注意两个条件要分开判断，有大于0的就加上相应的f，不是两个同时成立或者不成立
#include <stdio.h>  
#include <math.h>  
#include <string.h>  
#include <iostream>  
using namespace std;  
const int mod=1e9+7;  
int f[100010];  
void init()  
{  
    f[0]=1;  
    int i,j,k,flag=1;  
    for(i=1;i<=100000;i++)  
    {  
        f[i]=0;  
        for(j=1;;j++)  
        {  
            int t=i-j*(3*j-1)/2;  
            int tt=i-j*(3*j+1)/2;  
            if(j&1)  
                flag=1;  
            else  
                flag=-1;  
            if(t<0&&tt<0)  
                break;  
            if(t>=0)  
                f[i]=(f[i]+flag*f[t])%mod;  
            if(tt>=0)  
                f[i]=(f[i]+flag*f[tt])%mod;  
        }  
        f[i]=(f[i]+mod)%mod;  
    }  
}  
int main()  
{  
    init();  
    int T;  
    cin>>T;  
    while(T--)  
    {  
        int n;  
        cin>>n;  
        cout<<f[n]<<endl;  
    }  
    return 0;  
}  
//********************************************************
//要求拆分的数中每个数出现的次数不能大于等于k次。
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

typedef __int64 LL;
const int Maxn=100010;
const LL MOD=1000000007;
LL Q[Maxn],P[Maxn];
LL GetQ(LL x)
{
    LL ans=(LL)x*x*3-x;
    return (ans/2)%MOD;
}
void _init()
{
    Q[0]=0;
    for(int i=1;i<Maxn;i++)
    {
        if(i&1) Q[i]=GetQ(i/2+1);
        else Q[i]=GetQ(i/2*(-1));
    }
    P[0]=P[1]=1;
    for(int i=2;i<Maxn;i++)
    {
        for(int j=1;;j++)
        {
            if(Q[j]>i) break;
            int t=j;
            if(t&1) t=t/2+1;
            else t=t/2;
            if(t&1)
                P[i]=(P[i]+P[i-Q[j]]);
            else
                P[i]=(P[i]-P[i-Q[j]]);
            if(P[i]>=MOD) P[i]%=MOD;
            if(P[i]<0) P[i]+=MOD;
        }
    }
}
void solved(LL n,LL k)
{
    LL ans=0;
    for(int i=0;;i++)
    {
        if(Q[i]*k>n) break;
        int t=i;
        if(t&1) t=t/2+1;
        else t=t/2;
        if(t&1) ans=(ans-P[n-Q[i]*k]);
        else ans=(ans+P[n-Q[i]*k]);
        if(ans>=MOD) ans%=MOD;
        if(ans<0) ans+=MOD;
    }
    printf("%I64d\n",ans);
}
int main()
{
    _init();
    int T;
    LL n,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d%I64d",&n,&k);
        solved(n,k);
    }
    return 0;
}
/******************************************************/
//求A^b的约数之和对Mod去取模
//poj 1845
//里面有1+p+p^2+p^3…+p^n的方法
/*
题意:求 A^B的所有约数之和对9901取模后的结果.
    根据唯一分解定理将A进行因式分解可得:A = p1^a1 * p2^a2 * p3^a3 * pn^an.
A^B=p1^(a1*B)*p2^(a2*B)*...*pn^(an*B);
A^B的所有约数之和
sum=[1+p1+p1^2+...+p1^(a1*B)]*[1+p2+p2^2+...+p2^(a2*B)]*[1+pn+pn^2+...+pn^(an*B)].
      等比数列1+pi+pi^2+pi^3+...+pi^n可以由二分求得(即将需要求解的因式分成部分来求解)
       若n为奇数,一共有偶数项,设p为3,
则(1+p)+(p^2+p^3)=(1+p)+p^2(1+p)=(1+p^2)*(1+p)
                  1+p+p^2+p^3+........+p^n=(1+p+p^2+....+p^(n/2))*(1+p^(n/2+1));
       若n为偶数,一共有奇数项,设p为4,
则(1+p)+p^2+(p^3+p^4)=(1+p)+p^2+p^3(1+p)=(1+p^3)*(1+p)+P^2
1+p+p^2+p^3+........+p^n=(1+p+p^2+....+p^(n/2-1))*(1+p^(n/2+1));
*/
/*
POJ 1845 Sumdiv
求A^B的所有约数之和%9901

*/
#include<stdio.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

#define MOD 9901

//******************************************
//素数筛选和合数分解
const int MAXN=10000;
int prime[MAXN+1];
void getPrime()
{
    memset(prime,0,sizeof(prime));
    for(int i=2;i<=MAXN;i++)
    {
        if(!prime[i])prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i;j++)
        {
            prime[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}
long long factor[100][2];
int fatCnt;
int getFactors(long long x)
{
    fatCnt=0;
    long long tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++)
    {
        factor[fatCnt][1]=0;
        if(tmp%prime[i]==0)
        {
            factor[fatCnt][0]=prime[i];
            while(tmp%prime[i]==0)
            {
                factor[fatCnt][1]++;
                tmp/=prime[i];
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

//******************************************
long long pow_m(long long a,long long n)//快速模幂运算
{
    long long res=1;
    long long tmp=a%MOD;
    while(n)
    {
        if(n&1){res*=tmp;res%=MOD;}
        n>>=1;
        tmp*=tmp;
        tmp%=MOD;
    }
    return res;
}
long long sum(long long p,long long n)//计算1+p+p^2+````+p^n
{
    if(p==0)return 0;
    if(n==0)return 1;
    if(n&1)//奇数
    {
        return ((1+pow_m(p,n/2+1))%MOD*sum(p,n/2)%MOD)%MOD;
    }
    else return ((1+pow_m(p,n/2+1))%MOD*sum(p,n/2-1)+pow_m(p,n/2)%MOD)%MOD;

}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int A,B;
    getPrime();
    while(scanf("%d%d",&A,&B)!=EOF)
    {
        getFactors(A);
        long long ans=1;
        for(int i=0;i<fatCnt;i++)
        {
            ans*=(sum(factor[i][0],B*factor[i][1])%MOD);
            ans%=MOD;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
/************************************************/
//lightoj 1282
//给定两个数n,k 求n^k的前三位和最后三位
/*
后三位好求，快速幂模1000即可。 
前三位就需要一点数学知识了。
所有的数可以表示成n={10}^a
这个a一般是小数，那么n^k={10}^{ak}
这里把ak分成两部分，整数和小数部分，即x和y，那么n^k={10}^x\ast{10}^y,这里规定x为整数，y为小数，那么x就是制定位数的，y则是指定值的。
因为n={10}^a,所有a=logn,所以我们只需要求出a*k的小数位，然后乘以100即可。
fmod(x,y),可求出x模y后的值(double类型)
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<math.h>
using namespace std;
typedef long long ll;
int quick_mul(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b % 2)ans = ans*a % 1000;
        a = a*a % 1000;
        b /= 2;
    }
    return ans%1000;
}

int main()
{
    int T, k, n, kase = 0;
    scanf("%d", &T);
    int cas = 1;
    while (T--)
    {
        scanf("%d %d", &n, &k);
        int x = (int)pow(10.0, 2.0 + fmod(1.0*k*log10(1.0*n), 1));
        int y = quick_mul(n, k);
        printf("Case %d: %d %03d\n", cas++, x, y);
    }
    return 0;
}
/*****************************************************/
//lightoj 1245
/*
long long H( int n ) {
    long long res = 0;
    for( int i = 1; i <= n; i++ )
        res = res + n / i;
    return res;
}
快速求出res n<2^31
*/
/*
这题有几个结论比较重要。 
第一个结论: 一个数k出现的区间为(n/(k+1),n/k](k<=sqrt(n)) 
第二个结论:大于sqrt(n)的数并不是所有都出现了，他们的出现都与小于sqrt(n)的一一对应。 
综上，我们可以用sqrt(n)的时间来计算出所有值的和。
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<math.h>
using namespace std;
typedef long long ll;

int main()
{
    int T;
    scanf("%d", &T);
    int cas = 1;
    while (T--)
    {
        ll n;
        scanf("%lld", &n);
        int e = (int)sqrt(0.0 + n);
        ll ans = 0;
        for (int i = 1;i <= e;i++)
        {
            ans += 1LL * (n / i - n / (i + 1))*i + n / i;
            if (i == n / i)ans -= i;
        }
        printf("Case %d: %lld\n", cas++, ans);
    }

}
/**************************************************/
//sgu-106
//你有这么一个方程ax+by+c=0，现在给你a,b,c，再给定l1,r1,l2,r2，询问有几组整数解使得l1<=x<=r1,l2<=y<=r2。
//解不等式，有好多坑的地方。。。 
//首先判断一下a和b为0的情况。 
//除去这种特殊情况后，用exgcd求出答案，那么X=x+k*(b/d),Y=y-k*(a/d)。联立不//等式求出k的范围，为了避免负数的情况，我们可以预处理一下a和b和c的正负。
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<math.h>
using namespace std;
typedef long long ll;
ll extgcd(ll a,ll b,ll &d,ll &x,ll &y)
{
    if(!b)
        d=a,x=1,y=0;
    else
    {
        extgcd(b,a%b,d,y,x);
        y-=a/b*x;
    }
}

int main()
{
    ll a,b,c,x1,x2,y1,y2;
    scanf("%lld %lld %lld %lld %lld %lld %lld",&a,&b,&c,&x1,&x2,&y1,&y2);
    c=-c;
    if(c<0)
        c=-c,a=-a,b=-b;
    if(a<0)
        a=-a,swap(x1,x2),x1=-x1,x2=-x2;
    if(b<0)
        b=-b,swap(y1,y2),y1=-y1,y2=-y2;
    if(a==0||b==0)
    {
        if(a==0&&b==0)
        {
            if(c==0)
                cout<<(x2-x1+1)*(y2-y1+1)<<endl;
            else puts("0");
        }
        else if(a==0)
        {
            ll tmp=c/b;
            if(c%b==0&&tmp>=y1&&tmp<=y2)printf("%lld\n",x2-x1+1);
            else puts("0");
        }
        else if(b==0)
        {
            ll tmp=c/a;
            if(c%a==0&&tmp>=x1&&tmp<=x2)printf("%lld\n",y2-y1+1);
            else puts("0");
        }
    }
    else
    {
        ll x,y,d;
        extgcd(a,b,d,x,y);
        if(c%d)puts("0");
        else
        {
            x=x*(c/d);
            y=y*(c/d);
            double tmp1=b/d;
            double tmp2=a/d;
            ll r=min(floor(1.0*(x2-x)/tmp1),floor(1.0*(y-y1)/tmp2)),l=max(ceil(1.0*(x1-x)/tmp1),ceil(1.0*(y-y2)/tmp2));
            if(l>r)puts("0");
            else printf("%lld\n",r-l+1);
        }
    }
}
