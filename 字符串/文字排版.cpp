#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    int n;
    cin >> n;
    cin.ignore();
    string line, word, output= "";
    getline(cin, line);
    stringstream ss(line);
    
    bool first = true;
    
    int i = 1;
    while (ss >> word) {
        if (!first) output += " ";
        first = false;
        string x = output;
        x += word;
        if (x.length() > 80){
            output.pop_back();
            cout << output << endl;
            output = word + " ";
            first = true;
        }
        else if (i == n){
            output += word;
            cout << output;
        }
        else{
            output = x;
        }
        i++;
    }
    return 0;
}