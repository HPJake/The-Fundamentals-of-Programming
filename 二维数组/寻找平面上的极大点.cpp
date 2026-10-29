#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(){
	vector<pair<int, int>> a, max;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		//cin >> a[i].first >> a[i].second; 大错特错！vector一开始是没有数据的，用下标访问是错误的！！！ 
		int x, y;
		cin >> x >> y;
		a.push_back({x,y});
	}
	for (int i = 0; i < n; i++){
		bool dom = true;
		for (int j = 0; j < n; j++){
			if (i == j) continue;
			if (a[i].first <= a[j].first && a[i].second <= a[j].second) dom = false; 
		}
		if (dom) max.push_back(a[i]);
	}
	sort(max.begin(),max.end()); //直接使用sort，默认按pair.first从小到大排序，其他情况需要自定义cmp函数，见最下方 
	//sort(max.begin(),max.end(),cmp) 自定义时候，sort后面写 cmp !!! 不是 cmp()!!! 
	bool first = true;
	for (auto p : max){ //重要：遍历vector max里面的每个元素（暂存于p） 
		if (!first) cout << ',';
		cout << '(' << p.first << ',' << p.second <<')';
		first = false;
	}
	return 0;
}

/* 
bool cmp(pair<int,int> a, pair<int,int> b) { //这里就不要写auto了 
    return a.first > b.first; //从大到小 
}
sort(v.begin(),v.end(),cmp) //不是cmp()!!! 
*/
