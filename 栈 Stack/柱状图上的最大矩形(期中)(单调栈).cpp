#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main(){
	int n;
	cin >> n;
	
	vector <int> h(n + 1, 0);
	for (int i = 0; i < n; i++) cin >> h[i];
	
	stack<int> st;
	int ans = 0;
	for (int i = 0; i <= n; i++){
		while (!st.empty() && h[i] <= h[st.top()]){
			int height = h[st.top()];
			st.pop();
			int left = -1;
			if (!st.empty()){
				left = st.top();
			}
			int width = i - left - 1;
			int area = height * width;
			ans = max(ans,area);
		}
		st.push(i);
	}
	cout << ans << endl;
	return 0;
}
