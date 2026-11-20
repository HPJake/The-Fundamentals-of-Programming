#include <iostream>
#include <vector>
using namespace std;

int N, n;

// 棋盘：-1 表示空，0 表示黑棋，1 表示白棋
vector<vector<int>> board;

// 四个方向：水平、竖直、主对角线、次对角线
int dx[4] = {1, 0, 1, 1};
int dy[4] = {0, 1, 1, -1};

// 判断刚落下的棋子是否形成五子连珠
bool check(int x, int y, int player) {

    // 枚举四个方向
    for (int d = 0; d < 4; d++) {

        int cnt = 1; // 当前落下的棋子也算一颗

        // 沿当前方向的正反两侧检查
        for (int sign = -1; sign <= 1; sign += 2) {

            // 每一侧最多检查 4 格
            for (int step = 1; step <= 4; step++) {

                int nx = x + sign * step * dx[d];
                int ny = y + sign * step * dy[d];

                // 超出棋盘范围
                if (nx < 0 || nx >= N ||
                    ny < 0 || ny >= N) {
                    break;
                }

                // 不是同一方的棋子，连续性中断
                if (board[ny][nx] != player) {
                    break;
                }

                // 找到一颗连续的同色棋子
                cnt++;
            }
        }

        // 形成至少五颗连续同色棋子
        if (cnt >= 5) {
            return true;
        }
    }

    // 四个方向都没有形成五子连珠
    return false;
}

int main() {
    cin >> N >> n;

    // 初始化棋盘，全部为空
    board.assign(N, vector<int>(N, -1));

    // 按输入顺序模拟落子
    for (int i = 0; i < n; i++) {

        int x, y;
        cin >> x >> y;

        // 黑棋先手：0 黑棋，1 白棋
        int player = i % 2;

        // 在 (x, y) 位置落子
        // 注意：二维数组先行(y)，后列(x)
        board[y][x] = player;

        // 判断当前落子后是否获胜
        if (check(x, y, player)) {

            // i 从 0 开始，实际步数从 1 开始
            cout << i + 1 << " " << player << endl;

            // 题目只需要第一次出现胜利的时刻
            break;
        }
    }

    return 0;
}