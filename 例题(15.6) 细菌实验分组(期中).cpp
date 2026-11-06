//忠告：看清楚题目，繁殖率不等于繁殖后的数量 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Sample { //结构体的定义 
    int num;       // 培养皿编号
    int before;    // 试验前细菌数量
    int after;     // 试验后细菌数量
    double rate;   // 繁殖率
};

// 按繁殖率升序排序
bool cmp(const Sample& a, const Sample& b) {
    return a.rate < b.rate;
}

int main() {
    int n;
    cin >> n;

    vector<Sample> a;

    // 1. 读取数据，同时计算繁殖率
    for (int i = 0; i < n; i++) {
        Sample x;
        cin >> x.num >> x.before >> x.after;

        // 必须转换成 double，避免整数除法
        x.rate = (double)x.after / x.before;

        a.push_back(x);
    }

    // 2. 按繁殖率从小到大排序
    sort(a.begin(), a.end(), cmp);

    // 3. 找到相邻繁殖率差最大的分界位置
    double max_diff = -1;
    int B_begin = 1;

    for (int i = 1; i < n; i++) {
        double diff = a[i].rate - a[i - 1].rate;

        if (diff > max_diff) {
            max_diff = diff;
            B_begin = i;
        }
    }

    // 4. 分组
    // B 亚种：繁殖能力弱，位于前面
    vector<Sample> B(
        a.begin(), a.begin() + B_begin // vector<type> v(a.begin(), a.begin() + n); 把vector a的前n - 1个元素复制到vector v; Note: 左边闭，右边开 [begin, end)  
    );

    // A 亚种：繁殖能力强，位于后面
    vector<Sample> A(
        a.begin() + B_begin, a.end()
    );

    // 5. 按照题目要求输出
    cout << A.size() << endl;
    for (Sample y : A) {
        cout << y.num << endl;
    }

    cout << B.size() << endl;
    for (Sample z : B) {
        cout << z.num << endl;
    }

    return 0;
}

