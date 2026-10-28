#include <iostream>
#include <string>
using namespace std;

int a[27] = {0};

void count(string s){
	for (int i = 0; i < s.size(); i++){
		a[s[i] - 'A']++;
	}
}

int main(){
	string s[1005][3];
	int m;
	cin >> m;
	for (int i = 0; i < m; i++){
		for (int j = 0; j < 2; j++){
			cin >> s[i][j];
			if (j == 1) count(s[i][j]);
		}
	}
	int max= 0, max_i;
	for (int i = 0; i < 26; i++){
		if (a[i] > max){
			max = a[i];
			max_i = i;
		}
	}
	char author = (char)(max_i + 'A');
	cout << author << endl << max << endl;
	for (int i = 0; i < m; i++){
		if (s[i][1].find(author) != string::npos) cout<<s[i][0]<<endl;
	}
	return 0;
} 
