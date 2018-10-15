//时间复杂度O(nlogn)
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
int a[1005];
int b[1005];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 1;i <= n;i++)scanf("%d", &a[i]);
        int res = 1;
        b[1] = a[1];
        int ans = 1;
        for (int i = 2;i <= n;i++)
        {
            int j;
            if (a[i] > b[res])
            {
                res++;
                j = res;
            }
            else
                j = upper_bound(b + 1, b + 1 + res, a[i]) - b;
            b[j] = a[i];
            ans = max(ans, res);
        }
        cout << ans << endl;
    }
}
