//八数码问题
//hdu3567
//打表法
//我们可以发现，不管状态怎么变，它的下标仍然是从0到8，那么我们只要知道初始状态中//的值与它的下标对应关系，就可以将它变成表中的状态了，注意既然初始状态变了，那么最//终态也应该用同样的对应关系改变。
#include<iostream>  
#include<string>  
#include<queue>  
#include<vector>  
#include<cstring>  
using namespace std;  
int fact[10];  
void init2()  
{  
    fact[0] = 1;  
    for (int i = 1;i < 9;i++)  
        fact[i] = fact[i - 1] * i;  
}  
  
  
int kt(int s[], int n)  
{  
    int ans = 0;  
    int cnt = 0;  
    for (int i = 0;i < n;i++)  
    {  
        cnt = 0;  
        for (int j = i + 1;j < n;j++)  
            if (s[i] > s[j])cnt++;  
        ans += cnt*fact[n - i - 1];  
    }  
    return ans;  
}  
  
struct node  
{  
    int x, y;  
    int map[10];  
    int knum;  
    node(string s)  
    {  
        //memcpy(map, s, sizeof(map));  
        for (int i = 0;i < 9;i++)  
        {  
            if (s[i] == 'X')  
            {  
                map[i] = 0;  
                x = i / 3;  
                y = i % 3;  
            }  
            else  
            map[i] = s[i] - '0';  
        }  
        knum = kt(map, 9);  
    }  
    node(int s[], int _x, int _y, int _ktnum)  
    {  
        memcpy(map, s, sizeof(map));  
        x = _x;  
        y = _y;  
        knum = _ktnum;  
    }  
      
};  
const int maxn = 1e6 + 5;  
int fa[10][maxn];  
int ans[10][maxn];  
queue<node>Q;  
bool vis[maxn];  
int dir[4][2] = { 1,0,0,-1,0,1,-1,0 };  
  
char d[5] = "dlru";  
  
vector<char>V;  
  
void BFS(node a,int num)  
{  
    //while (!Q.empty())Q.pop();  
    memset(vis, 0, sizeof(vis));  
    vis[a.knum] = 1;  
    Q.push(a);  
    while (!Q.empty())  
    {  
        node u = Q.front();Q.pop();  
        int thex = u.x, they = u.y;  
        for (int i = 0;i < 4;i++)  
        {  
            int tempx = u.x + dir[i][0];  
            int tempy = u.y + dir[i][1];  
            if (tempx < 0 || tempx>2 || tempy < 0 || tempy>2)  
                continue;  
            int temp[10];  
            memcpy(temp, u.map, sizeof(u.map));  
            swap(temp[tempx * 3 + tempy], temp[u.x*3+u.y]);  
            int tmpkt = kt(temp, 9);  
            if (vis[tmpkt])continue;  
            fa[num][tmpkt] = u.knum;  
            vis[tmpkt] = 1;  
            ans[num][tmpkt] = i;  
            node v = node(temp, tempx, tempy, tmpkt);  
            Q.push(v);  
        }  
    }  
}  
  
void init()  
{  
    memset(fa, -1, sizeof(fa));  
    init2();  
    node a = node("X12345678");  
    BFS(a,0);  
    a = node("1X2345678");  
    BFS(a,1);  
    a = node("12X345678");  
    BFS(a,2);  
    a = node("123X45678");  
    BFS(a,3);  
    a = node("1234X5678");  
    BFS(a,4);  
    a = node("12345X678");  
    BFS(a, 5);  
    a = node("123456X78");  
    BFS(a, 6);  
    a = node("1234567X8");  
    BFS(a, 7);  
    a = node("12345678X");  
    BFS(a, 8);  
}  
int num[10];  
int bb[10];  
int main()  
{  
    init();  
    //freopen("D:\\input.txt", "r", stdin);  
    //freopen("D:\\1.txt", "w", stdout);  
    int T;  
    scanf("%d", &T);  
    int cas = 1;  
    while (T--)  
    {  
        string a, b;  
        cin >> a >> b;  
        memset(num, 0, sizeof(num));  
        memset(bb, 0, sizeof(bb));  
        int pos;  
        for (int i = 0, j=0;i < 9;i++)  
        {  
            if (a[i] == 'X')  
                pos = i;  
            else  
                num[a[i] - '0'] = j++;  
        }  
          
        for (int i = 0;i < 9;i++)  
        {  
            if (b[i] == 'X')continue;  
            b[i] = num[b[i] - '0'] + '1';  
            bb[i] = b[i] - '0';  
        }  
        V.clear();  
        int bkt = kt(bb, 9);  
        while (fa[pos][bkt]!=-1)  
        {  
            V.push_back(d[ans[pos][bkt]]);  
            bkt = fa[pos][bkt];  
        }  
        printf("Case %d: %d\n", cas++, V.size());  
        for(int i=V.size()-1;i>=0;i--)  
            printf("%c", V[i]);  
        printf("\n");  
    }  
    return 0;  
  
}  
