//模数为m，余数为a
//下标从1开始
int m[5];
int a[5];
long long M;
void initchina(int n)
{
    M=1;
    for(int i=1;i<=n;i++)M*=m[i];
}
long long extgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0){x=1;y=0;return a;}
    long long d=extgcd(b,a%b,x,y);
    long long t=x;x=y;y=t-a/b*y;
    return d;
}
long long solvechina(int n)
{
    long long x,y,d;
    long long res=0;
    for(int i=1;i<=n;i++)
    {
        long long Mi=M/m[i];
        extgcd(m[i],Mi,y,x);
        long long tmp=Mi*x%M;
        tmp=tmp*a[i]%M;
        res=(res+tmp)%M;
    }
    if(res<0)
        res=(res+M)%M;
    return res;
}

