//Version I: 得到输出的对应下标vector，之后按下标输出
#include <iostream>
#include <vector>
#include <utility> //pari
using namespace std;

int main(){
	vector<pair<int, int>> index; //用pair储存二元数据 e.g.坐标 
	int a[101][101];
	int r, c; //i：行，j：列
	cin >> r >> c;
	
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			cin >> a[i][j];
		}
	}
	
	int i = 0, j = 0, n = r * c;
	int r1 = 0, c1 = 0;
	while (index.size() < n){
		while (j < c){
			index.push_back({i,j});
			j++;
		}
		if (index.size() == n) break;
		//此时 j = c; i = 0;
		j = c - 1;
		c--;
		i++;
		while (i < r){
			index.push_back({i,j});
			i++;
		}
		if (index.size() == n) break; // index.size() < n 只在每轮外层循环开始时判断一次。
		//此时 j = c - 1; i = r;
		i = r - 1;
		r--;
		j--;
		while (j >= c1){
			index.push_back({i,j});
			j--;
		}
		if (index.size() == n) break;
		//此时 j = c1 - 1; i = r-1;
		j = c1;
		c1++;
		i--;
		while (i > r1){
			index.push_back({i,j});
			i--;
		}
		//此时 i = r1;
		if (index.size() == n) break;
		i = r1 + 1;
		r1++; 
		j++;
	}
	//cout << index.size() <<' ' << r * c << endl;
	for (int i = 0; i < index.size(); i++){
		cout<<a[index[i].first][index[i].second]<<endl;
	}
	return 0;
} 
