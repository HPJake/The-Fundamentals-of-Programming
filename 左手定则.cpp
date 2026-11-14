
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n, m;

    // 题目有多组测试数据
    // 一直读取，直到输入结束
    while (cin >> n >> m) {

        if (n == 0 && m == 0) break;

        // 存储迷宫
        vector<string> maze(n);

        // 记录起点坐标
        int x = -1, y = -1;

        // 读取迷宫
        for (int i = 0; i < n; i++) {
            cin >> maze[i];

            for (int j = 0; j < m; j++) {
                if (maze[i][j] == 'S') {
                    x = i;
                    y = j;
                }
            }
        }

        // 读取初始朝向：N、S、W、E
        char direction;
        cin >> direction;

        // 用 0、1、2、3 表示四个方向
        // 0：北 N
        // 1：东 E
        // 2：南 S
        // 3：西 W

        int dir = 0;

        if (direction == 'N') dir = 0;
        else if (direction == 'E') dir = 1;
        else if (direction == 'S') dir = 2;
        else if (direction == 'W') dir = 3;

        // 四个方向对应的坐标变化
        // 顺序：北、东、南、西
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};

        // visited[x][y][dir] 表示：
        // 是否曾经在 (x,y) 位置面朝 dir 方向
        bool visited[105][105][4] = {};

        // 是否成功找到宝藏
        bool found = false;

        // 开始模拟人物移动
        while (true) {

            // 1. 判断是否到达宝藏
            if (maze[x][y] == 'T') {
                found = true;
                break;
            }

            // 2. 如果相同状态以前出现过
            // 说明已经进入循环，无法到达宝藏
            if (visited[x][y][dir]) {
                break;
            }

            // 标记当前状态已经访问
            visited[x][y][dir] = true;

            // 3. 计算移动方向的优先级
            int nextDir[4];

            nextDir[0] = (dir + 3) % 4; // 左转
            nextDir[1] = dir;           // 直行
            nextDir[2] = (dir + 1) % 4; // 右转
            nextDir[3] = (dir + 2) % 4; // 掉头

            bool moved = false;

            // 4. 按照优先级尝试四个方向
            for (int i = 0; i < 4; i++) {

                int d = nextDir[i];

                // 计算下一位置
                int nx = x + dx[d];
                int ny = y + dy[d];

                // 判断是否越界
                if (nx < 0 || nx >= n ||
                    ny < 0 || ny >= m) {
                    continue;
                }

                // 判断是否遇到墙
                if (maze[nx][ny] == '#') {
                    continue;
                }

                // 找到可以走的方向
                x = nx;
                y = ny;

                // 移动后面朝新的方向
                dir = d;

                moved = true;

                // 按照左手定则，只走优先级最高的方向
                break;
            }

            // 如果四个方向都不能移动，就停止
            if (!moved) {
                break;
            }
        }

        // 5. 输出结果
        if (found) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
