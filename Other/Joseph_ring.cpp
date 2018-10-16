#include<iostream>
using namespace std;
///推导公式方法
int yuesefu(int n,int m){
        if(n == 1){
                return 0; //这里返回下标,从0开始，只有一个元素就是剩余的元素0
        }
        else{
                return (yuesefu(n-1,m) + m) % n; //我们传入的n是总共多少个数
        }
}
int main(void){
 
        int a=41,b=3;
        //递归求最后一个存活的编号
        //使用从正向思考
        cout<<"最后一个人是"<<yuesefu(a,b)+1<<endl;
        //反向思考，从自杀的最后一人向前
        int result = 2;
        //第一个自杀的人3号
        cout<<3;
        //每次自杀的都是2号，但是不同的2号换算到最初序号所需的的次数是不同的
        //外循环是循环不同的换算次数
        for(int i = a; i >= 2 ; i-- )
        {
            result = 2;
            //内循环是开始换算
            for(int j = i; j <= a; j++)
            {
                result = (result+b) %j;
            }
               cout<<"->"<<result+1;//0开始变1开始，所以加1
        }
        return 0;
}
