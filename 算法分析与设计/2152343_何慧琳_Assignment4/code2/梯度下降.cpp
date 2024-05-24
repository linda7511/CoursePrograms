/*
伪代码：
选择初始点 (𝑥1, 𝑥2)
设置学习率 𝛼
设置收敛条件
初始化迭代次数 𝑛 = 0

重复迭代直到收敛：
    计算梯度 ∇𝑓 = [∂𝑓/∂𝑥1, ∂𝑓/∂𝑥2] 在当前位置 (𝑥1, 𝑥2)
    更新位置：(𝑥1, 𝑥2) = (𝑥1, 𝑥2) - 𝛼 * ∇𝑓
    增加迭代次数 𝑛 = 𝑛 + 1

输出最小值点 (𝑥1, 𝑥2)
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

//计算函数在p点的梯度向量
std::vector<double> gredient(vector<double>p)
{
    return { exp(p[0] + 3 * p[1] - 0.1) + exp(p[0] - 3 * p[1] - 0.1) - exp(-p[0] - 0.1) ,3 * exp(p[0] + 3 * p[1] - 0.1) - 3 * exp(p[0] - 3 * p[1] - 0.1) };
}



int main()
{
    double x1 = 0, x2=0 ,x1_=x1,x2_=x2;//设置初始点
    double t = 1e-5,n=1e-10;//设置学习率和收敛条件
    bool convergent = false;
    while (!convergent) {
        vector<double> grad = gredient({ x1,x2 });
        x1_ = x1 - t * grad[0];
        x2_ = x2 - t * grad[1];
        if (abs(x1_ - x1) < n && abs(x2_ - x2) < n)//判断是否收敛
            convergent = true;
        else {
            x1 = x1_;
            x2 = x2_;
        }
    }
    cout << "f_min:" << fixed << setprecision(10) << exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) + exp(-x1 - 0.1) << endl;
    cout << "(x1*,x2*):(" << fixed << setprecision(10)<< x1 << "," << fixed << setprecision(10) << x2 << ")" << endl;

    return 0;
}