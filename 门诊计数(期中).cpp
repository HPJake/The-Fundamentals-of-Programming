#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n, a[21], ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++){
		int x;
		cin >> x;
		a[i] = x - 60;
	}
	sort(a, a + n);
	int time, cnt = 0; //time: 看完后的时间 
	bool eight = true;
	for (int i = 0; i < n; i++){
		if (eight == true){
			if(a[i] <= 0) cnt++;
			else if (a[i] > 0){
				eight = false;
				time = cnt * 10;
				ans = cnt;
			}
		}
		if (eight == false){
			if (a[i] < time){
				time += 10;
				if (time >= 120) break;
				ans++;
			}
			else if (a[i] >= time){ //必须看完上一个才可以看下一个 
				time =a[i] + 10;
				if (time >= 120) break;
				ans++;
			}
		}
		//cout << a[i] << ' ' << time << ' ' << ans <<endl; (for debug)
	}
	cout << ans;
	return 0;
} 

/* Example
10
5
10
160
180
20
110
145
70
100
200
-55 0 0
-50 0 0
-40 0 0
310 40 4
40 50 5
50 60 6
85 95 7
100 110 8
8
*/
