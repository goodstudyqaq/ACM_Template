//该题已知多边形与圆原点，求圆半径使得所交面积占多边形面积比率为(Q-P)/Q
//多边形与圆交
#include<bits/stdc++.h>
using namespace std;
const int maxn=205;
const double eps=1e-10;
const double PI=acos(-1.0);
int sgn(double x)
{
    if(fabs(x)<eps)return 0;
    if(x>0)return 1;
    return -1;
}
struct Point
{
    double x,y;
    Point(){}
    Point(double sx,double sy):x(sx),y(sy){}
    void read()
    {
        scanf("%lf %lf",&x,&y);
    }
    Point operator-(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator^(const Point &b)const
    {
        return x*b.y-y*b.x;
    }
    double operator*(const Point &b)const
    {
        return x*b.x+y*b.y;
    }
    double getdis()
    {
        return sqrt(x*x+y*y);
    }
    Point operator+(const Point &b)const
    {
        return Point(x+b.x,y+b.y);
    }
}Poly[maxn];
double PS;
int n;
bool InCircle(Point a,double r)
{
    if(sgn(a.getdis()-r)<=0)return 1;
    return 0;
}
typedef const Point CP;
Point intersection(CP &u1,CP &u2,CP &v1,CP &v2)
{
    Point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
            /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
double dis(CP &a,CP &b)
{
    double x=a.x-b.x;
    double y=a.y-b.y;
    return sqrt(x*x+y*y);
}
void intersection_line_circle(CP &c,double r,CP &l1,CP &l2,Point &p1,Point &p2)
{
    Point p=c;
    double t;
    p.x+=l1.y-l2.y;
    p.y+=l2.x-l1.x;
    p=intersection(p,c,l1,l2);
    t=sqrt(r*r-dis(p,c)*dis(p,c))/dis(l1,l2);
    p1.x=p.x+(l2.x-l1.x)*t;
    p1.y=p.y+(l2.y-l1.y)*t;
    p2.x=p.x-(l2.x-l1.x)*t;
    p2.y=p.y-(l2.y-l1.y)*t;
}
bool Inmid(Point a,Point b,Point c)
{
    if(sgn((c-a).getdis()+(c-b).getdis()-(a-b).getdis())<=0)return 1;
    return 0;
}
double getang(Point a,Point b)
{
    double ang=atan2(b.y,b.x)-atan2(a.y,a.x);
    if(sgn(ang+PI)<0)ang+=2*PI;
    if(sgn(ang-PI)>0)ang-=2*PI;
    return ang;
}
double xmult(Point a,Point b,Point c)
{
    return (a-c)^(b-c);
}
double disptoline(CP &p,CP &l1,CP &l2)
{
    return fabs(xmult(p,l1,l2))/dis(l1,l2);
}
int intersect_seg_circle(CP &c,double r,CP &l1,CP &l2)
{
    double t1=dis(c,l1)-r,t2=dis(c,l2)-r;
    Point t=c;
    if(t1<eps||t2<eps)
        return t1>-eps||t2>-eps;
    t.x+=l1.y-l2.y;
    t.y+=l2.x-l1.x;
    return xmult(l1,c,t)*xmult(l2,c,t)<eps&&disptoline(c,l1,l2)-r<eps;
}
double sqr(double x){return x*x;}
double dis2(Point a,Point b)
{
    double x=a.x-b.x;
    double y=a.y-b.y;
    return x*x+y*y;
}
double area_triangle(CP &p1,CP &p2,CP &p3)
{
    return fabs(xmult(p1,p2,p3))/2;
}
double area_circle_angle(CP &p1,CP &p2,CP &c,double r)
{
    double alpha=fabs(atan2(p1.y-c.y,p1.x-c.x)-atan2(p2.y-c.y,p2.x-c.x));
    if(alpha>PI)alpha=2*PI-alpha;
    return alpha/2*r*r;
}
double dmult(CP &p1,CP &p2,CP &p0)
{
    return (p1-p0)*(p2-p0);
}
double disptoseg(CP &p,CP &l1,CP &l2)
{
    Point t=p;
    t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
    if(xmult(l1,t,p)*xmult(l2,t,p)>eps)
        return dis(p,l1)<dis(p,l2)?dis(p,l1):dis(p,l2);
    return fabs(xmult(p,l1,l2))/dis(l1,l2);
}
double area_triangle_circle(CP &c,double r,CP &p1,CP &p2)
{
    double x=xmult(p2,c,p1);
    int flag=sgn(x);
    if(flag==0)return 0;
    double r2=sqr(r);
    double s=0,l1=dis2(p1,c),l2=dis2(p2,c);
    if((l1<=r2)&&(l2<=r2))
        return area_triangle(p2,c,p1)*flag;
    if((l1>r2)&&(l2>r2))
    {
        Point p3,p4;
        s=area_circle_angle(p2,p1,c,r);
        if(disptoseg(c,p1,p2)<r)
        {
            intersection_line_circle(c,r,p1,p2,p3,p4);
            if(dis2(p3,p1)>dis2(p4,p1))
                swap(p3,p4);
            s-=area_circle_angle(p3,p4,c,r)-area_triangle(p3,c,p4);
        }
        return s*flag;
    }
    if(l1<l2)
    {
        Point p3,p4;
        intersection_line_circle(c,r,p1,p2,p3,p4);
        if(dmult(p3,p2,p1)<=0)p3=p4;
        s=area_triangle(p1,p3,c)+area_circle_angle(p3,p2,c,r);
        return s*flag;
    }
    else
    {
        Point p3,p4;
        intersection_line_circle(c,r,p1,p2,p3,p4);
        if(dmult(p3,p1,p2)<=0)p3=p4;
        s=area_triangle(p2,p3,c)+area_circle_angle(p3,p1,c,r);
        return s*flag;
    }
}
double getS(double r)
{
   double ans=0;
   for(int i=1;i<=n;i++)
       ans+=area_triangle_circle(Point(0,0),r,Poly[i],Poly[i%n+1]);
   return fabs(ans);
}
bool check(double r,double haveS)
{
    double thes=getS(r);
    if(sgn(thes-haveS)<=0)
        return 1;
    return 0;
}
void solve()
{
    double x,y,P,Q;
    scanf("%lf %lf %lf %lf",&x,&y,&P,&Q);
    for(int i=1;i<=n;i++)Poly[i]=Poly[i]-Point(x,y);
    P=Q-P;
    //double haveS=PS*p;
    double l=0,r=1e7;
    for(int t=1;t<=100;t++)
    {
        double mid=(l+r)/2;
        double a=getS(mid);
        if(a*Q<P*PS)
            l=mid;
        else r=mid;
    }
    for(int i=1;i<=n;i++)Poly[i]=Poly[i]+Point(x,y);
    printf("%.12f\n",l+eps);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        Poly[i].read();
    for(int i=2;i<n;i++)
        PS+=((Poly[i]-Poly[1])^(Poly[i+1]-Poly[1]));
    PS*=0.5;
    if(PS<0)
    {
        reverse(Poly+1,Poly+1+n);
        PS*=-1;
    }
    int Q;
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
        solve();
    return 0;
}
