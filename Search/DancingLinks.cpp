//DLX模板(Poj 3074)数独
//有必要的时候需将模板进行修改，如有的时候仅需要找到一个ans就返回而不需要找最小，
//所以将dance函数改成bool类型，返回条件稍微修改一下。
//有时候重复覆盖需找最大值，则估价函数同样也需要修改。
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
using namespace std;
const int maxnode = 60000;
const int maxn = 800;
const int maxm = 350;
const int inf = 0x3f3f3f;
struct DLX
{
        int n, m, size;
        int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
        int H[maxn];//行头结点
        int S[maxm];//每一列有多少结点
        int ansd, ans[maxn];//如果有答案,择选了ansd行,放在ans[]数组里面0~ansd-1
        char cans[16*16+10];
        void init(int _n, int _m)
        {
                n = _n, m = _m;
                memset(cans, '\0', sizeof(cans));
                ansd = inf;
                for (int i = 0;i <= m;i++)
                {
                        S[i] = 0;
                        U[i] = D[i] = i;//初始状态下,上下自己指向自己(也就知道了头结点的值为i)
                        L[i] = i - 1;
                        R[i] = i + 1;
                }
                R[m] = 0, L[0] = m;//环状,下面的Link一样也是环,这样，不管从一行中的任意一个结点都可以遍历完这一行.
                size = m;//编号,每列的头结点编号1-m，所以size从m+1开始
                for (int i = 1;i <= n;i++)
                        H[i] = -1;
        }
        void link(int r, int c)//第r行,第c列
        {
                ++S[Col[++size] = c];//第size个结点的列为c,当前列的节点数++
                Row[size] = r;//第size个节点行位置为r
                D[size] = D[c];
                U[D[c]] = size;
                U[size] = c;
                D[c] = size;
                if (H[r] < 0)
                        H[r] = L[size] = R[size] = size;
                else
                {
                        R[size] = R[H[r]];
                        L[R[H[r]]] = size;
                        L[size] = H[r];
                        R[H[r]] = size;
                }
        }
        void exact_remove(int c)//删除节点c(列c),并且删除所有在这一列的节点所在的行中的所有的节点。。
        {
                L[R[c]] = L[c];
                R[L[c]] = R[c];
                for(int i=D[c];i!=c;i=D[i])
                        for (int j = R[i];j != i;j = R[j])
                        {
                                U[D[j]] = U[j];
                                D[U[j]] = D[j];
                                --S[Col[j]];
                        }
        }
        void repeat_remove(int c)//只删除列
        {
                for (int i = D[c];i != c;i = D[i])
                        L[R[i]] = L[i], R[L[i]] = R[i];
        }
        void exact_resume(int c)//恢复节点c(列c),以及恢复所有在这一列的节点所在的行中的所有的节点。
        {
                for (int i = U[c];i != c;i = U[i])
                        for (int j = L[i];j != i;j = L[j])
                                ++S[Col[U[D[j]] = D[U[j]] = j]];
                L[R[c]] = R[L[c]] = c;
        }
        void repeat_resume(int c)
        {
                for (int i = U[c];i != c;i = U[i])
                        L[R[i]] = R[L[i]] = i;
        }
        bool exact_dance(int d)//深度
        {
                if (R[0] == 0)
                {
            ansd = d;
                        return 1;
                }
                int c = R[0];
                for (int i = R[0];i != 0;i = R[i])
                        if (S[i] < S[c])
                                c = i;
                exact_remove(c);//找到节点数最少的列,当前元素不是原图上0,1的节点,而是列头结点
                for (int i = D[c];i != c;i = D[i])
                {
                        ans[d] = Row[i];//列头结点下面的一个节点
                        for (int j = R[i];j != i;j = R[j])
                                exact_remove(Col[j]);
                        if(exact_dance(d + 1))return 1;
                        for (int j = L[i];j != i;j = L[j])
                                exact_resume(Col[j]);
                }
                exact_resume(c);
                return 0;
        }
        int f()  //估价函数 最小值估价
        {

                bool vv[maxm];
                int ret = 0, c, i, j;
                for (c = R[0];c != 0;c = R[c])vv[c] = 1;
                for(c=R[0];c!=0;c=R[c])
                        if (vv[c])
                        {
                                ret++, vv[c] = 0;
                                for (i = D[c];i != c;i = D[i])
                                        for (j = R[i];j != i;j = R[j])
                                                vv[Col[j]] = 0;
                        }
                return ret;
        }
        int fmax() //估价函数 最大值估价
        {
        bool vv[maxm];
        int ret = 0, c, i, j;
        for (c = R[0];c != 0;c = R[c])
            ret++;
        return ret;
        }
        void repeat_dance(int d)
        {
                if (d + f() >= ansd)return;
                if (R[0] == 0)
                {
                        if (d < ansd)ansd = d;
                        return;
                }
                int c = R[0], i, j;
                for (i = R[0];i;i = R[i])
                        if (S[i] < S[c])c = i;
                for (i = D[c];i != c;i = D[i])
                {
                        repeat_remove(i);
                        ans[d]=Row[i];
                        for (j = R[i];j != i;j = R[j])repeat_remove(j);
                        repeat_dance(d + 1);
                        for (j = L[i];j != i;j = L[j])repeat_resume(j);
                        repeat_resume(i);
                }
        }
        void out()
        {
        //cout<<ansd<<endl;
                int kinds, num;
                for (int i = 0;i < ansd;i++)
                {
                        kinds = (ans[i]-1) % 9+1;
                        num = (ans[i]-1) / 9+1;
                        cans[num] = kinds + '0';
                }
                //for(int i=1;i<=81;i++)if(cans[i]=='\0')puts("YES");
                //puts("");
                printf("%s\n", cans+1);
        }
}x;
///repeat代表重复覆盖，exact代表精确覆盖。
int main()
{
    char s[9 * 9 + 10];
        while (~scanf("%s",s+1))
        {
                if (s[1] == 'e')break;
                x.init(9 * 9 * 9, 324);
                int Size = strlen(s + 1);
                for (int i = 1;i <= Size;i++)
                {
                        int row = (i - 1) / 9 + 1;
                        int col = (i - 1) % 9 + 1;
                        int grid = ((row - 1) / 3) * 3 + (col - 1) / 3 + 1;
                        if (s[i] == '.')
                        {
                                for (int k = 1;k <= 9;k++)
                                {
                                        x.link((i - 1) * 9 + k, i);
                                        x.link((i - 1) * 9 + k, 81 + (row - 1) * 9+k);
                                        x.link((i - 1) * 9 + k, 81 * 2 + (col - 1) * 9+k);
                                        x.link((i - 1) * 9 + k, 81 * 3 + (grid - 1) * 9 + k);
                                }
                        }
                        else
                        {
                                int temp = s[i] - '0';
                                x.link((i - 1) * 9 + temp, i);
                                x.link((i - 1) * 9 + temp, 81+(row - 1) * 9 + temp);
                                x.link((i - 1) * 9 + temp, 81 * 2 + (col - 1) * 9 + temp);
                                x.link((i - 1) * 9 + temp, 81 * 3 + (grid - 1) * 9 + temp);
                        }
                }
                x.exact_dance(0);
                x.out();
        }
}
