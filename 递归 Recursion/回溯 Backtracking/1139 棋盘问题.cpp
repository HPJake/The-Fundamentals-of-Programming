//选与不选型 + 八皇后式回溯
#include <iostream>
using namespace std;

int n, k, ans;
int usedCol[10];
char board[10][10];

void dfs(int row, int placed){
    if (placed == k){
        ans++;
        return;
    }
    if (row == n) return;

    //第一种选择：不放
    dfs(row + 1, placed);

    //第二种选择：放
    for (int col = 0; col < n; col++){
        if (board[row][col] != '#' || usedCol[col]) continue;
        
        usedCol[col] = true;
        dfs(row + 1, placed + 1); //放

        //回溯：撤销选择
        usedCol[col] = false;
    }
}

int main(){
    while (cin >> n >> k && n != -1 && k != -1){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> board[i][j];
            }
        }
        dfs(0,0);
        cout << ans << endl;
        ans = 0; //ans需要reset
        //但是board数组不需要，因为每个递归层都遵循：修改状态 -> 递归 -> 回溯
    }
    return 0;
}