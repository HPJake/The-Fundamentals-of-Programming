
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// 四个方向：上、右、下、左
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

// 返回连接两张卡片的最少线段数
// 无法连接时返回 -1
int bfs(const vector<string>& g, int w, int h,
        int x1, int y1, int x2, int y2) {

    // dist[y][x]：到达该位置至少需要多少条线段
    // -1 表示还没有到达过
    vector<vector<int>> dist(
        h + 2, vector<int>(w + 2, -1)
    );

    queue<pair<int, int>> q;

    // 起点不需要任何线段
    dist[y1][x1] = 0;
    q.push({x1, y1});

    while (!q.empty()) {

        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 如果到达终点
        if (x == x2 && y == y2) {
            return dist[y][x];
        }

        // 向四个方向尝试走直线
        for (int d = 0; d < 4; d++) {

            int nx = x + dx[d];
            int ny = y + dy[d];

            // 沿当前方向一直前进
            while (nx >= 0 && nx <= w + 1 &&
                   ny >= 0 && ny <= h + 1) {

                // 遇到其他卡片不能穿过
                // 但终点的卡片可以到达
                if (g[ny][nx] == 'X' &&
                    !(nx == x2 && ny == y2)) {
                    break;
                }

                // 如果这个位置还没有访问过
                if (dist[ny][nx] == -1) {

                    // 从当前点走一段直线到这里
                    dist[ny][nx] = dist[y][x] + 1;

                    q.push({nx, ny});
                }

                // 继续沿同一个方向前进
                nx += dx[d];
                ny += dy[d];
            }
        }
    }

    // BFS 结束仍然到不了终点
    return -1;
}

int main() {
    int w, h;
    int board = 0;

    // 可能有多组棋盘
    while (cin >> w >> h && (w != 0 || h != 0)) {

        board++;

        // 在棋盘外围额外增加一圈空格
        // 允许路径走出原来的棋盘
        vector<string> g(h + 2, string(w + 2, ' '));

        // 读取上一行残留的换行符
        string s;
        getline(cin, s);

        // 读取棋盘
        for (int y = 1; y <= h; y++) {
            getline(cin, s);

            // 不足宽度的部分视为空格
            while ((int)s.size() < w) {
                s += ' ';
            }

            for (int x = 1; x <= w; x++) {
                g[y][x] = s[x - 1];
            }
        }

        cout << "Board #" << board << ":" << endl;

        int x1, y1, x2, y2;
        int pairNum = 0;

        // 读取要连接的卡片对
        while (cin >> x1 >> y1 >> x2 >> y2) {

            // 四个 0 表示当前棋盘结束
            if (x1 == 0 && y1 == 0 &&
                x2 == 0 && y2 == 0) {
                break;
            }

            pairNum++;

            int ans = bfs(g, w, h, x1, y1, x2, y2);

            cout << "Pair " << pairNum << ": ";

            if (ans == -1) {
                cout << "impossible." << endl;
            } else {
                cout << ans << " segments." << endl;
            }
        }

        // 每个棋盘输出结束后空一行
        cout << endl;
    }

    return 0;
}
