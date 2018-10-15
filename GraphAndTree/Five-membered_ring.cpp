//判五元环
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int a[205][205];
int n,T;
char s[205];
bitset<205> f[205][205],g;
int main()
{
	scanf("%d",&T);
    for (int z=1;z<=T;++z)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;++i)
		{
			scanf("%s",s+1);
			for (int j=1;j<=n;++j) a[i][j]=s[j]-'0';
		}
		for (int i=1;i<=n;++i) 
			for (int j=1;j<=n;++j) f[i][j].reset();
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
			{
				if (j==i) continue;
				for (int k=1;k<=n;++k)
				{
					if (j==k) continue;
					if (i==k) continue;
					if (a[i][j]&&a[j][k]) 
					{
						f[i][k][j]=1;
					}
				}
			}
		bool flag=false;
		for (int i=1;i<=n;++i)
		{
			for (int j=1;j<=n;++j)
			{
				for (int k=1;k<=n;++k)
				{
					if (j==i) continue;
					if (j==k) continue;
					if (i==k) continue;
					if (a[j][k]==0) continue;
					int tmp1=f[i][j][k];
					int tmp2=f[i][k][j];
					f[i][j][k]=f[i][k][j]=0;
					g=f[i][j]|f[i][k];
					if (g.count()>=2&&f[i][j].count()>=1&&f[i][k].count()>=1) flag=true;
					f[i][j][k]=tmp1;f[i][k][j]=tmp2;
					if (flag) break;
				}
				if (flag) break;
			}
			if (flag) break;
		}
		printf("Case #%d: ",z);

		if (flag) printf("Starfish!\n");else printf("Walk Walk\n");
	}
	return 0;
}
