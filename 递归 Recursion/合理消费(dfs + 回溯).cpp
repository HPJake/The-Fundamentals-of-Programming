//深搜 + 回溯
#include <iostream>
#include <vector>  
using namespace std;

int n;
vector<int> price;
vector<int> path;
bool found = false;

void dfs(int p, int start){
    if (p == 0){
        bool first = true;
        found = true;
        for (auto x : path){
            if (!first) cout << " ";
            first = false;
            cout << x;
        }
        cout << endl;
        return;
    }
    for (int i = start; i < n; i++){
        if (price[i] <= p){
            path.push_back(price[i]);
            dfs(p - price[i], i);
            path.pop_back();
        }
    }
}

int main(){
    int p;
    cin >> n >> p;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        price.push_back(x);
    }
    dfs(p, 0);
    if (!found) cout << "NO" << endl;
    return 0;
}