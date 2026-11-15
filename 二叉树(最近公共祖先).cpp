//不需要 DFS，也不需要真的建立一棵树
//题目翻译：给你二叉树中的两个结点，找出它们从下往上走时，第一次相遇的那个结点。
//最近公共祖先（Lowest Common Ancestor，LCA）
//编号为 n 的结点，它的父结点编号就是 floor(n / 2)。

#include <iostream>
using namespace std;

int main(){
    int x, y;
    cin >> x >> y;
    while (x != y){
        if (x > y) x /= 2;
        else if (x < y) y /= 2;
    }
    cout << x ;
    return 0;
}