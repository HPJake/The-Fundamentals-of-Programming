#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
	string line, word;
	getline(cin, line);
	stringstream ss(line);
	bool first = true;
	while (ss >> word){
		if (!first) cout<<' ';
		cout<<word;
		first = false;
	}
	return 0;
} 
