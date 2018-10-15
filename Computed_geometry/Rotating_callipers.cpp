//求凸多边形直径
//大概讲一下算法步骤
/*
1.计算多边形y方向的端点，我们称之为ymin和ymax
2.通过ymin和ymax构造两条水平切线，由于他们已经是一对对踵点，计算他们之间的距离并维护一个当前的最大值。
3.同时旋转两条线直到其中一条与多边形的一边重合。
4.一个新的对踵点对此时产生。计算新的距离。
5.重复3,4步骤
*/

//xmult(a,b,c)=(a-c)^(b-c) 写的和习惯不太一样
void solve2(int num)
{
    int ymax=-1e5,ymin=1e5;
    int ymaxidx,yminidx;
    for(int i=1;i<=num;i++)
    {
        if(ch[i].y>ymax)
        {
            ymax=ch[i].y;
            ymaxidx=i;
        }
        if(ch[i].y<ymin)
        {
            ymin=ch[i].y;
            yminidx=i;
        }
    }
    int ans=dis2(ch[ymaxidx]-ch[yminidx]);
    ch[num+1]=ch[1];
    for(int t=1;t<=num;t++,yminidx=yminidx%num+1)
    {
        while(xmult(ch[yminidx+1],ch[ymaxidx+1],ch[yminidx])>xmult(ch[yminidx+1],ch[ymaxidx],ch[yminidx]))ymaxidx=ymaxidx%num+1;
        ans=max(ans,dis2(ch[ymaxidx]-ch[yminidx]));
        ans=max(ans,dis2(ch[ymaxidx]-ch[yminidx+1]));
    }
    printf("%d\n",ans);
}
/**************************************************/
//凸多边形最小面积外接矩阵
double solve(int num)
{
    int r=2,q=2,p;
    double res=1e10;
    ch[num+1]=ch[1];
    for(int i=1;i<=num;i++)
    {
        while(sgn(xmult(ch[i+1],ch[r+1],ch[i])-xmult(ch[i+1],ch[r],ch[i]))>0)r=r%num+1;//找到i的对踵点
        while(sgn(dot(ch[i+1],ch[q+1],ch[i])-dot(ch[i+1],ch[q],ch[i]))>0)q=q%num+1;//找到距离i方向最远的点
        if(i==1)p=q;
        while(sgn(dot(ch[i+1],ch[p+1],ch[i])-dot(ch[i+1],ch[p],ch[i]))<=0)p=p%num+1;//q的对踵点
        double a=xmult(ch[i+1],ch[r],ch[i]);//len(i,i+1)*h
        double b=dot(ch[i+1],ch[q],ch[i])-dot(ch[i+1],ch[p],ch[i]);//len(i,i+1)*w
        double c=dot(ch[i+1],ch[i+1],ch[i]);//len(i,i+1)*len(i,i+1)
        res=min(res,a*b/c);
    }
    return res;
}
