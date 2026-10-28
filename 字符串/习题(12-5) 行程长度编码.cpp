//Version I: 利用ASCII码 ('X' = char('x' - ('a' - 'A'));) 
#include <iostream>
#include <string>
using namespace std;

//思路：考虑ASCII码，'a'：97, 'A':67
//'X' = char('x' - ('a' - 'A'));
//Remark: 有点复杂 ,可用 <cctype> + toupper

int main(){
	string s, out = "";
	while (cin >> s){
		int cnt = 0;
		for (int i = 1; i <= s.size(); i++){
			string letter;
			if (s[i-1] >= 'a') letter = char(s[i-1] - ('a' - 'A'));
			else letter = s[i-1];
			if (s[i] == s[i-1] || s[i] + 'a' - 'A' == s[i-1] || s[i] == s[i-1] + 'a' - 'A'){
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
