//值得学习的地方：找到一个目标后，继续找下一个目标，用target[pos]实现
//贪心算法/贪心扫描：每找到一个需要的字母，就尽早确定这一列，继续寻找下一个字母。 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
	int t, pos = 0;
	string target = "vika"; //target[pos]对应当前正在寻找的字符 
	cin >> t;
	for (int i = 0; i < t; i++){
		int n, m;
		cin >> n >> m;
		vector<string> s(n);
		pos = 0;
		for (int j = 0; j < n; j++){
			cin >> s[j];
		}
		for (int k = 0; k < m; k++){
			for (int l = 0; l < n; l++){
				if (s[l][k] == target[pos]){
					pos++; //注意，当找到最后一个字符'a'的时候，pos依旧会+1, 所以全部找到 <=> pos == 4 
					break;
				}
			}
		}
		if (pos == 4) cout << "YES" << endl; //注意，当找到最后一个字符'a'的时候，pos依旧会+1, 所以全部找到 <=> pos == 4 
		else cout << "NO" << endl;
	}
}

/*
pos	当前要找的字母
0	v
1	i
2	k
3	a
4	全部找到
*/
