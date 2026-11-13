#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype> // isdigit()只能判断单个字符是否为数字，不能判断字符串是否为一个数(两位数以上)、小数、负数
#include <sstream>
#include <cstdio> // printf() 需要此头文件
using namespace std;

int main(){
    string s, elm;
    vector<string> v;
    stack<double> st;
    getline(cin, s);

    stringstream ss(s);
    while (ss >> elm){
        v.push_back(elm);
    }

    for(int i = v.size() - 1; i >= 0; i--){
        if (v[i] == "+" || v[i] == "-" || v[i] == "*" || v[i] == "/") { //isdigit()只能判断单个字符是否为数字，不能判断字符串是否为一个数(两位数以上)、小数、负数
            if (st.size() >= 2){ //段代码要正常执行，栈中必须至少有两个元素。加入这行避免报错
                double a = st.top(); st.pop();
                double b = st.top(); st.pop();
                if (v[i] == "+") st.push(a + b);
                else if (v[i] == "-") st.push(a - b);
                else if (v[i] == "*") st.push(a * b);
                else if (v[i] == "/") st.push(a / b);
            }
        }
        else {
            // 题目保证输入合法，因此这里就是数字
            st.push(stod(v[i])); //stod() means string to double
        }
    }
    printf("%f\n", st.top());
    return 0; 
}