//cdq分治
//四维偏序
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long ll;
const int MAXN = 50002;

int n;

struct Item {
    int d1,d2,d3,d4,part; // 分别表示每一维的数据，part为第一维重标号之后的值
}a[MAXN];
const int LEFT = 0;
const int RIGHT = 1;

namespace BIT { // 树状数组相关
    int arr[MAXN];
    inline int lowbit( int num ) { return num&(-num); }
    void add( int idx ) {
        for( ; idx <= n; idx += lowbit(idx) ) arr[idx]++;
    }
    int query( int idx ) {
        int ans = 0;
        for( ; idx; idx -= lowbit(idx) ) ans += arr[idx];
        return ans;
    }
    void clear( int idx ) {
        for( ; idx <= n; idx += lowbit(idx) ) arr[idx] = 0;
    }
}

ll ans = 0;

Item tmp3d[MAXN];
Item tmp2d[MAXN];
void cdq3d( int L, int R ) { // 对第二维分治，按照第三维合并
    if( R-L <= 1 ) return;
    int M = (L+R)>>1; cdq3d(L,M); cdq3d(M,R);
    int p = L, q = M, o = L;
    while( p < M && q < R ) { // 因为第二维是“左边全都是L，右边全都是R”，所以略去第二维的标号
        if( tmp2d[p].d3 < tmp2d[q].d3 ) {
            if( tmp2d[p].part == LEFT ) BIT::add( tmp2d[p].d4 );
            tmp3d[o++] = tmp2d[p++];
        } else {
            if( tmp2d[q].part == RIGHT ) ans += BIT::query( tmp2d[q].d4 );
            tmp3d[o++] = tmp2d[q++];
        }
    }
    while( p < M ) tmp3d[o++] = tmp2d[p++];
    while( q < R ) {
        if( tmp2d[q].part == RIGHT ) ans += BIT::query( tmp2d[q].d4 );
        tmp3d[o++] = tmp2d[q++];
    }
    for( int i = L; i < R; ++i ) { // 清空树状数组
        if( tmp3d[i].part == LEFT ) BIT::clear( tmp3d[i].d4 );
        tmp2d[i] = tmp3d[i];
    }
}
void cdq2d( int L, int R ) { // 对第一维分治，按照第二维合并
    if( R-L <= 1 ) return;
    int M = (L+R)>>1; cdq2d(L,M); cdq2d(M,R);
    int p = L, q = M, o = L;
    while( p < M && q < R ) {
        if( a[p].d2 < a[q].d2 ) {
            a[p].part = LEFT; // 重标号
            tmp2d[o++] = a[p++];
        } else {
            a[q].part = RIGHT;
            tmp2d[o++] = a[q++];
        }
    }
    while( p < M ) {
        a[p].part = LEFT;
        tmp2d[o++] = a[p++];
    }
    while( q < R ) {
        a[q].part = RIGHT;
        tmp2d[o++] = a[q++];
    }
    for( int i = L; i < R; ++i ) a[i] = tmp2d[i]; // tmp2d为“复制的那一份”
    cdq3d(L,R);
}

int main() {
    freopen( "partial_order.in", "r", stdin );
    freopen( "partial_order.out", "w", stdout );
    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) {
        a[i].d1 = i;
        scanf( "%d", &a[i].d2 );
    }
    for( int i = 0; i < n; ++i ) scanf( "%d", &a[i].d3 );
    for( int i = 0; i < n; ++i ) scanf( "%d", &a[i].d4 );
    cdq2d(0,n); printf( "%lld\n", ans );
    return 0;
}
