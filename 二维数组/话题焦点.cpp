#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int N = 0, user[101] = {0};
	vector<int> v[10001];
	vector<int> ment;
	cin >> N;
	for (int i = 0; i < N; i++){
		int a,k;
		cin >> a >> k;
		v[i].push_back(a);
		if (k == 0) continue;
		for (int j = 0; j < k; j++){
			int b; cin >> b;
			v[i].push_back(b);
			user[b]++;
		}
	}
	int max = 0, max_i;
	for (int i = 0; i < 100; i++){
		if (user[i] > max){
			max = user[i];
			max_i = i;
		}
	}
	cout << max_i << endl;
	for (int i = 0; i < N; i++){
		for (int j = 1; j < v[i].size(); j++){
			if (v[i][j] == max_i){
				ment.push_back(v[i][0]);
			}
		}
	}
	sort(ment.begin(), ment.end());
	bool first = true;
	ment.erase(unique(ment.begin(), ment.end()), ment.end());
	for (auto x : ment){
		if (!first) cout << ' ';
		cout << x;
		first = false;
	}
	return 0;
}
