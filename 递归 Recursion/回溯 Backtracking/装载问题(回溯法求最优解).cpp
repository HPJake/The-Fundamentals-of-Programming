
#include <iostream>
#include <vector>
using namespace std;

int n, c1, c2, total = 0;
int best = 0;

// 使用 vector 代替固定长度数组
vector<int> w;
vector<int> chosen;
vector<int> bestChosen;

void dfs(int id, int sum) {

    // 第一艘船超载
    if (sum > c1) {
        return;
    }

    // 所有集装箱都已经考虑完毕
    if (id == n) {

        // 找到更优的装载方案
        if (sum > best) {
            best = sum;

            // 保存当前最优方案
            bestChosen = chosen; //vector支持直接使用 = 复制整个容器
        }

        return;
    }

    // 第一种选择：装进第一艘船
    chosen[id] = 1;
    dfs(id + 1, sum + w[id]);

    // 回溯：恢复当前选择状态
    chosen[id] = 0;

    // 第二种选择：留给第二艘船
    dfs(id + 1, sum);
}

int main() {
    cin >> n;

    // 根据实际输入的 n 分配空间
    w.resize(n);
    chosen.resize(n, 0); //后面的参数是初始值
    bestChosen.resize(n, 0);

    // 读取所有集装箱重量
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        total += w[i];
    }

    cin >> c1 >> c2;

    // DFS 寻找第一艘船的最大装载重量
    dfs(0, 0);

    // 判断剩余集装箱能否装进第二艘船
    if (total - best <= c2) {

        cout << "ok,can load it" << endl;
        cout << "a way is:" << endl;

        cout << "the first trip load:";
        bool first = true;

        for (int i = 0; i < n; i++) {
            if (bestChosen[i]) {
                if (!first) cout << ' ';
                cout << w[i];
                first = false;
            }
        }
        cout << endl;

        cout << "the second trip load:";
        first = true;

        for (int i = 0; i < n; i++) {
            if (!bestChosen[i]) {
                if (!first) cout << ' ';
                cout << w[i];
                first = false;
            }
        }
        cout << endl;
    }
    else {
        cout << "can't find a way to Loading" << endl;
    }

    return 0;
}
