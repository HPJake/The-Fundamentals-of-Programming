#include <iostream>
#include <string>
#include <cctype> //tolower(), toupper()
using namespace std;

char trans(char x){
	if (x >= 'a' && x<='z') return toupper(x);
	else if (x >= 'A' && x<= 'Z') return tolower(x);
	else return x;
}

int main(){
	string eml;
	//string s[1e4+1][3]; 这样写会出现[Error] size of array 's' has non-integral type 'double'，因为1e4是double类型，解决方法：直接写10001 或 用const
	const int MAXN = 1e4 + 1;
	string s[MAXN][3]; 
	int N;
	cin >> eml;
	cin >> N;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < 3; j++){
			cin >> s[i][j];
		}
	}
	bool empty = true;
	for (int i = 0; i < N; i++){
		if (s[i][2] == eml){
			empty = false;
			cout << s[i][0] << ' ';
			for (int l = 0; l < s[i][1].size(); l++){
				cout<< trans(s[i][1][l]);
			}
			cout << endl;
		}
	}
	if (empty) cout << "empty";
	return 0;
} 
