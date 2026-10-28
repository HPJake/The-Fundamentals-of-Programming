#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
	string line, word;
	vector<string> s;
	getline(cin, line);
	stringstream ss(line);
	while (ss >> word){
		s.push_back(word);
	}
	s[s.size() - 1].pop_back(); //str.pop_back() -> 去除字符串最后一个字符 
	int max = 0, max_i;
	for (int i = 0; i < s.size(); i++){
		int len;
		//if (i = s.size() - 1) len = s[i].length() - 1; (直接把最后一个字符串的最后一个字符'.'去掉则无需判断)
		//s是vector, s.size()是vector的元素个数，s[i]是字符串，s[i].size()是string的长度 
		len = s[i].length();
		if (len > max){
			max = len;
			max_i = i;
		}
	}
	cout<<s[max_i];
	return 0;
} 
