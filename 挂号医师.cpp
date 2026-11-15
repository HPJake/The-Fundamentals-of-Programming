#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Doctor{
    int num;
    int patient;
};

bool cmp(Doctor a, Doctor b){
    return a.patient < b.patient;
}

int main(){
    int n;
    vector<Doctor> a;
    cin >> n;
    for (int i = 1; i <= n; i++){
        Doctor x;
        x.num = i;
        cin >> x.patient;
        a.push_back(x);
    }
    stable_sort(a.begin(), a.end(), cmp);
    cout << a[0].num;
    return 0;
}