//Version 2.0 AC
//子序列匹配(Subsequence Matching):过维护一个不断向前移动的位置，保证元素按照指定顺序匹配。
#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符, cin和getline混用时一定要注意！！！！！！！！！！
    for (int i = 0; i < n; i++){
        size_t pos = 0;
        string a, b;
        getline(cin, a, ':');
        getline(cin, b);
        bool abbr = true;

        if (a.length() >= b.length()) {
            abbr = false;
        }

        for (char c : a){
            size_t found = b.find(c, pos); //size_t: 无符号整数
            if (found != string::npos){
                //if (b.find(c) > pos){ //坑点：不可以写if (b.find(c) > pos), 因为str.find()返回的是size_t(无符号整数)类型, 而pos是int类型, 可能会出现负数和正数比较的情况, 导致逻辑错误
                pos = found + 1;
            }
            else{
                abbr = false;
                break;
            }
        }
        if (abbr) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}