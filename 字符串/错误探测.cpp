#include <iostream>
using namespace std;

/* 
思路: 在方阵右侧多加一列，表示该行1的个数；在下边多加一行，表示该列1的个数（be like 行列式的行/列变换）
4 (把4*4方阵扩大一阶)
1 0 1 0 2
0 0 1 0 1
1 1 1 1 4
0 1 0 1 2
2 2 3 2 0
*/

int main(){
	int n = 1;
	while (n != 0){
		int a[101][101] = {0};
		cin >> n;
		if (n == 0) break;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				cin >> a[i][j];
				a[i][n] += a[i][j];
				a[n][j] += a[i][j];
			}
		}
		int cnt_R = 0, cnt_C = 0, p = 0, q = 0; //p,q用来记录有错误的行，列（最后一个） 
		for (int i = 0; i < n; i++){ //看附加的侧边列（1的个数） -> indicate每一行1的个数 
		 	if (a[i][n] % 2 != 0){
		 		cnt_R++;
		 		p = i + 1; //记录有错误的行（只计最后一个有错误的行，不过不影响判断） 
			}
		}
		for (int j = 0; j < n; j++){
			if (a[n][j] % 2 != 0){
				cnt_C++; //-> indicate每一列1的个数
				q = j + 1;  //记录有错误的列 
			}
		}
		if (cnt_R == 0 && cnt_C == 0) cout << "OK" <<endl;
		else if (cnt_R == cnt_C && cnt_R == 1){
			cout << "Change bit (" << p << ',' << q << ")" << endl;
		}
		else cout << "Corrupt" << endl;
	}
	return 0;
}
