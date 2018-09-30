//返回最小生成树权值，返回-1表示原图不连通
const int maxn=30;
const int maxm=80;
const int inf=0x3f3f3f3f;
int G[maxn][maxn];
int lowcost[maxn];
int closest[maxn];
int prim(int n)
{
    memset(closest,0,sizeof(closest));
    memset(lowcost,inf,sizeof(lowcost));
    closest[0]=-1;
    int newnode=0;
    int num=0,ans=0;
    while(num<n-1)
    {
        int micost=inf,theidx;
        for(int i=0;i<n;i++)if(closest[i]!=-1)
        {
            if(lowcost[i]>G[i][newnode])
                lowcost[i]=G[i][newnode];
            if(lowcost[i]<micost)
            {
                micost=lowcost[i];
                theidx=i;
            }
        }
        if(micost==inf)return -1;
        ans+=micost;
        closest[theidx]=-1;
        newnode=theidx;
        num++;
    }
    return ans;
}
//
//
//Kruskal求MST
//顶点从1到n，边的下标从0到tot-1
const int maxn = 55;
const int maxm = 3000;
struct Edge
{
	int from, to, dist;
	Edge(int _f,int _t,int _d):from(_f),to(_t),dist(_d){}
	Edge(){}
}edges[maxm];
int tot;
void addedge(int u, int v, int dist)
{
	edges[tot++] = Edge(u, v, dist);
}
int f[maxn], e[maxm];
bool cmp(int a, int b)
{
	return edges[a].dist < edges[b].dist;
}
int find(int a) { return a == f[a] ? a : f[a] = find(f[a]); }
int kruskal(int n,int m)
{
	for (int i = 1;i <= n;i++)f[i] = i;
	for (int i = 0;i < tot;i++)e[i] = i;
	sort(e, e + tot, cmp);
	int num = 0, ans = 0;
	for (int i = 0;i < tot;i++)
	{
		if (num == n - 1)break;
		int u = edges[e[i]].from, v = edges[e[i]].to, dis = edges[e[i]].dist;
		int rootu = find(u), rootv = find(v);
		if (rootu != rootv) { f[rootu] = rootv; ans += dis; num++; }
		else continue;
	}
	if(num<n-1)return -1;
	return ans;
}
//

