#include <iostream>
#include <map>
#include <cctype> //isalnum(), isalpha(), isdigit()
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
	string sentence, word;
	map<string, int> word_map;
	vector<string> word_set;
	getline(cin, sentence);
	
	//把无关标点符号改成空格，方便用stringstream进行切割，但需追单引号 ' 需要保留 
	for (auto &c : sentence){ //&c引用传递，修改c能直接修改sentence里对应的字符 
		if (!(isalnum(c) || c == '\'')) c = ' '; // 若c是字符或数字，isalnum(c) 返回true (也可用 isalpha和isdigit);
		//'\'' 单引号 ' 本身有特殊作用，所以如果想表示单引号这个字符，就需要使用转义字符 \。 
	}
	
	stringstream ss(sentence);
	while (ss >> word){
		if (word_map[word] == 0){ //如果元素不存在，mp[x]返回 0 
			word_set.push_back(word);
		}
		word_map[word]++; //如果元素不存在，就会加入元素 
	}
	for (auto w : word_set){
		cout << w << ' ' << word_map[w] << endl;
	}
	return 0;
}

/*
其他常用转义字符
写法	含义
'\''	单引号 '
'\"'	双引号 "
'\\'	反斜杠 \
'\n'	换行
'\t'	制表符
'\0'	空字符
*/
