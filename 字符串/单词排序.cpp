#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	string line, word;
	vector<string> s;
	getline(cin, line);
	stringstream ss(line);
	while (ss >> word){
		s.push_back(word);
	}
	sort(s.begin(), s.end());
	s.erase(unique(s.begin(), s.end()), s.end()); //vector去重, unique()把重复元素移道尾部，然后返回一个去重后有效范围的尾后迭代器it 
	for (int i = 0; i < s.size(); i++){
		cout<<s[i]<<endl;
	} 
	return 0;
}
