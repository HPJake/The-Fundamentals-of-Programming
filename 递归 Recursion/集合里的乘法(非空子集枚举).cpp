//非空子集枚举问题, 选或不选型DFS
//这题和“最佳凑单”很像，但是要处理非空的问题
#include <iostream>
#include <vector>
using namespace std;

int n, t;
vector<int> s;
bool ans = false;

void dfs(int id, int product, bool chosen){ //chosen = true -> 子集非空
    if (id == n){ // id范围0 ~ n-1, 当id为n时说明走完了
        //cout << product << endl;
        if (chosen && product == t){ //and 不是 or
            ans = true;
        }
        return;
    }

    if (ans) return; //找到一个满足条件的自己就可以return了

    //分叉
    dfs(id + 1, product * s[id], true); //选; 注意是'*',不是'*='; 选了元素，则chosen为true，子集非空
    dfs(id + 1, product, chosen); //不选，不改变chosen的状态
}

int main(){
    cin >> t >> n;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        s.push_back(x);
    }
   dfs(0, 1, false); //开始的时候子集为空
   if (ans) cout << "YES";
   else cout << "NO";
   return 0;
}