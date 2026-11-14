
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    while (n--) {
        int k;
        string a, b;

        cin >> k >> a >> b;

        // 1. 去掉整数部分和小数点
        // 例如 "0.1011" 变成 "1011"
        a = a.substr(a.find('.') + 1);
        b = b.substr(b.find('.') + 1);

        // 2. 将两个小数补齐到相同长度
        int len = max(a.size(), b.size());

        a.resize(len, '0');
        b.resize(len, '0');

        // 3. 保存计算结果
        string ans(len, '0');

        // carry 表示进位
        int carry = 0;

        // 4. 从右往左逐位相加
        for (int i = len - 1; i >= 0; i--) {

            // 字符转成数字，再加上进位
            int sum = (a[i] - '0') + (b[i] - '0') + carry;

            // 当前位应该保留的数字
            ans[i] = (sum % k) + '0';

            // 计算向前一位的进位
            carry = sum / k;
        }

        // 5. 删除小数部分末尾多余的 0
        while (!ans.empty() && ans.back() == '0') {
            ans.pop_back();
        }

        // 6. 输出整数部分和小数部分
        // 因为两个输入都小于 1，所以整数部分只有 0 或 1
        cout << carry << "." << ans << endl;
    }

    return 0;
}
