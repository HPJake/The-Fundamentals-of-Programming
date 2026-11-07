//vector去重、字符串变成全小写(引用传递)、 vector<pair<char, int>>自定义排序 

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
using namespace std;

bool cmp(pair<char, int> a, pair<char, int> b){
	return a.first < b.first;
}

int main(){
	string s;
	vector<pair<char, int>> a;
	cin >> s;
	for (char &c : s) c = tolower(c); //把字符串的每一个字符都改成小写，注意要引用传递(&c)，这样修改c就会修改s 
	for (auto x : s){
		if (!(x >= 'a' && x <= 'z')) continue;
		pair<char, int> y;
		y.first = tolower(x);
		y.second = s.find(x);
		a.push_back(y); //别不记得push_back() QAQ 
	}
	sort(a.begin(), a.end(), cmp);
	a.erase(unique(a.begin(), a.end()), a.end()); //vector去重, unique()返回一个迭代器（iterator），指向去重后有效区间的末尾
	for (auto z : a){
		cout << z.first << ' ' << z.second << endl;
	}
	return 0;
}

/*
#引用传递 
char c：复制字符，修改 c 不会影响原字符串。
char &c：引用原字符串中的字符，修改 c 就会修改 s。

#vector去重
sort()		排序，让相同元素相邻
unique()	将相邻重复元素移到有效区间之后，返回新逻辑结尾
erase()		真正删除多余元素，缩短 vector 
*/
