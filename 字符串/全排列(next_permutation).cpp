//本题亦可以通过 排列型dfs + 回溯 实现
#include <iostream>
#include <algorithm> //next_permutation();
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    do {
        for (auto c : s){
            cout << c ;
        }
        cout << endl;
    } while (next_permutation(s.begin(), s.end())); ////next_permutation(起始迭代器, 结束迭代器);
    //while (next_permutation(a, a + n));这种写法只适用于数组，而对于string必须要用迭代器
    //next_permutation()会改变数组元素的顺序
    return 0;
}

/*
#next_permutation();
将一个序列变成字典序中的下一个排列（Next Lexicographical Permutation）
***用 do...while 而不是 while : 需要先处理初始排列，再生成下一个排列。
***while 会先调用函数，再执行循环体 
*/
