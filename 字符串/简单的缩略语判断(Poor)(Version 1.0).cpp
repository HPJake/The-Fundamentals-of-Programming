//Version: 1.0 这一版无法再编程网格上AC, VS Code能实现效果，但是网格不行, 但是这期很有教育意义
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main(){
    int n, pos = -1;
    cin >> n;
    cin.ignore(); // 忽略换行符, cin和getline混用时一定要注意！！！！！！！！！！
    for (int i = 0; i < n; i++){
        pos = -1;
        string a, b;
        getline(cin, a, ':');
        getline(cin, b);
        bool abbr = true;
        for (char &c : a){
            if (b.find(c) != string::npos){
                //if (b.find(c) > pos){ //坑点：不可以写if (b.find(c) > pos), 因为str.find()返回的是size_t(无符号整数)类型, 而pos是int类型, 可能会出现负数和正数比较的情况, 导致逻辑错误
                if (static_cast<int>(b.find(c)) > pos){ //坑点：不可以写if (b.find(c) > pos), 因为str.find()返回的是size_t(无符号整数)类型, 而pos是int类型, 可能会出现负数和正数比较的情况, 导致逻辑错误
                    pos = b.find(c);
                    abbr = true;
                    b.replace(pos, 1, " ");
                }
                else {
                    abbr = false;
                    break;
                }
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