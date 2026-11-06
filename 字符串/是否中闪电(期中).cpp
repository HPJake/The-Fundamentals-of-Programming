#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
	string s, x;
	vector<string> a;
	getline(cin, s);
	stringstream ss(s);
	while (ss >> x){
		a.push_back(x);
	}
	if (a[0] == "heitao" && a[1] >= "2" && a[1] <= "9") cout << "yes";
	return 0;
}
