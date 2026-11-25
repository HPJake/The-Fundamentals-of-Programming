//排列型dfs, 和八皇后问题相似，每一层都有多个候选对象，通过for循环枚举，再利用标记数组避免冲突
//本题亦可以通过next_permutation()轻松实现
#include <iostream>
#include <string>
using namespace std;

string s;
string path;
int n;
bool used[6] = {};

void dfs(int depth){ //depth表示已经确定了多少个字符，和选或不选型dfs中id的概念不一样
    if (depth == n){
        cout << path<< endl;
        return;
    }

    //枚举当前位置可以选择的字符
    for (int i = 0; i < n; i++){
        if (!used[i]){
            //做出选择
            used[i] = true;
            path.push_back(s[i]);

            //递归确定下一个位置
            dfs(depth + 1);

            //回溯：撤销刚才的选择
            path.pop_back();
            used[i] = false;
        }
    }
}

int main(){
    cin >> s;
    n = s.size();
    dfs(0);
    return 0;
}