#include <iostream>
#include <utility>
using namespace std;

int a[1001][1001];

int main() {
	int n;
	pair <int, int> LU, RL; //左上角、右下角坐标
	cin >> n;
	bool found_1 = false;
	for (int i = 0; i < n; i++){
	    for (int j = 0; j < n; j++){
	        cin >> a[i][j];
	        if (a[i][j] == 0 && found_1 == false){
	            LU.first = i; LU.second = j;
	            found_1 = true;
	        }
	    }
	}
	bool found_2 = false;
	for (int i = n - 1; i >= 0; i--){
	    for (int j = n - 1; j >= 0; j--){
	        if (a[i][j] == 0 && found_2 == false){
	            RL.first = i; RL.second = j;
	            //break; 这样写的话，最终 RL = {1,3} , 因break只能中止一次循环！！！ 
	            found_2 = true;
	        }
	    }
	}
	cout << (RL.first - LU.first - 1) * (RL.second - LU.second - 1);
	return 0;
}

/* 也可以这么写 
if (x == 0) {
    LU.first = min(LU.first, i);
    LU.second = min(LU.second, j);

    RL.first = max(RL.first, i);
    RL.second = max(RL.second, j);
}
*/
