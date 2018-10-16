//牛顿迭代
//求F(x)=5x^3+4x^2+2
const double eps = 1e-6;
double F(double x){return 5*x*x*x + 4*x*x + 2;}
double F1(double x){return 15*x*x + 8*x;}       //F(x)的导函数
int newton(double x){                           //x是初始枚举值
    while(fabs(F(x)) > eps) x -= F(x)/F1(x);    //牛顿迭代
    return x;
}
//如果想求出一个范围内的所有的跟，则可以在该范围内枚举初始值x，来逼近根的值。
