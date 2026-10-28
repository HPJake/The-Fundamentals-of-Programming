#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    string groups[8] = {
        "ABC", "DEF", "GHI", "JKL",
        "MNO", "PRS", "TUV", "WXY"
    };

    for (int i = 0; i < n; i++) {
        string s, ans = "";
        cin >> s;

        for (char c : s) { //依次取出字符串 s 中的每一个字符，并赋值给变量 c (vector也可以这样操作) 
            // 数字直接保留
            if (c >= '0' && c <= '9') {
                ans += c;
            }
            // 字母转换成对应数字
            else if (c >= 'A' && c <= 'Z') {
                for (int j = 0; j < 8; j++) {
                    if (groups[j].find(c) != string::npos) {  
                        ans += char('2' + j); //将group下标转换为数字字符 e.g. "ABC" (0) 对应 数字(2) 
                        break;
                    }
                }
            }
            // '-' 自动跳过
        }

        // 在第3位之后添加连字符
        ans.insert(3, "-");

        cout << ans << endl;
    }

    return 0;
}

