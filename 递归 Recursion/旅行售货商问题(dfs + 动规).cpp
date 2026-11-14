
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 15;
const int INF = 1000000000;

int n;
int cost[N][N];

// dp[mask][current]：
// 已访问的城市集合为 mask，当前位于 current，
// 访问完剩余城市并回到起点的最小费用
int dp[1 << N][N];

// DFS 返回完成剩余旅程的最小费用
int dfs(int current, int mask) {

    // 1. 终止条件：所有城市都访问过
    if (mask == (1 << n) - 1) {
        // 最后还需要飞回起点城市 0
        return cost[current][0];
    }

    // 2. 如果之前计算过，直接返回答案
    if (dp[mask][current] != -1) {
        return dp[mask][current];
    }

    int ans = INF;

    // 3. 枚举下一座城市
    for (int i = 0; i < n; i++) {

        // 判断城市 i 是否尚未访问
        if ((mask & (1 << i)) == 0) {

            // 将城市 i 标记为已访问
            int nextMask = mask | (1 << i);

            // 飞到 i 的费用 + 后续旅程的最小费用
            int total = cost[current][i]
                      + dfs(i, nextMask);

            // 选择费用最小的路线
            ans = min(ans, total);
        }
    }

    // 4. 记住这个状态的最优答案
    dp[mask][current] = ans;

    return ans;
}

int main() {
    cin >> n;

    // 输入机票价格矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    // -1 表示这个状态还没有计算过
    memset(dp, -1, sizeof(dp));

    // 固定从城市 0 出发
    // mask = 1 表示城市 0 已经访问过
    cout << dfs(0, 1) << endl;

    return 0;
}
