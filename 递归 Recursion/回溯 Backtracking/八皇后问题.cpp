#include <iostream>
using namespace std;

//一列一列地放皇后
int pos[9]; //皇后所在的行

bool usedRow[9]; //标记已经放过皇后的行 (下标：列)

bool diag1[17] = {}; //主斜线 "\"
bool diag2[17] = {}; //次斜线 "/"

int num; //解法编号

void printsol(){
    cout << ++num << endl; //++i, 先加再输出
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (pos[j] == i) cout << '*';
            else cout << '.';
            if (j < 8) cout << ' ';
        }
        cout << endl;
    }
}

void queen(int col){
    if (col == 9){
        printsol();
        return;
    }

    //尝试把当前皇后放在每一行
    for (int row = 1; row <= 8; row++){
        //计算斜线编号
        int d1 = row - col + 8; //对于同一条 \ 方向的斜线，行号减列号相同。
        int d2 = row + col; //对于同一条 / 方向的斜线，行号加列号相同。
        
        //如果行或斜线被占用，跳过
        if (usedRow[row] || diag1[d1] || diag2[d2]){
            continue;
        }

        //放置皇后
        pos[col] = row;
        //标记所在行、主次斜线
        usedRow[row] = true;
        diag1[d1] = true;
        diag2[d2] = true;

        //处理下一列
        queen(col + 1);

        //回溯，撤销本次选择
        //无条件回溯，当下一项递归的函数return后，就会接着执行下面的回溯操作
        usedRow[row] = false;
        diag1[d1] = false;
        diag2[d2] = false;
    }
}

int main(){
    queen(1); //从第一列开始放置
    return 0;
}