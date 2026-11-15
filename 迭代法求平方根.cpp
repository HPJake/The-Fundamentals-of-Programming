
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a;
    cin >> a;

    // 按照题目要求，初始值为 1
    double x = 1.0;

    while (true) {
        // 根据公式计算下一次近似值
        double next = 0.5 * (x + a / x);

        // 判断连续两次结果是否足够接近
        if (fabs(next - x) <= 1e-5) {
            x = next;
            break;
        }

        // 更新近似值，继续下一轮计算
        x = next;
    }

    // 保留 7 位小数
    cout << fixed << setprecision(7) << x << endl;

    return 0;
}
