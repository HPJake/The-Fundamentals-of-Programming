#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
	vector<string> s;
	string line, word;
	getline(cin, line);
	stringstream ss(line);
	while (ss >> word){
		s.push_back(word);
	}
	bool first = true;
	for (int i = s.size() - 1; i >= 0; i--){
		if (!first) cout<<' ';
		cout<<s[i];
		first = false;
	}
	return 0;
}
