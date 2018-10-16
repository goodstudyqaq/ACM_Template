//****************************************
// pollard_rho 算法进行质因数分解
//****************************************
long long factor[100];//质因数分解结果(返回时无序)
int tot;//质因子个数,编号从0到tot-1
long long gcd(long long a,long long b)
{
    long long t;
    while(b)
    {
        t=a;
        a=b;
        b=t%b;
    }
    if(a>=0)return a;
    return -a;
}
//找到一个因子
long long pollard_rho(long long x,long long c)
{
    long long i=1,k=2;
    srand(time(NULL));
    long long x0=rand()%(x-1)+1;
    long long y=x0;
    while(1)
    {
        i++;
        x0=(mult_mod(x0,x0,x)+c)%x;
        long long d=gcd(y-x0,x);
        if(d!=1&&d!=x)return d;
        if(y==x0)return x;
        if(i==k){y=x0;k+=k;}
    }
}
//对n进行素因子分解，存入factor.k设置为107左右即可
void findfac(long long n,int k)
{
    if(n==1)return;
    if(Miller_Rabin(n))
    {
        factor[tot++]=n;
        return;
    }
    long long p=n;
    int c=k;
    while(p>=n)p=pollard_rho(p,c--);//值变化，防止死循环k
    findfac(p,k);
    findfac(n/p,k);
}
//poj 1811
//输入一个N (2<=N<=2^54) 如果是素数 输出prime 否则输出最小素因子
int main()
{
    int T;
    scanf("%d",&T);
    long long n;
    while(T--)
    {
        scanf("%lld",&n);
        if(Miller_Rabin(n))puts("Prime");
        else
        {
            tot=0;
            findfac(n,107);
            long long ans=factor[0];
            for(int i=1;i<tot;i++)ans=min(ans,factor[i]);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
