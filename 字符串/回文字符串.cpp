#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

int main(){
    string line;
    while (getline(cin, line)){
        string s = "";
        for (auto c : line){
            if (isalpha(c)) s += c;
        }
        string r = s;
        reverse(r.begin(), r.end());
        if (r == s){
            cout << "true" << endl;
        }
        else cout << "false" << endl;
    }
    return 0;
}