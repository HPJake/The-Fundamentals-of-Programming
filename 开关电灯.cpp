#include <iostream>
using namespace std;

int a[1005] = {0};

void rev(int x){
	if (a[x] == 0) a[x] = 1;
	else if (a[x] == 1) a[x] = 0;
}

int main(){
	int N;
	cin >> N;
	for (int i = 2; i <= N; i++){ //第一个人将全部灯熄灭 
		for (int j = 1; j <= N; j++){
			if (j % i == 0) rev(j); //注意：rev(j)而不是i, 一定要小心,不要搞混i,j 
		}
	}
	//bool first = true;
	for (int i = 1; i <= N; i++){
		if (a[i] == 1){
			//if (!first) cout << ' ';
			cout << i << ' '; //这题居然是，每个输出数字后带一个空格 
			//first = false;
		}
	}
	return 0;
}
