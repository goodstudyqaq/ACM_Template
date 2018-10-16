struct LB
{
    int d[31];
    int cnt,mx;
    LB()
    {
        memset(d,0,sizeof(d));
        cnt=0,mx=31;
    }
    void init(){memset(d,0,sizeof(d));}
    bool add(int val)
    {
        for(int i=mx-1;i>=0;i--)
        {
            if(val&(1<<i))
            {
                if(!d[i])
                {
                    d[i]=val;break;
                }
                val^=d[i];
            }
        }
        return val>0;
    }
    int querymx_xor(int num=0)
    {
        int ret=num;
        for(int i=mx-1;i>=0;i--)if((ret^d[i])>ret)ret^=d[i];
        return ret;
    }
    LB operator+(const LB&_A)const
    {
        LB ret=*this;
        for(int i=mx-1;i>=0;i--)if(_A.d[i])ret.add(_A.d[i]);
        return ret;
}
/*重新构造以便求异或和第k小
    */
    int p[31],cnt;
    void rebuild()
    {
        for(int i=mx-1;i>=0;i--)
            for(int j=i-1;j>=0;j--)
            if(d[i]&(1<<j))
                d[i]^=d[j];
        for(int i=0;i<mx;i++)
            if(d[i])
            p[cnt++]=d[i];
    }
    int kthquery(int k)
    {
        int ret=0;
        if(k>=(1<<cnt))return -1;
        for(int i=mx-1;i>=0;i--)
            if(k&(1<<i))ret^=p[i];
        return ret;
    }
};
