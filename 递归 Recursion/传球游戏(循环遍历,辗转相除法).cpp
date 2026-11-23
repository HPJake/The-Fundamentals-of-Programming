//题目：N个人围成一圈玩传球游戏。开始时，第一个人拿着球。每个人把球传给左手的第K个人，其中，1 <= K <= N/2。计算最大的K，使得第一个人重新拿到球之前，每个人都拿过球。
//解法：找gcd，详细解析见相关文档
//辗转相除法找gcd可通过循环或递归实现
#include <iostream>
using namespace std;

//辗转相除法求gcd by 递归
int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main(){
    int n, k = 0;
    cin >> n;
    for (int i = 1; i <= n / 2; i++){ //直接倒序遍历更好
        if (gcd(n, i) == 1){ //若n,k互质则符合条件
            k = i;
        }
    }
    cout << k;
    return 0;
}