//不知数据组数的输入 
#include <iostream>
#include <cmath>
using namespace std;

int main(){
	//vector<pair<double, double>> d; 其实不用那么麻烦喵 
	double x = 0, y = 0, dx, dy;
	// 每次读取两个浮点数
	// 直到输入结束（EOF），本地终端测试时，输入"EOF"结束输入 
	while (cin >> dx >> dy){
		x += dx;
		y += dy;
	}
	double disp = sqrt(x * x + y * y);
	printf("%.4f", disp);
	return 0;
} 
