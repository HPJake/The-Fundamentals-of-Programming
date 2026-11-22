#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;  // 测试数据组数

    while (n--) {
        int year;
        cin >> year;

        // 从下一年开始逐年枚举
        for (int i = year + 1; i <= 9999; i++) {

            // 提取年份的四个数字
            int a = i / 1000;        // 千位
            int b = i / 100 % 10;    // 百位
            int c = i / 10 % 10;     // 十位
            int d = i % 10;         // 个位

            // 判断四个数字是否两两不同
            if (a != b && a != c && a != d &&
                b != c && b != d &&
                c != d) {

                cout << i << endl;

                // 找到的第一个就是最小的
                break;
            }
        }
    }

    return 0;
}
