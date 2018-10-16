//hdu 1166
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 50005;
int A[maxn],n;
int Sum[maxn << 2], Add[maxn << 2];
#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
void PushUp(int rt) { Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1]; }
void build( int l, int r, int rt)
{
	if (l == r)
	{
		Sum[rt] = A[l];
		return;
	}
	int m = l + r >> 1;
	build(ls);
	build(rs);
	PushUp(rt);
}

void PushDown(int rt, int ln, int rn)
{
	if (Add[rt])
	{
		Add[rt << 1] += Add[rt];
		Add[rt << 1 | 1] += Add[rt];
		Sum[rt << 1] += Add[rt] * ln;
		Sum[rt << 1 | 1] += Add[rt] * rn;
		Add[rt] = 0;
	}
}
void Update(int L, int C, int l, int r, int rt)
{
	if (l == r)
	{
		Sum[rt] += C;
		return;
	}
	int m = l + r >> 1;
	PushDown(rt, m - l + 1, r - m);
	if (L <= m)Update(L, C, ls);
	else Update(L, C, rs);
	PushUp(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
	if (L <= l&&r <= R)
		return Sum[rt];
	int m = l + r >> 1;
	PushDown(rt, m - l + 1, r - m);
	int Ans = 0;
	if (L <= m)Ans += Query(L, R, ls);
	if (R > m)Ans += Query(L, R, rs);
	return Ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	char s[100];
	int a, b;
	for (int time = 1;time <= T;time++)
	{
		scanf("%d", &n);
		for (int i = 1;i <= n;i++)scanf("%d", &A[i]);
		build(1, n, 1);
		memset(Add, 0, sizeof(Add));
		printf("Case %d:\n", time);
		while (~scanf("%s",s)&&s[0]!='E')
		{
			scanf("%d %d", &a, &b);
			if (s[0] == 'Q')
			{
				printf("%d\n", Query(a, b, 1, n, 1));
			}
			else if (s[0] == 'A')
			{
				Update(a, b, 1, n, 1);
			}
			else
			{
				Update(a, -b, 1, n, 1);
			}
		}
	}
	return 0;
}

