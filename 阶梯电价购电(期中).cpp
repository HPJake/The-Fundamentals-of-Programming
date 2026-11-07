#include <iostream>
using namespace std;

int main(){
	double m, d;
	cin >> m;
	if (m <= 240 * 0.4883){
		d = m / 0.4883;
	}
	else if (m > 240 * 0.4883 && m <= 240 * 0.4883 + 160 * 0.5383){
		d = (m - 240 * 0.4883) / 0.5383 + 240;
	}
	else if (m > 240 * 0.4883 + 160 * 0.5383){
		d = (m - 240 * 0.4883 - 160 * 0.5383) / 0.7883 + 240 + 160;
	}
	printf("%.2f", d);
	return 0;
} 
