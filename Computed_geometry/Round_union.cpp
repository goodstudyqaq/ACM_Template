//圆并
#include<bits/stdc++.h>
using namespace std;

typedef pair<double,double>P;
const int N=1010;
const double PI=acos(-1.0),eps=1e-8;
int n,i,j,del[N],t;
double a[N],b[N],r[N],d,x,y,u,ans;
P q[N],tmp;
double sqr(double x){return x*x;}
double dis(double x1,double y1,double x2,double y2)
{
    return sqrt(sqr(x1-x2)+sqr(y1-y2));
}
double angle(double a,double b,double c)
{
    return acos((sqr(a)+sqr(b)-sqr(c))/(2*a*b));
}
int sig(double x)
{
    if(fabs(x)<eps)return 0;
    if(x>0)return 1;
    return -1;
}
void cal(int i,double L,double R)
{
    double x1=a[i]+r[i]*cos(L),y1=b[i]+r[i]*sin(L),
           x2=a[i]+r[i]*cos(R),y2=b[i]+r[i]*sin(R);
    ans+=r[i]*r[i]*(R-L-sin(R-L))+x1*y2-x2*y1;
}
int main()
{
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%lf %lf %lf",&a[i],&b[i],&r[i]);
        for(j=0;j<i;j++)if(!sig(r[i]-r[j])&&!sig(a[i]-a[j])&&!sig(b[i]-b[j]))
        {
            r[i]=0;break;
        }
    }
    for(i=0;i<n;i++)for(j=0;j<n;j++)
        if(i!=j&&sig(r[j]-r[i])>=0&&sig(dis(a[i],b[i],a[j],b[j])-r[j]+r[i])<=0)
    {
        del[i]=1;
        break;
    }
    for(i=0;i<n;i++)if(sig(r[i])&&!del[i])
    {
        for(t=j=0;j<n;j++)if(i!=j)
        {
            d=dis(a[i],b[i],a[j],b[j]);
            if(sig(d-r[i]-r[j])>=0||sig(d-fabs(r[i]-r[j]))<=0)continue;
            x=atan2(b[j]-b[i],a[j]-a[i]),y=angle(r[i],d,r[j]);
            tmp=P(x-y,x+y);
            if(sig(tmp.first)<=0&&sig(tmp.second)<=0)q[t++]=P(2*PI+tmp.first,2*PI+tmp.second);
            else if(sig(tmp.first)<0)q[t++]=P(2*PI+tmp.first,2*PI),q[t++]=P(0,tmp.second);
            else q[t++]=tmp;
        }
        if(t)sort(q,q+t);
        for(u=0,j=0;j<t;j++)
            if(sig(u-q[j].first)>=0)u=max(u,q[j].second);
            else cal(i,u,q[j].first),u=q[j].second;
        if(!sig(u))ans+=r[i]*r[i]*2*PI;else cal(i,u,2*PI);
    }
    ans/=2;
    printf("%.3f\n",ans);
}
