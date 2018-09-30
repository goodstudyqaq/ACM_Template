/*最小树形图-朱刘算法
 *相关定义
 *定义: 设G设G = (V,E)是一个有向图，它具有下述性质：
 *1.G种不包含有向环
 *2.存在一个定点V_i,它不是任何弧的终点，而V中的其它顶点都恰好是唯一的一条弧的终点，则称G是以V_i为根的树形图。
 *最小树形图就是有向图G = (V, E)中以vi为根的树形图中权值和最小的那一个。
 */

 //朱刘算法，复杂度O(NM)
 //Hdu2121
/*root为给定根，点从0到NV-1，边从0到NE
 *说明一下不定根的做法
 *如果根节点是不定的，虚拟一个根节点，到每个结点都有一条边，
 *其到每个节点的权值应该相等，表明每个结点都应该且有机会当根
 *且边的权值应比总权值大一些。如果最终算出来的最小树形图的总
 *权值大于原图的总权值+虚根到实根(也就是原图的总权值+1)，
 *其实就是算出来的最小树形图的总权值大于等于原图总权值的二倍+2，
 *就不能构成有向图的最小树形图。
 */
#include<bits/stdc++.h>
using namespace std;
#define N 1010
#define INF 0x7f7f7f7f
struct Edge
{
    int u,v,w;
} e[N*N];
int cnt;
int in[N];
int vis[N],pre[N],id[N];
int minroot;
void addedge(int u,int v,int w)
{
    e[cnt].u=u;
    e[cnt].v=v;
    e[cnt++].w=w;
}
int Directed_MST(int root,int NV,int NE)
{
    int ret = 0;
    while(true)
    {
        ///步骤1：找到最小边
        for(int i = 0; i < NV; i ++)
            in[i] = INF;
            memset(pre,-1,sizeof(pre));
        for(int i = 0; i < NE; i ++)
        {
            int u = e[i].u , v = e[i].v;
            if(e[i].w < in[v] && u != v)
            {
                pre[v] = u;
                in[v] = e[i].w;
                if(u==root) minroot=i;
            }
        }
        for(int i = 0; i < NV; i ++)
        {
            if(i == root) continue;
            if(in[i] == INF) return -1;///除了根节点以外有点没有入边，则根无法到达他
        }
        int cntnode = 0;
        memset(id,-1,sizeof(id));
        memset(vis,-1,sizeof(vis));
        ///找环
        in[root] = 0;
        for(int i = 0; i < NV; i ++) ///标记每个环，编号
        {
            ret += in[i];
            int v = i;
            while(vis[v] != i && id[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)
            {
                for(int u = pre[v]; u != v; u = pre[u])
                {
                    id[u] = cntnode;
                }
                id[v] = cntnode ++;
            }
        }
        if(cntnode == 0) break;//无环
        for(int i = 0; i < NV; i ++)
            if(id[i] == -1)
                id[i] = cntnode ++;
        ///步骤3：缩点，重新标记
        for(int i = 0; i < NE; i ++)
        {
            int u=e[i].u;
            int v = e[i].v;
            e[i].u = id[u];
            e[i].v = id[v];
            if(e[i].u != e[i].v) e[i].w -= in[v];
        }
        NV = cntnode;
        root = id[root];
    }
    return ret;///最小树形图的长度
}
int main()
{
    int n,m,sum;
    int u,v,w;
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        cnt=0;sum=0;
        for(int i=0; i<m; i++)
        {
            scanf("%d %d %d",&u,&v,&w);
            addedge(u+1,v+1,w);
            sum+=w;
        }
        sum++;
        for(int i=1; i<=n; i++)
            addedge(0,i,sum);
        int ans=Directed_MST(0,n+1,cnt);
        if(ans==-1||ans>=2*sum)
            printf("impossible\n\n");
        else
            printf("%d %d\n\n",ans-sum,minroot-m);
    }
    return 0;
}

 
