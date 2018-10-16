//三分。。
// 浮点求极大值
int find(int l, int r) {
    while (l < r - 1) {
        int m1 = l + r >> 1;
        int m2 = m1 + r >> 1;
        if (work(m1) > work(m2))
            r = m2;
        else
            l = m1;
    }
    return work(l) > work(r) ? l : r;
}
// 浮点求极小值
double find(double l, double r) {
    double m1, m2;
    while (r - l >= eps) {
        m1 = l + (r - l) / 3;
        m2 = r - (r - l) / 3;
        // m1 = l + r >> 1;
        // m2 = m1 + r >> 1;
        if (work(m1) > work(m2))
            l = m1;
        else
            r = m2;
    }
    return (m1 + m2) / 2;
}
