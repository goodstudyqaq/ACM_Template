// KM算法时间复杂度O(nL*nL*nR)
//点的编号从1开始
//若求最小权匹配，可将权值取反，结果取相反数
//hdu2255
#include<bits/stdc++.h>
using namespace std;
const int maxn=305;
const int inf=0x3f3f3f3f;
#define map mp
int nL,nR;
int map[maxn][maxn];//二分图描述
int cx[maxn],cy[maxn];
int dx[maxn],dy[maxn];
int lx[maxn],ly[maxn];
bool find(int u)
{
    dx[u]=1;
    for(int i=1;i<=nR;i++)if(!dy[i]&&lx[u]+ly[i]==map[u][i])
    {
        dy[i]=1;
        if(cy[i]==-1||find(cy[i]))
        {
            cx[u]=i;
            cy[i]=u;
            return 1;
        }
    }
    return 0;
}
int KM()
{
    memset(cx,-1,sizeof(cx));
    memset(cy,-1,sizeof(cy));
    memset(ly,0,sizeof(ly));
    for(int i=1;i<=nL;i++)
    {
        lx[i]=0;
        for(int j=1;j<=nR;j++)
            lx[i]=max(lx[i],map[i][j]);
    }
    for(int u=1;u<=nL;u++)
    {
        while(1)
        {
            memset(dx,0,sizeof(dx));
            memset(dy,0,sizeof(dy));
            if(find(u))break;
            int inc=inf;
            for(int i=1;i<=nL;i++)if(dx[i])
                for(int j=1;j<=nR;j++)if(!dy[j])
                    inc=min(inc,lx[i]+ly[j]-map[i][j]);
            for(int i=1;i<=nL;i++)
                if(dx[i])lx[i]-=inc;
            for(int i=1;i<=nR;i++)
                if(dy[i])ly[i]+=inc;
        }
    }
    int ans=0;
    for(int i=1;i<=nL;i++)if(cx[i]!=-1)
        ans+=map[i][cx[i]];
    return ans;
}

int main()
{
    int N;
    while(~scanf("%d",&N))
    {
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                scanf("%d",&map[i][j]);
        nL=nR=N;
        printf("%d\n",KM());
    }
    return 0;
}
