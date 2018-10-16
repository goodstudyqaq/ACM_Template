//hdu1540
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 50005;
#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
int n;
struct node
{
	int lmax, rmax, maxx;
	node(int _l,int _r,int _m):lmax(_l),rmax(_r),maxx(_m){}
	node(){}
}nodes[maxn << 2];
void build(int l, int r, int rt)
{
	nodes[rt] = node(r - l + 1, r - l + 1, r - l+1);
	if (l == r)return;
	int m = l + r >> 1;
	build(ls);
	build(rs);
}

void pushup(int rt,int ln,int rn)
{
	nodes[rt] = node(nodes[rt << 1].lmax, nodes[rt << 1 | 1].rmax, 0);
	nodes[rt].maxx = max(nodes[rt << 1].maxx, nodes[rt << 1 | 1].maxx);
	nodes[rt].maxx = max(nodes[rt].maxx, nodes[rt << 1].rmax + nodes[rt << 1 | 1].lmax);
	if (nodes[rt << 1].lmax == ln)
		nodes[rt].lmax = ln + nodes[rt << 1 | 1].lmax;
	if (nodes[rt << 1 | 1].rmax == rn)
		nodes[rt].rmax = rn + nodes[rt << 1].rmax;

}

void update(int L,int C, int l, int r, int rt)
{
	if (l == r)
	{
		if (C)
			nodes[rt] = node(1, 1, 1);
		else
			nodes[rt] = node(0, 0, 0);
		return;
	}
	int m = l + r >> 1;
	if (L <= m)
		update(L, C, ls);
	else
		update(L, C, rs);
	pushup(rt,m-l+1,r-m);
}

int query(int L, int l, int r, int rt)
{
	if (l == r || nodes[rt].maxx == r - l + 1 || nodes[rt].maxx == 0)
		return nodes[rt].maxx;
	int m = l + r >> 1;
	if (L <= m)
	{
		if (L >= m - nodes[rt << 1].rmax + 1)
			return query(L, ls) + query(m + 1, rs);
		else
			return query(L, ls);
	}
	else
	{
		if (L <= m+1 + nodes[rt << 1 | 1].lmax-1)
			return query(L, rs) + query(m, ls);
		else
			return query(L, rs);
	}
}


int main()
{
	int n, m;
	while (~scanf("%d %d", &n, &m))
	{
		build(1, n, 1);
		char s[3];
		int x;
		int stack[50005], tot = 0;
		for (int i = 1;i <= m;i++)
		{
			scanf("%s", s);
			if (s[0] == 'D')
			{
				scanf("%d", &x);
				stack[++tot] = x;
				update(x, 0, 1, n, 1);
			}
			else if (s[0] == 'Q')
			{
				scanf("%d", &x);
				printf("%d\n", query(x, 1, n, 1));
			}
			else
			{
				int tmp = stack[tot--];
				update(tmp, 1, 1, n, 1);
			}
		}
	}
	return 0;
}
