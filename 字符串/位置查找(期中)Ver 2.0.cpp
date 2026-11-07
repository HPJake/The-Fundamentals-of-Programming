//Ver 2.0: 用一个长度为26的数组记录每个字母第一次出现的位置 

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    cin >> s;

    int pos[26];

    // -1 表示该字母尚未出现
    for (int i = 0; i < 26; i++) {
        pos[i] = -1;
    }

    // 从左往右扫描整个字符串
    for (int i = 0; i < (int)s.size(); i++) {

        // 转换成小写，忽略大小写
        char c = tolower(s[i]);

        // 跳过所有非英文字母
        if (c < 'a' || c > 'z') {
            continue;
        }

        // 将字母映射为 0~25
        int index = c - 'a';

        // 只有第一次出现时才记录位置
        if (pos[index] == -1) {
            pos[index] = i;
        }
    }

    // 按 a~z 的顺序输出
    for (int i = 0; i < 26; i++) {

        // 没出现过的字母不输出
        if (pos[i] == -1) {
            continue;
        }

        char c = 'a' + i;

        cout << c << " " << pos[i] << endl;
    }

    return 0;
}
