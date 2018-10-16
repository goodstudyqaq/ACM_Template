//求C_i=\sum_{jxork=i}A\left[j\right]\astB\left[k\right]
//1代表变过去 -1变回来
//将A和B进行变换后相乘得到的结果进行逆变换即可。
void FWT(int a[],int n,int flag){
    for (int d=1;d<n;d<<=1)
        for (int i=0;i<n;i+=(d<<1))
            for (int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%mod;
                a[i+j+d]=(x-y)%mod;
                if (flag==-1){
                    a[i+j]=1LL*a[i+j]*inv2%mod;
                    a[i+j+d]=1LL*a[i+j+d]*inv2%mod;
                }
            }
}
