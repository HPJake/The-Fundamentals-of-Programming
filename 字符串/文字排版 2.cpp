#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    string word, output = "";
    cin >> n;
    bool first = true;
    for (int i = 0; i < n; i++){ //知道输入次数可以不用getline, 可以避免换行符没被读取的问题
        if (!first) output += " ";
        first = false;
        cin >> word;
        string x = output;
        x += word;
        if (x.length() > 80){
            output.pop_back();
            cout << output << endl;
            output = word + " ";
            first = true;
        }
        else if (i == n-1){
            output += word;
            cout << output;
        }
        else{
            output = x;
        }
    }
    return 0;
}