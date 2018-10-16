//模拟退火
//给出n个点，求距所有点最小距离最大的那个点的坐标
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
const double inf=1e10;
const double eps=1e-6;
const double pi=acos(-1.0);
double px[maxn],py[maxn];
double d[maxn];
double cx[maxn],cy[maxn];
double dist(double x1,double y1,double x2,double y2)
{
    double x=x1-x2;
    double y=y1-y2;
    return sqrt(x*x+y*y);
}
int main()
{
    //freopen("input.txt","r",stdin);
    int T;
    scanf("%d",&T);
    srand(time(NULL));
    while(T--)
    {
        int R,C,M;
        scanf("%d %d %d",&R,&C,&M);
        double x,y;
        for(int i=1; i<=M; i++)
        {
            scanf("%lf %lf",&x,&y);
            px[i]=x,py[i]=y;
        }
        for(int i=1; i<=30; i++)
        {
            cx[i]=(rand()%1000+1)*1.0/1000*R;
            cy[i]=(rand()%1000+1)*1.0/1000*C;
            double thed=inf;
            for(int j=1; j<=M; j++)
                thed=min(thed,dist(cx[i],cy[i],px[j],py[j]));
            d[i]=thed;
        }
        double hot=max(R,C)/(sqrt(1.0*M));
        while(hot>eps)
        {
            for(int i=1; i<=30; i++)
            {
                for(int k=1; k<=30; k++)
                {
                    x=cx[i],y=cy[i];
                    double tmp=rand()%10000*1.0/10000*10*pi;
                    double dx=x+hot*cos(tmp);
                    double dy=y+hot*sin(tmp);
                    if(dx>R||dx<0||dy>C||dy<0)
                        continue;
                    double thed=inf;
                    for(int j=1; j<=M; j++)
                        thed=min(thed,dist(dx,dy,px[j],py[j]));
                    if(d[i]<thed)
                    {
                        d[i]=thed;
                        cx[i]=dx;
                        cy[i]=dy;
                    }
                }
            }
            hot*=0.8;
        }
        double ansd=-1;
        int idx;
        for(int i=1; i<=30; i++)
            if(ansd<d[i])
            {
                ansd=d[i];
                idx=i;
            }
        printf("The safest point is (%.1lf, %.1lf).\n",cx[idx],cy[idx]);
    }
    return 0;
}
