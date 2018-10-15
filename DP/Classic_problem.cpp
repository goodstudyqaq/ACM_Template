//贴瓷砖问题
//poj2411
//算出所有状态兼容的状态，再dp求答案。
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
const int maxn = 15;
long long dp[maxn][1 << maxn];
long long path[5000000][2];
int cnt;
//横着放所在的两个格子都填充1，竖着放，上面那个填0，下面填1
void get(int width)
{
	cnt = 0;
	for(int i=0;i<(1<<width);i++)
		for (int j = 0;j < (1 << width);j++)
		{
			bool ok = true;
			for (int k = 0;k < width;k++)if(ok)
			{
				if (((i >> k) & 1)==0)
				{
					if (((j >> k) & 1)==0)//上面为0下面为0，不ok
					{
						ok = false;
						break;
					}
				}
				else
				{
					if (((j >> k) & 1) == 0)
						continue;
					k++;
					if (k >= width || ((i >> k) & 1) == 0)
					{
						ok = false;
						break;
					}
					else if (((j >> k) & 1) == 0)
					{
						ok = false;
						break;
					}
				}
			}
			if (ok)
			{
				path[++cnt][0] = i;
				path[cnt][1] = j;
			}
		}
}

int main()
{
	int h, w;
	while (~scanf("%d %d",&h,&w)&&h)
	{
		if (w > h)swap(h, w);
		get(w);
		memset(dp, 0, sizeof(dp));
		dp[0][(1 << w) - 1] = 1;
		for(int i=0;i<h;i++)
			for (int j = 1;j <= cnt;j++)
			{
				dp[i+1][path[j][1]] += dp[i][path[j][0]];
			}
		printf("%lld\n", dp[h][(1 << w) - 1]);
	}
	return 0;
}
//**********************************************************
//直接枚举当前行的操作，那么前一行只能有一种方式与之对应。通过深搜生成所有可行的模拟操作。
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
int n,m,w;  
const int maxn =15;  
long long d[maxn][1<<15];  
int path[5000000][2];//path[10][0]表示第11种(从0计数)兼容方式的前一行二进制形式对应的的值  
//path[10][1]表示第11种(从0计数)兼容方式的后一行二进制形式对应的的值  
//一共可能有(1<<11)*(1<<11)种兼容方式  
  
void get(int c,int pre,int now)//得到具有m列的矩阵的所有对应兼容方式存入path中  
{  
    if(c>m)return ;  
    else if(c==m)  
    {  
        path[w][0]=pre;  
        path[w++][1]=now;  
        return;  
    }  
    get(c+1,(pre<<1)|1,now<<1);  //当前位不放，则前行的当前位必定为1才能兼容且后行为0：c=c+1
    get(c+1,(pre<<1),(now<<1)|1);  //当前位上放，则前行的当前位必定为0才能兼容且后行为1：c=c+1
    get(c+2,(pre<<2)|3,(now<<2)|3);  //当前位右方，则前行的当前2位必定为1才能兼容且后行当前2位为1：c=c+2
}  
  
int main()  
{  
  
    while(scanf("%d%d",&n,&m)==2&&n&&m)  
    {  
        w=0;//兼容方式总数  
        if(m>n)swap(n,m);//始终保持n为行，m为列数，且m较小  
        get(0,0,0);//得到所有兼容方式  
        memset(d,0,sizeof(d));  
        d[0][(1<<m)-1]=1;//假想的第0行且二进制形式为全1时 出现1次  
        for(int i=0; i<n; i++)//共n行  
            for(int j=0; j<w; j++)//每行有w种对应的兼容方式  
            {  
                d[i+1][path[j][1]] +=d[i][path[j][0]];//path[j][0]与path[j][1]分别指兼容的两个二进制  
                //d[i][x]表示第i行且该行的二进制表示为X时，共有多少种摆放骨牌的方式。  
            }  
        printf("%I64d\n",d[n][(1<<m)-1]);  
    }  
    return 0;  
}  
