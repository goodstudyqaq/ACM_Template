//二维BIT区间更新单点查询
//使用前先resize bit的大小
#define lowbit(x) x&-x
vector<int>bit[maxn];
int n,m,T;
inline void add(int x,int y,int z)
{
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j))
        bit[i][j]+=z;
}
inline void update(int x1,int y1,int x2,int y2,int z)
{
    add(x1,y1,z);add(x2+1,y2+1,z);
    add(x1,y2+1,-z);add(x2+1,y1,-z);
}
inline int query(int x,int y)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
        res+=bit[i][j];
    return res;
}
