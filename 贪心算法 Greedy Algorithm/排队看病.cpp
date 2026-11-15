#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Patient{
    int id;
    int time;
};

bool cmp(Patient a, Patient b){
    return a.time < b.time;
}

int main(){
    int n;
    vector<Patient> a;
    cin >> n;
    for (int i = 0; i < n; i++){
        Patient x;
        x.id = i + 1;
        cin >> x.time;
        a.push_back(x);
    }
    stable_sort(a.begin(), a.end(), cmp);
    bool first = true;

    double avg_t, sum = 0;
    for (int i = 0; i < n; i++){
        if (!first) cout << ' ';
        cout << a[i].id ;
        first = false;
        sum += (n - i - 1) * a[i].time;
    }
    cout << endl;
    avg_t = sum / n;
    printf("%.2f", avg_t);
    return 0;
}