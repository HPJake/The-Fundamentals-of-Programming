#include <iostream>
#include <string>
#include <vector>
using namespace std;

void check(string s){
	if (s.size() < 6){
		cout << "Not safe" << endl;
		return;
	}
	vector<int> type = {0, 0, 0, 0}; //四个位代表四个种类 
	for (char c : s){
		if (c >= '0' && c <= '9') type[0]++;
		else if (c >= 'a' && c <= 'z') type[1]++; //一定要用else if, 不然最后一个else只会限于上一个if 
		else if (c >= 'A' && c <= 'Z') type[2]++;
		else type[3]++;
	}
	int cnt = 0;
	for (int x : type){
		if (x > 0) cnt++;
	}
	//cout << cnt << endl;
	if (cnt == 1) cout << "Not safe" << endl;
	else if (cnt == 2) cout << "Medium safe" << endl;
	else if (cnt > 2) cout << "Safe" << endl;
	return;
}

int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string password;
		cin >> password;
		check(password);
	}
	return 0;
} 
