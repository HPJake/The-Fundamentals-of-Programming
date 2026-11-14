//这题其实和区间再现的思路是一样的
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start;
    int end;
};

bool cmp(Activity a, Activity b) {
    return a.end < b.end;
}

int main(){
    int n;
    cin >> n;
    vector<Activity> v(n);
    for (int i = 0; i < n; i++){
        cin >> v[i].start >> v[i].end;
    }
    sort(v.begin(), v.end(), cmp);

    int ans = 0, lastend = -1;
    for (int i = 0; i < n; i++){
        if (v[i].start >= lastend){
            ans++;
            lastend = v[i].end;
        }
    }
    cout << ans << endl;
    return 0;
}