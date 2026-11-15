//Japan 2004 Domestic
#include <iostream>
#include <cstring> //用memset将数组清零
using namespace std;

int W, H;
int ans = 0;
char maze[25][25] = {0};
bool visited[25][25] = {false};

void dfs(int x, int y){ //x: 行(范围: 0~H)，y: 列(范围：0~W) 千万别搞反
    if (maze[x][y] == '#' || x < 0 || y < 0 || x >= H || y >= W || visited[x][y] == true) return;
    //不能写 maze[x][y] != '.', 这样会把起点'@'也排除掉的！！！

    visited[x][y] = true;
    ans++;

    dfs(x - 1, y); //上
    dfs(x, y - 1); //左
    dfs(x + 1, y); //下
    dfs(x, y + 1); //右
}

int main(){
    
    while (cin >> W >> H){
        if (W == 0 && H == 0) break;

        int start_x, start_y;
        memset(maze, 0, sizeof(maze)); //memset(起始地址, 填充值, 字节数量);
        memset(visited, 0, sizeof(visited));
        ans = 0;

        for (int i = 0; i < H; i++){
            for (int j = 0; j < W; j++){
                cin >> maze[i][j];
                if (maze[i][j] == '@'){
                    start_x = i;
                    start_y = j;
                }
            }
        }
        dfs(start_x, start_y);
        cout << ans << endl;
    }
    return 0;
}

/*关于memset
memset() 不能用于把普通整数数组的每个元素任意设置成 1、2、3 等数值。
因为 memset(a, 1, ...) 是把每个字节设置成 01（十六进制）。

如果要把每个整数都设为 1，建议使用：
int a[5];
fill(a, a + 5, 1); //需调用<aglorithm>
*/