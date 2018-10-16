//求轮廓周长
//poj1177
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
const int maxn = 5005;
struct line
{
	int l, r, h;
	int flag;
	line(int _l,int _r,int _h,int _f):l(_l),r(_r),h(_h),flag(_f){}
	line(){}
	bool operator<(const line &b)const
	{
		return h < b.h;
	}
}lines[maxn << 1];
struct node
{
	int l, r;
	int cnt;
	int len;
	int num; //所包含的区间数量，如三条[1,2]，[2,3]，[4,5]线段被覆盖，则line=2，      因为 [1,2]，[2,3]是连续的。这个是用来辅助计算垂直边的
	bool left, right; //左右端点是否被覆盖，用来辅助对line的计算
	node(int _l,int _r,int _c,int _len,int _num,bool _le,bool _ri)
	:l(_l),r(_r),cnt(_c),len(_len),num(_num),left(_le),right(_ri){}
	node(){}
}nodes[maxn << 3];
int X[maxn << 1];
#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
void build(int l, int r, int rt)
{
	nodes[rt] = node(l, r, 0, 0,0,0,0);
	if (l == r)return;
	int m = l + r >> 1;
	build(ls);
	build(rs);
}
void pushup(int rt)
{
	int lidx = nodes[rt].l, ridx = nodes[rt].r + 1;
	if (nodes[rt].cnt)
		nodes[rt].len = X[ridx] - X[lidx];
	else if (nodes[rt].l == nodes[rt].r)
		nodes[rt].len = 0;
	else
		nodes[rt].len = nodes[rt << 1].len + nodes[rt << 1 | 1].len;

	if (nodes[rt].cnt)
		nodes[rt].num = 1, nodes[rt].left = nodes[rt].right = 1;
	else if (nodes[rt].l == nodes[rt].r)
		nodes[rt].num = 0, nodes[rt].left = nodes[rt].right = 0;
	else
	{
		nodes[rt].num = nodes[rt << 1].num + nodes[rt << 1 | 1].num;
		nodes[rt].left = nodes[rt << 1].left;
		nodes[rt].right = nodes[rt << 1 | 1].right;
		if (nodes[rt << 1].right == nodes[rt << 1 | 1].left&&nodes[rt << 1].right)
			nodes[rt].num--;
	}
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
	if (L <= m)
		update(L, R, C, ls);
	if (R > m)
		update(L, R, C, rs);
	pushup(rt);
}


int main()
{
	int n;
	scanf("%d", &n);
	int x1, x2, y1, y2;
	int lnum = 0, xnum = 0;
	for (int i = 1;i <= n;i++)
	{
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		lines[lnum++] = line(x1, x2, y1, 1);
		lines[lnum++] = line(x1, x2, y2, -1);
		X[xnum++] = x1;
		X[xnum++] = x2;
	}
	sort(lines, lines + lnum);
	sort(X, X + xnum);
	xnum = unique(X, X + xnum)-X;
	int before = 0;
	int change;
	int ans = 0;
	int lidx, ridx;
	build(0, xnum - 1, 1);
	for (int i = 0;i < lnum-1;i++)
	{
		lidx = lower_bound(X, X + xnum, lines[i].l) - X;
		ridx = lower_bound(X, X + xnum, lines[i].r) - X;
		ridx--;
		update(lidx, ridx, lines[i].flag, 0, xnum - 1, 1);
		change = abs(nodes[1].len - before);
		ans += change + 2 * (lines[i + 1].h - lines[i].h)*nodes[1].num;
		before = nodes[1].len;
		//cout << ans << endl;
	}
	lidx = lower_bound(X, X + xnum, lines[lnum - 1].l) - X;
	ridx = lower_bound(X, X + xnum, lines[lnum - 1].r) - X;
	ridx--;
	update(lidx, ridx, lines[lnum - 1].flag, 0, xnum - 1, 1);
	ans += abs(nodes[1].len-before);
	cout << ans << endl;
}
