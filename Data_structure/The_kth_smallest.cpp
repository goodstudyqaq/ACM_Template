//带插入及修改的区间k小询问
/*
BZOJ 3065: 带插入区间 K 小值 带插入、修改的区间 k 小值在线查询。
 1. Q x y k: 询问从左至右第 x 只跳蚤到从左至右第 y 只跳蚤中，弹跳力第 k 小的跳蚤的弹 跳力是多少。(1 <= x <= y <= m,1 <= k <= y−x +1) 
 2. M x val: 将从左至右第 x 只跳蚤的弹跳力改为 val。(1 <= x <= m) 
 3. I x val: 在从左至右第 x 只跳蚤的前面插入一只弹跳力为 val 的跳蚤。即插入后从左至右 第 x 只跳蚤是我刚插入的跳蚤。(1 <= x <= m+1) 
*/
#include<bits/stdc++.h>
#define alpha 0.75
#define N 10000005
using namespace std;
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
int tmp;
int n,m,sz,lastans,root;
int v[70005],dfn[70005],rt[70005],ls[70005],rs[70005];
struct seg{int l,r,sum;}a[N];
vector<int> rec,t,p;
inline int newnode()
{
	if(!rec.size())return ++sz;
	else
	{
		int k=rec.back();rec.pop_back();
		return k;
	}
}
void reclaim(int &x)
{
	if(!x)return;
	rec.push_back(x);
	reclaim(a[x].l);reclaim(a[x].r);
	a[x].sum=0;x=0;
}
void insert(int &k,int l,int r,int val,int f)
{
	if(!k)k=newnode();
	if(l==r){a[k].sum+=f;return;}
	int mid=(l+r)>>1;
	if(val<=mid)insert(a[k].l,l,mid,val,f);
	else insert(a[k].r,mid+1,r,val,f);
	a[k].sum=a[a[k].l].sum+a[a[k].r].sum;
	if(!a[k].sum)reclaim(k);
}
void build(int &k,int l,int r)
{
	if(l>r)return;
	if(l==r)
	{
		k=dfn[l];insert(rt[k],0,70000,v[k],1);return;
	}
	int mid=(l+r)>>1;k=dfn[mid];
	build(ls[k],l,mid-1);build(rs[k],mid+1,r);
    for(int i=l;i<=r;i++)
		insert(rt[k],0,70000,v[dfn[i]],1);
}
void del(int &x)
{
	if(!x)return;reclaim(rt[x]);
	del(ls[x]);p.push_back(x);del(rs[x]);
	x=0;
}
void rebuild(int &x)
{
	del(x);int s1=p.size();
	for(int i=1;i<=s1;i++)dfn[i]=p[i-1];
	build(x,1,s1);
	p.clear();
}
int modify(int k,int x,int val)
{
	insert(rt[k],0,70000,val,1);
	int t,L=a[rt[ls[k]]].sum;
	if(L+1==x){t=v[k];v[k]=val;}
	else if(L>=x)t=modify(ls[k],x,val);
	else t=modify(rs[k],x-L-1,val);
	insert(rt[k],0,70000,t,-1);
	return t;
}
void query(int k,int l,int r)
{
	int L=a[rt[ls[k]]].sum,R=a[rt[k]].sum;
	if(l==1&&r==R){t.push_back(rt[k]);return;}
	if(l<=L+1&&r>=L+1)p.push_back(v[k]);
	if(r<=L)query(ls[k],l,r);
	else if(l>L+1)query(rs[k],l-L-1,r-L-1);
	else
	{
		if(l<=L)query(ls[k],l,L);
		if(R>L+1)query(rs[k],1,r-L-1);
	}
}
int solve_query(int L,int R,int K)
{
	query(root,L,R);K--;
	int l=0,r=70000,s1=t.size(),s2=p.size();
	while(l<r)
	{
		int mid=(l+r)>>1,sum=0;
		for(int i=0;i<s1;i++)sum+=a[a[t[i]].l].sum;
		for(int i=0;i<s2;i++)
			if(p[i]>=l&&p[i]<=mid)sum++;
		if(K<sum)
		{
			for(int i=0;i<s1;i++)t[i]=a[t[i]].l;
			r=mid;
		}
		else
		{
			for(int i=0;i<s1;i++)t[i]=a[t[i]].r;
			l=mid+1;K-=sum;
		}
	}
	t.clear();p.clear();
	return l;
}
void insert(int &k,int x,int val)
{
	if(!k)
	{
		k=++n;
		insert(rt[k],0,70000,val,1);
		v[k]=val;
		return;
	}
	insert(rt[k],0,70000,val,1);
	int L=a[rt[ls[k]]].sum;
	if(L>=x)insert(ls[k],x,val);
	else insert(rs[k],x-L-1,val);
	if(a[rt[k]].sum*alpha>max(a[rt[ls[k]]].sum,a[rt[rs[k]]].sum))
	{
		if(tmp)
		{
			if(ls[k]==tmp)rebuild(ls[k]);
			else rebuild(rs[k]);
			tmp=0;
		}
	}
	else tmp=k;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<=n;i++)dfn[i]=i;
	build(root,1,n);
	m=read();
	char ch[2];int x,y,K;
	while(m--)
	{
		scanf("%s",ch);
		x=read();y=read();x^=lastans;y^=lastans;
		switch(ch[0])
		{
		case 'Q':K=read();K^=lastans;lastans=solve_query(x,y,K);printf("%d\n",lastans);break;
		case 'M':modify(root,x,y);break;
		case 'I':tmp=0;insert(root,x-1,y);if(tmp){tmp=0;rebuild(root);}break;
		}
	}
	return 0;
}
