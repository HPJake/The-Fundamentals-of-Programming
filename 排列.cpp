#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool arith(vector<int> a){
	 if (a.size() <= 2) return true; //只有一个或是两个元素 -> 等差数列，不然到一行就会出现访问越界 
	int D = a[1] - a[0]; //公差，如果只有一个或两个元素，会出现访问越界;
	int d = D; //两项之差 
	for (int i = 1; i < a.size(); i++){
		d = a[i] - a[i - 1];
		if (d != D) return false;
	}
	return true;
}

int main(){
	int T;
	cin >> T;
	for (int i = 0; i < T; i++){
		vector<int> a;
		int n, ans = 0; cin >> n;
		for (int j = 0; j < n; j++){
			int x; cin >> x;
			a.push_back(x);
		}
		for (int k = 1; k < n; k++){ //k不能从0开始，当k=0时，left数组截取到空vector 
			vector<int> left(a.begin(), a.begin() + k);
			vector<int> right(a.begin() + k, a.end());
			sort(left.begin(), left.end());
			sort(right.begin(), right.end());
			if (arith(left) && arith(right)) ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
