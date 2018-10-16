//轮廓面积
//求覆盖至少两次的区域面积
//hdu1255
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 1005;
struct line
{
	double l, r, h;
	int flag;
	line(double _l,double _r,double _h,int _f)
:l(_l),r(_r),h(_h),flag(_f){}
	line(){}
	bool operator<(const line &b)const
	{
		return h < b.h;
	}
}lines[maxn<<1];
struct node
{
	int l, r;
	int cnt;
	double len,len2;
	
	node(int _l,int _r,int _c,double _len,double _len2)
:l(_l),r(_r),cnt(_c),len(_len),len2(_len2){}
	node(){}
}nodes[maxn << 3];

#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1

double X[maxn << 1];
void build(int l, int r, int rt)
{
	nodes[rt] = node(l, r,0, 0,0);
	if (l == r)return;
	int m = l + r >> 1;
	build(ls);
	build(rs);
}

void pushup(int rt)
{
	int lidx = nodes[rt].l, ridx = nodes[rt].r + 1;
	if (nodes[rt].cnt )
		nodes[rt].len = X[ridx] - X[lidx];
	else if (nodes[rt].l == nodes[rt].r)
		nodes[rt].len = 0;
	else
		nodes[rt].len = nodes[rt << 1].len + nodes[rt << 1 | 1].len;

	if (nodes[rt].cnt > 1)
		nodes[rt].len2 = X[ridx] - X[lidx];
	else if (nodes[rt].l == nodes[rt].r)
		nodes[rt].len2 = 0;
	else
		if (nodes[rt].cnt == 1)
		{
			nodes[rt].len2 = nodes[rt << 1].len + nodes[rt << 1 | 1].len;
		}
		else
			nodes[rt].len2 = nodes[rt << 1].len2 + nodes[rt << 1 | 1].len2;
}




void update(int L, int R, int C, int l, int r, int rt)
{
	
	if (L <= l&&r <= R)
	{
		nodes[rt].cnt += C;
		pushup(rt);
		return;
	}
	int m = l + r >> 1;
	if (L <= m)update(L, R, C, ls);
	if (R > m)update(L, R, C, rs);
	pushup(rt);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
		double x1, y1, x2, y2;
		int lnum=0, xnum = 0;
		for (int i = 1;i <= n;i++)
		{
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			lines[lnum++] = line(x1, x2, y1, 1);
			lines[lnum++] = line(x1, x2, y2, -1);
			X[xnum++] = x1;
			X[xnum++] = x2;
		}
		sort(lines, lines + lnum);
		sort(X, X + xnum);
		xnum = unique(X, X + xnum) - X;
		build(0, xnum - 1, 1);
		double ans = 0;
		for (int i = 0;i < lnum - 1;i++)
		{
			int lidx = lower_bound(X, X + xnum, lines[i].l) - X;
			int ridx = lower_bound(X, X + xnum, lines[i].r) - X;
			ridx--;
			update(lidx, ridx, lines[i].flag, 0, xnum - 1, 1);
			ans += nodes[1].len2*(lines[i + 1].h - lines[i].h);
			
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
