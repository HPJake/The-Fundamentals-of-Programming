//子集枚举问题, 选或不选型DFS
#include <iostream>
#include <vector>
#include <climits> //提供INT_MAX
using namespace std;

int n, t, min_s = INT_MAX;
vector<int> p;

void dfs(int id, int sum){
    if (id == n){ // id范围0 ~ n-1, 当id为n时说明走完了
        if (sum >= t){
        min_s = min(sum, min_s);
        }
        return;
    }
    //分叉
    dfs(id + 1, sum + p[id]); //购买
    dfs(id + 1, sum); //不买
}

int main(){
    cin >> n >> t;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        p.push_back(x);
    }
   dfs(0, 0);
   if (min_s < INT_MAX) cout << min_s;
   else cout << 0;
   return 0;
}