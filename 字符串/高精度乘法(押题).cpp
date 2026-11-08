
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // 使用字符数组读取两个超大整数
    // 这里假设每个整数最多 1000 位
    char sa[1005], sb[1005];
    cin >> sa >> sb;

    // 倒序存储两个乘数
    int a[1005] = {0};
    int b[1005] = {0};

    // 结果最多 2000 位，留出额外空间
    int c[2010] = {0};

    int n = strlen(sa);
    int m = strlen(sb);

    // 1. 将字符数组转成 int 数组
    // 个位放在下标 0
    for (int i = 0; i < n; i++) {
        a[i] = sa[n - 1 - i] - '0';
    }

    for (int i = 0; i < m; i++) {
        b[i] = sb[m - 1 - i] - '0';
    }

    // 2. 逐位相乘，累加到对应的位置
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] += a[i] * b[j];
        }
    }

    // 3. 统一处理进位
    for (int i = 0; i < n + m; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    // 4. 找到结果的最高非零位
    int len = n + m;

    while (len > 1 && c[len - 1] == 0) {
        len--;
    }

    // 5. 从最高位向最低位输出
    for (int i = len - 1; i >= 0; i--) {
        cout << c[i];
    }

    cout << '\n';

    return 0;
}

