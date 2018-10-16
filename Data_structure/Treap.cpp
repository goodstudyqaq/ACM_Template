//给定一个无向图，操作1: D X,把第X条边删掉，边的序号为输入顺序。操作 2:Q X k询问所有和X联通的点中，权值第k大的值。操作3:C X V将节点X的权值改为V 碰到E就结束操作。
#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0),cin.tie(0)
#define M(a,b) memset(a,b,sizeof(a))
using namespace std;

const int MAXN=20007;
const int oo=0x3f3f3f3f;
typedef long long LL;
const LL loo=4223372036854775807ll;
typedef long double LB;
const LL mod=1e9+7;

//名次树
struct Node
{
    Node *ch[2];//左右儿子
    int rank;//随机优先级
    int val;//值
    int s;//孩子总数

    Node(int v) { val=v;rank=rand();s=1;ch[0]=ch[1]=NULL; }
    int cmp(int x) const
    {
        if(x==val) return -1;
        else return (x<val) ? 0 : 1;
    }
    void maintain()
    {
        s=1;
        if(ch[0]!=NULL) s+=ch[0]->s;
        if(ch[1]!=NULL) s+=ch[1]->s;
    }
};
Node* treaproot[MAXN];

void rotate(Node* &o, int d)//d=0代表左旋，d=1代表右旋
{
    Node* k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
    o->maintain();k->maintain();
    o=k;
}
int find(Node* o, int x)//在Treapo中查找x
{
    while(o!=NULL)
    {
        int d=o->cmp(x);
        if(d==-1) return 1;
        else o=o->ch[d];
    }
    return 0;
}
void insert(Node* &o, int x)//在Treapo中插入key=x的元素
{
    if(o==NULL) { o=new Node(x); }
    else
    {
        int d=(x<o->val ? 0 : 1);
        insert(o->ch[d], x);
        if(o->ch[d]->rank>o->rank) rotate(o, d^1);
    }
    o->maintain();
}
void remove(Node* &o, int x)//在Treapo中移除key为x的元素
{
    int d=o->cmp(x);
    if(d==-1)
    {
        Node* u=o;
        if(o->ch[1]==NULL)
        {
            o=o->ch[0];
            delete u;
        }
        else if(o->ch[0]==NULL)
        {
            o=o->ch[1];
            delete u;
        }
        else
        {
            int d2=(o->ch[0]->rank>o->ch[1]->rank ? 1 : 0);
            rotate(o, d2);remove(o->ch[d2], x);
        }
    }
    else
    {
        remove(o->ch[d], x);
    }
    if(o!=NULL) o->maintain();
}
void release(Node* &o)//释放整颗Treap
{
    if(o->ch[0]!=NULL) release(o->ch[0]);
    if(o->ch[1]!=NULL) release(o->ch[1]);
    delete o;
    o=NULL;
}
void merge(Node* &a, Node* &b)
{
    if(b->ch[0]!=NULL) merge(a, b->ch[0]);
    if(b->ch[1]!=NULL) merge(a, b->ch[1]);
    insert(a, b->val);
    delete b;b=NULL;
}
int find_Kth(Node* o, int k)
{
    if(o==NULL||k<=0||k>o->s) return 0;
    else
    {
        Node* now=o;
        while(1)
        {
            int rson=(now->ch[1]==NULL ? 0 : now->ch[1]->s);
            if(k==rson+1) { return now->val; }
            else if(k<=rson)
            {
                now=now->ch[1];
            }
            else
            {
                now=now->ch[0];
                k=k-rson-1;
            }
        }
    }
}
//名次树

//并查集
int fa[MAXN];
int get_fa(int a)
{
    return a==fa[a] ? a : fa[a]=get_fa(fa[a]);
}
//并查集

int op;
int operate[500010][3];//操作指令序列
int querycnt=0;
LL querysum=0;
vector<int> G[MAXN];
int val[MAXN];
struct Edge
{
    int from, to, removed;
    Edge() {}
    Edge(int _a, int _b, int _c) { from=_a;to=_b;removed=_c; }
};
vector<Edge> edge;
void init()//初始化整个
{
    for(int i=0;i<MAXN;i++) G[i].clear();
    edge.clear();
    querycnt=querysum=op=0;
}
void add_edge(int i)
{
    int from=edge[i].from, to=edge[i].to;
    int fathera=get_fa(from);
    int fatherb=get_fa(to);
    if(fathera==fatherb) return;
    if(treaproot[fathera]->s>treaproot[fatherb]->s)
    {
        fa[fatherb]=fathera;
        merge(treaproot[fathera], treaproot[fatherb]);
    }
    else
    {
        fa[fathera]=fatherb;
        merge(treaproot[fatherb], treaproot[fathera]);
    }
}

void query(int x, int k)
{
    int fatherx=get_fa(x);
    querycnt++;
    querysum+=find_Kth(treaproot[fatherx], k);
}
void change_weight(int a, int b)
{
    int fa=get_fa(a);
    remove(treaproot[fa], val[a]);
    insert(treaproot[fa], b);
    val[a]=b;
}
int main()
{
    _;
    int n;
    int kase=0;
    while(scanf("%d", &n))
    {
        init();
        int m;scanf("%d", &m);
        if(n==0) break;
        for(int i=1;i<=n;i++) scanf("%d", &(val[i]));
        for(int i=0;i<m;i++)
        {
            int ta, tb;scanf("%d%d", &ta, &tb);
            edge.push_back(Edge(ta, tb, 0));
        }

        while(1)
        {
            char type;scanf(" %c", &type);
            if(type=='E') break;
            if(type=='D')
            {
                int typed;scanf("%d", &typed);
                edge[typed-1].removed=1;
                operate[op][0]='D'-'A';
                operate[op++][1]=typed;
            }
            if(type=='Q')
            {
                int ta, tb;scanf("%d%d", &ta, &tb);
                operate[op][0]='Q'-'A';
                operate[op][1]=ta;operate[op++][2]=tb;
            }
            if(type=='C')
            {
                int ta, tb;scanf("%d%d", &ta, &tb);
                operate[op][0]='C'-'A';
                operate[op][2]=val[ta];
                val[ta]=tb;
                operate[op++][1]=ta;
            }
        }

        for(int i=1;i<=n;i++)
        {
            fa[i]=i;
            if(treaproot[i]!=NULL) release(treaproot[i]);
            insert(treaproot[i], val[i]);
        }
        for(int i=0;i<m;i++)
        {
            if(!edge[i].removed)
                add_edge(i);
        }
        for(int i=op-1;i>=0;i--)
        {
            if(operate[i][0]+'A'=='Q')
            {
                query(operate[i][1], operate[i][2]);
            }
            if(operate[i][0]+'A'=='C')
            {
                change_weight(operate[i][1], operate[i][2]);
            }
            if(operate[i][0]+'A'=='D')
            {
                add_edge(operate[i][1]-1);
            }
        }

        printf("Case %d: %.6lf\n", ++kase, querysum/(double)querycnt);
    }

    return 0;
}
