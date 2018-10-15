//多重背包二进制优化
 for(i=0;i<n;i++){
        for(j=1;j<=a[i].num;j<<=1){ //分解为2^x
            value[tot]=j*a[i].v;
            weight[tot]=j*a[i].w;
            tot++;
            a[i].num-=j;
        }
        if(a[i].num>0){     //最后一项补齐
            value[tot]=a[i].num*a[i].v;
            weight[tot]=a[i].num*a[i].w;
            tot++;
        }
}
