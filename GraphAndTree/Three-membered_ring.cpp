//枚举三元环
#include<bits/stdc++.h>
using namespace std;
const int N=100010,M=200010,Base=(1<<21)-1;
struct edge{int v,w;edge *nxt;}epool[M],*ecur=epool,*g[N],*j,*k;
struct Edge{int x,y,w;Edge *nxt;}Epool[M],*Ecur=Epool,*G[Base+1],*l;
int n,m,i,d[N],x,y,lim,Hash;
struct Elist{int x,y,w;}e[M];
bool cmp(const Elist &a,const Elist &b){return a.x==b.x?a.y<b.y:a.x<b.x;}
int vis(int x,int y)
{
    for(l=G[(x<<8|y)&Base];l;l=l->nxt)if(l->x==x&&l->y==y)return l->w;
    return 0;
}
int main()
{
    while(~scanf("%d %d",&n,&m))
    {
        while(lim*lim<m)lim++;
        for(i=1;i<=m;i++)
        {
            scanf("%d %d",&x,&y);
            if(x<y)swap(x,y);
            e[i].x=x,e[i].y=y;
        }
        for(sort(e+1,e+1+m,cmp),i=1;i<=m;i++)
        {
            d[x=e[i].x]++;
            ecur->v=y=e[i].y;ecur->w=i;ecur->nxt=g[x];g[x]=ecur++;
            Ecur->x=x;Ecur->y=y;Ecur->w=i;Ecur->nxt=G[Hash=(x<<8|y)&Base];G[Hash]=Ecur++;
        }
        for(i=3;i<=n;i++)for(j=g[i];j;j=j->nxt)if(d[x=j->v]<=lim){
            for(k=g[x];k;k=k->nxt)if(y=vis(i,k->v)){
                //三条边分别为e[j->w] e[k->w] e[y]
                //与x点相连的两条边分别为e[j->w] e[k->w]
                //与i点相连的两条边分别为e[j->w] e[y]
                //与k->v点相连的两条分别为e[k->w] e[y]
            }
        }else for(k=j->nxt;k;k=k->nxt)if(y=vis(x,k->v)){
            //三条边分别为e[j->w] e[k->w] e[y]
            //与i点相连的两条边分别为e[j->w] e[k->w]
            //与x点相连的两条边分别为e[j->w] e[y]
            //与k->v点相连的两条边分别为e[k->w] e[y]
        }
        lim=0,ecur=epool,Ecur=Epool;
        for(i=1;i<=n;i++)d[i]=0,g[i]=NULL;
        for(i=1;i<=m;i++)G[(e[i].x<<8|e[i].y)&Base]=NULL;
    }
}
