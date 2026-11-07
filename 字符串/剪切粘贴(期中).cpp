#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 处理一个完整的样本
void process(vector<string>& lines) {
    int namespacePos = -1;    // [Namespace] 所在行
    int requirementPos = -1;  // [Requirement] 所在行

    int abnormalType = 0;     // 1: Namespace 异常
                              // 2: Requirement 异常

    string number = "";       // 异常编号，如 "1"、"2"

    // 第一步：寻找标签和异常类型
    for (int i = 0; i < (int)lines.size(); i++) {

        string& s = lines[i];

        if (s == "[Namespace]") {
            namespacePos = i;
        }
        else if (s == "[Requirement]") {
            requirementPos = i;
        }
        else if (s.find("[Namespace]-(") == 0) {

            namespacePos = i;
            abnormalType = 1;

            // 提取括号中的编号
            number = s.substr(13, s.size() - 14);

            // 删除异常标记
            s = "[Namespace]";
        }
        else if (s.find("[Requirement]-(") == 0) {

            requirementPos = i;
            abnormalType = 2;

            number = s.substr(15, s.size() - 16);

            s = "[Requirement]";
        }
    }

    // 第二步：将异常编号转移到另一个标签
    if (abnormalType == 1 && requirementPos != -1) {
        lines[requirementPos] =
            "[Requirement]-(" + number + ")";
    }
    else if (abnormalType == 2 && namespacePos != -1) {
        lines[namespacePos] =
            "[Namespace]-(" + number + ")";
    }

    // 第三步：输出整个样本
    for (const string& s : lines) {
        cout << s << '\n';
    }
}

int main() {
    string line;

    vector<string> lines;

    // 分割线由64个 '-' 组成
    string separator(64, '-');

    // 一直读取到文件结束
    while (getline(cin, line)) {

        if (line == separator) {

            // 先处理之前读到的样本
            process(lines);
            lines.clear();

            // 分割线保持不变
            cout << line << '\n';
        }
        else {
            // 保存原始行，包括空行
            lines.push_back(line);
        }
    }

    // 文件结束后，处理最后一个样本
    process(lines);

    return 0;
}
