//求连续和

//一维最大连续和(最大连续子区间)
//dp[i]代表以i结尾的最大连续和
/***********************************/
//二维(最大子矩阵和)
//转化为一维即可。
for(i=0; i<n; i++){
    memset(arr,0,sizeof(arr));
    for(j=i; j<n; j++){
        for(k=0; k<n; k++)
            arr[k] += dp[j][k];
        maxsubarr = maxsub(arr,n);
        if(maxsubarr > maxsubrec) maxsubrec = maxsubarr;
    }
}
/***********************************/
//三维最大子矩阵和
long long ans = -INF;
	for (int c = 1; c <= A; c++) {
		for (int i = 1; i <= B; i++) {
			for (int j = i; j <= B; j++) {
				for (int k = 1; k <= C; k++) {
					long long h = 0;
					for (int l = k; l <= C; l++) {
						h += g[c][j][l];//g为原矩阵的值
						sum[i][j][k][l] = sum[i][j - 1][k][l] + h;
						if (c == 1) res[i][j][k][l] = sum[i][j][k][l];
						else 
res[i][j][k][l] = max(sum[i][j][k][l], res[i][j][k][l] + sum[i][j][k][l]);
						ans = max(ans, res[i][j][k][l]);
					}
				}
			}
		}
	}
	return ans;
