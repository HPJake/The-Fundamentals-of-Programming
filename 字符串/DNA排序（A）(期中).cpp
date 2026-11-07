#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

int m, n;

int inv_pair(string s){
	int cnt = 0;
	for (int i = 0; i < m; i++){
		for (int j = i + 1; j < m; j++){
			if (s[i] > s[j]) cnt++;
		}
	}
	return cnt;
}

bool cmp(const pair<int, string> &a, const pair<int, string> &b){
	return a.first < b.first; //就算两项逆序对数一样，sort函数也只会比较seq.first，不会比较seq.second 
}

int main(){
	//string s[51];
	vector<pair<int, string>> seq;
	cin >> m >> n;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		pair<int, string> x; //就算把逆序对数摆到first的位置，也要自定义cmp()比较函数进行排序 
		x.second = s;
		x.first = inv_pair(s);
		seq.push_back(x);
	}
	stable_sort(seq.begin(), seq.end(), cmp);
	for (auto y : seq){
		cout << y.second << endl;
	}
	return 0;
}

/*一个Wrong Anwser的Case: 
问题在于逆序对个数一样时，本应该不改变顺序，但是程序输出却按字典序排好了。这是因为sort函数会默认先按p.first排序，如果p.first一样，就按照p.second排序
解决方法：自定义排序，写cmp()比较函数 
Different: Different at line 2.
Std: 'C'
Out: 'A'

Input of in case 3:
1 5
A
C
G
T
A

Standard Output:
...

Your Output:
A
A
C
G
T
*/
