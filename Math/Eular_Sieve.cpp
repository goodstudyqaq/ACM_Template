//分解质因数求欧拉函数
getFactors(n);
int ret=n;
for(int i=0;i<fatCnt;i++)
    ret=ret/factor[i][0]*(factor[i][0]-1);
/*****************************************/
//筛法欧拉函数
//时间复杂度O(nloglogn)
const int maxn=3000005;
int phi[maxn];
void phi_table(int n)
{
    for(int i=2;i<=n;i++)phi[i]=0;
    phi[1]=1;
    for(int i=2;i<=n;i++)if(!phi[i])
        for(int j=i;j<=n;j+=i)
    {
        if(!phi[j])phi[j]=j;
        phi[j]=phi[j]/i*(i-1);
    }
}
/****************************************/
//求单个数的欧拉函数
long long eular(long long n)
{
    long long ans=n;
    for(int i=2;1LL*i*i<=n;i++)
    {
        if(n%i==0)
        {
            ans-=ans/i;
            while(n%i==0)
                n/=i;
        }
    }
    if(n>1)ans-=ans/n;
    return ans;
}
/***************************************/
//线性筛(同时得到欧拉函数和素数表)
const int maxn=10000000;
bool check[maxn+10];
int phi[maxn+10];
int prime[maxn+10];
int tot;//素数的个数

void phi_and_prime_table(int N)
{
    memset(check,0,sizeof(check));
    phi[1]=1;
    tot=0;
    for(int i=2;i<=N;i++)
    {
        if(!check[i])
        {
            prime[tot++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(i*prime[j]>N)break;
            check[i*prime[j]]=true;
            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            else
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
