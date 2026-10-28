#include <iostream>
#include <string>
using namespace std;

int main(){
	string s, s1, s2;
	getline(cin, s, ','); //读取直到遇到逗号',', string无法scanf格式化读取 
	getline(cin, s1, ',');
	getline(cin, s2);
	int x1 = s.find(s1) + s1.size() - 1;
	int x2 = s.rfind(s2);
	//int d = x2 - x1; 
	if (x1 == -1 || x2 == -1) cout<<-1;
	else if (x1 > x2 || x1 - x2 == 0){
		cout<<-1;
	}
	else cout<<x2 - x1;
	return 0;
}
