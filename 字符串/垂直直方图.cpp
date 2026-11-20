#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(){
    string line;
    map<char, int> letter;
    vector<string> graph(27);
    int max_h = 0; //记录最高的高度

    while(getline(cin,line)){
        for (char x : line){
            if (isalpha(x)){
                letter[x]++;
            }
        }
    }
    for (auto y : letter){
        if (y.second > max_h) max_h = y.second; //y.first -> key; y.second -> value
    }

    //先绘制一个纵向的直方图，最后再横向输出
    for (int i = 0; i <= max_h; i++){
        graph[0].push_back('#');
    }

    for (int i = 1; i <= 26; i++){
        char a = (char)(i + 'A' - 1);
        graph[i].push_back(a);
        for (int j = 0; j < max_h; j++){
            if (j < letter[a]) graph[i].push_back('*');
            else graph[i].push_back(' ');
        }
    }

    //横向输出，从最后一列开始向前遍历，再按行顺序输出
    for (int i = max_h; i >= 0; i--){
        for (int j = 0; j < 27; j++){
            cout << graph[j][i];
        }
        cout << endl;
    }
    return 0;
}