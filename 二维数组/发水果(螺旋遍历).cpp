#include <iostream>
using namespace std;

int main(){
    int n,m;
    cin >> n >> m;
    int a[15][15];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    bool visited[15][15] = {};
    
    //方向：下、右、上、左 -> 逆时针
    int dx[4] = {1, 0, -1, 0}; //行
    int dy[4] = {0, 1, 0, -1}; //列

    int x = 0, y = 0;
    int dir = 0;

    for (int i = 0; i < n * m; i++){
        if (i > 0) cout << ' ';
        cout << a[x][y]; //输出当前位置的学号
        visited[x][y] = true; //标记当前位置已经访问

        if (i == n * m - 1){
            break;
        }

        //计算下一个位置的下标
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        //如果下个位置不合法，就改变方向
        if (nx < 0 || nx >= n || ny < 0 || ny >= m || visited[nx][ny]){
            dir = (dir + 1) % 4; //循环遍历（循环下标）

            //转弯后重新计算下一位置
            nx = x + dx[dir];
            ny = y + dy[dir];
        }

        //移动到下一个位置
        x = nx;
        y = ny;
    }
    return 0;
}

/*
//方向：右、下、左、上 -> 顺时针
    int dx[4] = {0, 1, 0, -1}; //行
    int dy[4] = {1, 0, -1, 0}; //列
*/