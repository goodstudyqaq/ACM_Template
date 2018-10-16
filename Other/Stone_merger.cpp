//石子合并
//n^2
//每次可以合并相邻两堆石子，代价为两堆石子的个数和。
/*
算法步骤:设序列为stone[],从左往右，找一个满足stone[k-1]<=stone[k+1]的k，找到后合并stone[k]和stone[k-1]，
再从当前位置开始向左找最大的j，使其满足stone[j]>stone[k]+stone[k-1],插到j的后面就行。一直重复，直到只剩下
一堆石子就可以了。在这个过程中，可以假设stone[-1]和stone[n]是正无穷的。
*/
int a[50003],n,i,t,ans;
void combine(int k)
{
    int tmp=a[k]+a[k-1],i,j;ans+=tmp;
    for(i=k;i<t-1;i++)a[i]=a[i+1];
    for(t--,j=k-1;j>0&&a[j-1]<tmp;j--)a[j]=a[j-1];
    a[j]=tmp;
    while(j>=2&&a[j]>=a[j-2])i=t-j,combine(j-1),j=t-i;
}
int main()
{
    while(1)
    {
        scanf("%d",&n);
        if(!n)return 0;
        for(i=ans=0;i<n;i++)scanf("%d",a+i);
        for(t=i=1;i<n;i++)
        {
            a[t++]=a[i];
            while(t>=3&&a[t-3]<=a[t-1])combine(t-2);
        }
        while(t>1)combine(t-1);
        printf("%d\n",ans);
    }
    return 0;
}
