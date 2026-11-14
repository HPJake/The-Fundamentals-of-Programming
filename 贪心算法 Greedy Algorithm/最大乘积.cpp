#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v;

    // 第一步：从 2 开始选择不同的整数
    for (int i = 2; n >= i; i++) {
        v.push_back(i);
        n -= i;
    }

    // 第二步：从右往左分配剩余的数
    for (int i = (int)v.size() - 1; i >= 0 && n > 0; i--) {
        v[i]++;
        n--;
    }

    // 第三步：如果还有剩余，加给最后一个数
    if (n > 0) {
        v.back() += n;
    }

    // 第四步：输出
    for (int i = 0; i < (int)v.size(); i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }

    return 0;
}