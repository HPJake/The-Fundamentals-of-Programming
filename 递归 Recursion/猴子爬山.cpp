#include <iostream>
using namespace std;

int m, ans;

void climb(int step){
    if (step == m){
        ans++;
        return;
    }

    if (step > m){
        return;
    }

    climb(step + 1);
    climb(step + 3);
    climb(step + 5);
}

int main(){
    cin >> m;
    climb(0);
    cout << ans;
    return 0;
}