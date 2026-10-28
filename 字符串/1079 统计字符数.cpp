#include <iostream>
#include <string>
using namespace std;

int main(){
	int n;
	string s = "";
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> s;
		int a[27] = {0};
		for (int j = 0; j < s.length(); j++){
			a[s[j]-'a' + 1]++;
		}
		int max = 0, max_i=0;
		for (int k = 1; k <= 26; k++){
			if (a[k] > max){
				max = a[k];
				max_i = k;
			}
		}
		cout<<char(max_i - 1 + 'a')<<' '<<max<<endl;
	}
	return 0;
}
