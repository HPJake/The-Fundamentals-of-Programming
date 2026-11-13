#include <iostream>
using namespace std;

int dfs(int n, int i){
    int product = 1;
    if (n == 1) return product;
    for (int i = 1; i <=n; i++){
        dfs(n - i, i);
    }
}

int main(){
    return 0;
}