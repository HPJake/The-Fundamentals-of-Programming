//Version II: <cctype> + toupper
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main(){
	string s, out = "";
	while (cin >> s){
		int cnt = 0;
		for (int i = 1; i <= s.size(); i++){
			string letter;
			if (s[i-1] >= 'a') letter = toupper(s[i-1]);
			else letter = s[i-1];
			if (toupper(s[i]) == toupper(s[i - 1])){
				cnt++;
			}
			else{
				out += '(' + letter + ',' + to_string(cnt + 1) +')';
				cnt = 0;
			}
		}
	cout << out << endl;
	out = "";
	}
	return 0;
}
