#include <iostream>
#include <cmath>
using namespace std;

int digit_sum(int x){
	int sum = 0;
	while (x > 0){
		sum += x % 10;
		x /= 10;
	}
	return sum;
}

int main(){
	int m, n, k;
	scanf("%d,%d,%d", &m, &n, &k);
	int d = (int)log10(n) + 1;
	int t = 1;
	while (t <= 9*d){
		bool first = true;
		for (int i = m; i < n; i++){
			if (digit_sum(i) == k * t){
				if (!first) cout<<',';
				cout<<i;
				first = false;
			}
		}
		t++;
		if (!first) cout<<endl;
	}
	return 0;
}
