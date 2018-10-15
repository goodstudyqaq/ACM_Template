//笛卡尔树
/*
笛卡尔树是一种同时满足二叉搜索树和堆的性质的数据结构。可在一个数组上构造出来(时间复杂度可达到O(n))。树上节点有几个属性,key(节点元素的大小),index(节点在原数组中的索引),left(左子节点),right(右子节点),parent(父节点)。

性质
1.	树上的元素满足二叉搜索树性质，要求按照中序遍历得到的序列为原数组序列。
2.	树上节点满足堆性质，节点的key值要大于其左右子节点的key值
构造
	要求在给定的数组的基础上构造一棵笛卡尔树，这可以在O(n)的时间内完成。 其具体思路为：
	当按照index从1到n（或者从0到n-1）的顺序将数组中的每个元素插入到笛卡尔树中时，当前要被插入的元素的index值最大，因此根据二叉搜索的性质需要沿着当前已经完成的笛卡尔树的根的右子树链搜索。 
    由于笛卡尔树要满足堆的性质（以最大堆为例），父节点的key值要大于子节点的key值，所以沿着树根的右子树链往下走，直到搜索到的节点的key值小于等于当前要插入节点的key值。 
此时，便找到了当前结点需要插入的位置，记为P。此时P下方的节点的key值肯定小于当前被插入节点的key，但是index也小于当前插入节点的index（即需要在二叉搜索树中当前结点之前的位置），所以将当前节点插入到P的位置，同时将以P为根的子树挂载到新插入的节点的左子树（为了保证P及其子树在新插入节点之前被二叉搜索）。
实际实现的时候，可以采用栈的数据结构。栈中保存当前树中的从树根开始的右子节点链，根在栈底部。 
    插入新元素的时候，从树的右子链的最末尾从下往上查找，直到找到第一个满足堆性质的节点（即找到的节点的key值大于当前需要插入的节点）。用栈来实现就是从栈顶不断弹出元素，直到栈顶的元素的key大于当前结点的key，然后将该节点入栈，同时将最后被弹出的节点的parent指向该节点，以及该节点的左子节点指向最后被弹出的节点。
*/
//hdu6305
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const int mod=1e9+7;
int inv[maxn];
void invTable(int n, int p, int inv[]) {
    inv[1] = 1;
    for(int i = 2; i <= n; ++i)
        inv[i] = 1LL*(p-p/i) * inv[p%i] % p;
}
int n;
int stk[maxn],len;
struct node
{
    int l,r,p,v,id; //l r 左右孩子 p父亲 v权值 id标号
    void init()
    {
        l=r=p=v=id=0;
    }
}tree[maxn];
int build()
{
    //tree[0].init();
    len=1;
    stk[1]=1;
    for(int i=2;i<=n;i++)
    {
        while((len>0)&&(tree[stk[len]].v<tree[i].v))len--;
        if(len)
        {
            tree[i].p=stk[len];
            tree[tree[stk[len]].r].p=i;
            tree[i].l=tree[stk[len]].r;
            tree[stk[len]].r=i;
        }
        else
        {
            tree[stk[1]].p=i;
            tree[i].l=stk[1];
        }
        stk[++len]=i;
    }
    return stk[1];
}
int a[maxn];
int sz[maxn];
void dfs(int u)
{
    if(u==0)return;
    sz[u]=1;
    dfs(tree[u].l);
    dfs(tree[u].r);
    sz[u]+=sz[tree[u].l]+sz[tree[u].r];
}


int main()
{
    invTable(maxn-5,mod,inv);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            tree[i].init();
            tree[i].v=a[i];
            tree[i].id=i;
        }
        int root=build();
        dfs(root);
        long long ans=1LL*n*inv[2]%mod;
        for(int i=1;i<=n;i++)
            ans=(ans*inv[sz[i]])%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
