//莫队模板
//len取sqrt(n)
int len;
struct Query
{
    int L,R,block;
    int idx;
    Query(int l,int r,int i):L(l),R(r),idx(i)
    {
        block=L/len;
    }
    Query(){}
    bool operator<(const Query &b)const
    {
        if(block!=b.block)return block<b.block;
        return R<b.R;
    }
};
Query q[maxm];
