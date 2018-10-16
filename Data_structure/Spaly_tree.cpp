splay树
//HYSBZ-1500
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
typedef long long ll;
const int maxn=5e5+10;
#define fmax fx
int ch[maxn][2],val[maxn],pre[maxn],size[maxn],flip[maxn],setv[maxn];//size 区间结点个数 flip 区间是否被翻转 setv 区间是否被赋为一个值
int sum[maxn],smax[maxn],fmax[maxn],pmax[maxn],S[maxn],root,tot,tot2;// sum 区间和 smax 区间最大子段和 pmax 区间最大前缀和 fmax 区间最大后缀和
/*
 *对于空结点的处理，smax[i] pmax[i] fmax[i] 都要赋为-inf以确保不会被选中
 */
int num[maxn];
char str[maxn];

void NewNode(int &rt,int fa,int v)
{
    if(tot2)
        rt=S[tot2--];
    else
        rt=++tot;
    ch[rt][0]=ch[rt][1]=flip[rt]=setv[rt]=0;
    val[rt]=sum[rt]=smax[rt]=fmax[rt]=pmax[rt]=v;
    pre[rt]=fa;
}
void pushup(int rt)
{
    int ls=ch[rt][0],rs=ch[rt][1];
    size[rt]=size[ls]+size[rs]+1;
    sum[rt]=sum[ls]+sum[rs]+val[rt];
    smax[rt]=max(smax[ls],smax[rs]);
    smax[rt]=max(smax[rt],val[rt]);
    smax[rt]=max(smax[rt],fmax[ls]+val[rt]);
    smax[rt]=max(smax[rt],pmax[rs]+val[rt]);
    smax[rt]=max(smax[rt],fmax[ls]+val[rt]+pmax[rs]);

    pmax[rt]=max(pmax[ls],sum[ls]+val[rt]);
    pmax[rt]=max(pmax[rt],sum[ls]+val[rt]+pmax[rs]);
    fmax[rt]=max(fmax[rs],sum[rs]+val[rt]);
    fmax[rt]=max(fmax[rt],sum[rs]+val[rt]+fmax[ls]);
}
void fson(int rt)
{
    if(!rt)return;
    swap(ch[rt][0],ch[rt][1]);
    swap(fmax[rt],pmax[rt]);
    flip[rt]^=1;
}
void sson(int rt,int v)
{
    if(!rt)return;
    val[rt]=v;
    sum[rt]=v*size[rt];
    pmax[rt]=smax[rt]=fmax[rt]=max(v,sum[rt]);
    setv[rt]=1;
}
void pushdown(int rt)
{
    if(flip[rt])
    {
        fson(ch[rt][0]);
        fson(ch[rt][1]);
        flip[rt]=0;
    }
    if(setv[rt])
    {
        sson(ch[rt][0],val[rt]);
        sson(ch[rt][1],val[rt]);
        setv[rt]=0;
    }
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    pushdown(y);pushdown(x);
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y])ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
    pushup(y);
}
void Splay(int rt,int goal)
{
    //pushdown(rt);
    while(pre[rt]!=goal)
    {
        int y=pre[rt];
        if(pre[y]==goal)
            Rotate(rt,ch[y][0]==rt);
        else
        {
            int kind=ch[pre[y]][0]==y;
            if(ch[y][kind]==rt)
            {
                Rotate(rt,kind^1);
                Rotate(rt,kind);
            }
            else
            {
                Rotate(y,kind);
                Rotate(rt,kind);
            }
        }
    }
    pushup(rt);
    if(goal==0)root=rt;
}
void RotateTo(int k,int goal) //kth
{
    int rt=root;
    pushdown(rt);
    while(size[ch[rt][0]]!=k)
    {
        if(size[ch[rt][0]]>k)
            rt=ch[rt][0];
        else
        {
            k-=(size[ch[rt][0]]+1);
            rt=ch[rt][1];
        }
        pushdown(rt);
    }
    Splay(rt,goal);
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r)return;
    int m=l+r>>1;
    NewNode(rt,fa,num[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    pushup(rt);
}
void Insert(int k,int n)
{
    RotateTo(k,0);
    RotateTo(k+1,root);
    build(0,n-1,ch[ch[root][1]][0],ch[root][1]);
    pushup(ch[root][1]);
    pushup(root);
}
void erase(int rt)
{
    if(!rt)return;
    S[++tot2]=rt;
    erase(ch[rt][0]);
    erase(ch[rt][1]);
}
void Delete(int k,int n)
{
    RotateTo(k-1,0);
    RotateTo(k+n,root);
    erase(ch[ch[root][1]][0]);
    ch[ch[root][1]][0]=0;
    pushup(ch[root][1]);
    pushup(root);
}
void Make_setv(int k,int n,int v)
{
    RotateTo(k-1,0);
    RotateTo(k+n,root);
    sson(ch[ch[root][1]][0],v);
    pushup(ch[root][1]);
    pushup(root);
}
void Flip(int k,int n)
{
    RotateTo(k-1,0);
    RotateTo(k+n,root);
    fson(ch[ch[root][1]][0]);
    pushup(ch[root][1]);
    pushup(root);
}
int getSum(int k,int n)
{
    RotateTo(k-1,0);
    RotateTo(k+n,root);
    return sum[ch[ch[root][1]][0]];
}
int getMaxsum(int k,int n)
{
    RotateTo(k-1,0);
    RotateTo(k+n,root);
    return smax[ch[ch[root][1]][0]];
}
void init(int n)
{
    for(int i=0;i<n;++i)
        scanf("%d",&num[i]);
    ch[0][0]=ch[0][1]=pre[0]=size[0]=flip[0]=setv[0]=0;
    smax[0]=pmax[0]=fmax[0]=-inf;
    sum[0]=val[0]=root=tot=tot2=0;
    NewNode(root,0,0);
    NewNode(ch[root][1],root,0);
    build(0,n-1,ch[ch[root][1]][0],ch[root][1]);
    pushup(ch[root][1]);
    pushup(root);
}

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        init(n);
        while(m--)
        {
            scanf("%s",str);
            if(str[0]=='M'&&str[2]=='X')
                printf("%d\n",getMaxsum(1,size[root]-2));
            else
            {
                 int k,len,v;
                scanf("%d%d",&k,&len);
                if(str[0]=='I')
                {
                    for(int i=0;i<len;++i)
                        scanf("%d",&num[i]);
                    Insert(k,len);
                }
                else if(str[0]=='D')
                    Delete(k,len);
                else if(str[0]=='M')
                {
                    scanf("%d",&v);
                    Make_setv(k,len,v);
                }
                else if(str[0]=='R')
                    Flip(k,len);
                else
                    printf("%d\n",getSum(k,len));
            }
        }
    }
    return 0;
}
