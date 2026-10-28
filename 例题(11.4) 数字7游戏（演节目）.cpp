#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// C++³õÊ¼Ä£°å³ÌÐò

bool judge(int x){
	if (x % 7 == 0) return 1;
	while (x > 0){
		if (x % 10 == 7) return 1;
		else x /= 10;
	}
	return 0;
}

int main() {
	int n, cnt = 0;
	cin >> n;
	vector<int> stu;
	for (int i = 1; i <= n; i++){
		stu.push_back(i);
	}
	int i=1, j=0;
	while (cnt < n && stu.size() > 0){
		cout<<i<<' '<<stu[j]<<endl;
		int out;
	    if (judge(i)){
	        out = stu[j];
	        //cout<<"out "<<cnt<<' '<<out<<endl;
	        stu.erase(remove(stu.begin(), stu.end(), out), stu.end());
	        cnt++;
	    }
	    else{
	    	j++;
		}
	    i++;
		if (j >= stu.size()){
			j = 0;
		}
	}
	return 0;
}

