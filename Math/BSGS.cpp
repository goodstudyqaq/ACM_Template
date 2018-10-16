/*==================================================*\
| Baby-Step-Giant-Step 大步小步算法
| 求 a^x === b (mod p) 中的 x值 -- 此处p仅为素数
| 实际运用中用自己的hash表代替map可防TLE
\*==================================================*/
LL BSGS(LL a, LL b, LL p) {
    a %= p; b %= p;
    map<LL, LL> h;
    LL m = ceil(sqrt(p)), x, y, d, t = 1, v = 1;
    for(LL i = 0; i < m; ++i) {
        if(h.count(t)) h[t] = min(h[t], i);
        else h[t] = i;
        t = (t*a) % p;
    }
    for(LL i = 0; i < m; ++i) {
        d = extgcd(v, p, x, y);
        x = (x* b/d % p + p) % (p);
        if(h.count(x)) return i*m + h[x];
        v = (v*t) % p;
    }
    return -1;
}
