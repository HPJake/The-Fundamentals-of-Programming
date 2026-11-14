#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Interval{
	int l;
	int r;
};

bool cmp(Interval a, Interval b){
	return a.l < b.l;
} 

int main(){
	vector<Interval> a;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		Interval x;
		cin >> x.l >> x.r;
		a.push_back(x);
	}
	sort(a.begin(), a.end(), cmp);
	
	int l = a[0].l, r = a[0].r;
	
	for (auto y : a){
		if (y.l > r){ //如左端点大于上一项的右端点(e.g. [1,2],[4,5])那么存在空隙 
			cout << "no" ;
			return 0;
		} 
		r = max(y.r, r); //合并区间：如果没有空隙，右端点为下一项的右端点，或不变(包含关系 e.g. [2,3]包含于[1,5]) 
	}
	cout << l << ' ' << r;
	return 0;
} 
