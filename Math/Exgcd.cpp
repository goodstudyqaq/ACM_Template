//拓展欧几里得算法(求ax+by=gcd的解以及逆元)
//***************************************************
//返回d=gcd(a,b)；和对应于等式ax+by=d中的x，y
long long extgcd(long long a,long long b,long long &x,long long &y)
{
    if(a==0&&b==0)return -1;//无最大公约数
    if(b==0){x=1;y=0;return a;}
    long long d=extgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;//返回gcd(a,b)
}
//****************求逆元******************************
//ax=1(mod n)
long long mod_reverse(long long a,long long n)
{
    long long x,y;
    long long d=extgcd(a,n,x,y);
    if(d==1)return (x%n+n)%n;
    return -1;
}
