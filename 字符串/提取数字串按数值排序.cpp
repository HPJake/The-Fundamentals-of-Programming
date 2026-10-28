#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main(){
	string line, word;
	getline(cin, line);
	vector<int> a;
	bool num = false;
	for (int i = 0; i < line.size(); i++){
		if (line[i] < 48 || line[i] > 57){
			line[i] = ' ';
		}
		else num = true;
	}
	if (!num){
		cout << 0;
		return 0;
	}
	stringstream ss(line);
	while (ss >> word){
		a.push_back(stoi(word));
	}
	sort(a.begin(),a.end());
	bool first = true;
	for (int i = 0; i < a.size(); i++){
		if (!first) cout<<',';
		cout<<a[i];
		first = false;
	}
	return 0;
}

