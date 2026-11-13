#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void prime_fact(int n, vector<int> &v){ //分解质因数, 建议记住
    if (n == 1) return;
    for (int i = 2; i <= n; i++){ //从2开始找最小的质因数
        if (n % i == 0){
            v.push_back(i);
            prime_fact(n / i, v); //递归调用，继续分解n/i
            return;
        }
    }
}

int main(){
    int a, b;
    scanf("%d,%d", &a, &b);
    vector<int> af, bf;
    prime_fact(a, af);
    prime_fact(b, bf);
    af.erase(unique(af.begin(), af.end()), af.end());
    bf.erase(unique(bf.begin(), bf.end()), bf.end());
    if (af == bf) printf("YES\n");
    else printf("NO\n");
    return 0;
}