//非常重要: cin不读取的换行符，会被之后的getline读取，需用cin.ignore()丢弃遗留的换行符 
//C 语言的合法标识符由字母、数字和下划线 _ 组成，不能以数字开头，不能与关键字重名，也不能使用标准保留的标识符名称。 
#include <iostream>
#include <string>
using namespace std;

int main(){
	int n;
	string s;
	cin >> n; //cin没有读取换行符，这个换行符会被之后的getline读取，输出一个0 
	cin.ignore(); //丢弃下一个字符，即遗留的换行符 
	for (int i = 0; i < n; i++){
		s = "";
		getline(cin, s);
		int judge = 0;
		if (s[0] == '_' || (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z')) judge = 1; //注意s[i]是char类型，与其比较的字符应用单引号'' 
		int cnt = 0;
		bool first = true;
		for (char x : s){
			if (first){
				first = false;
				continue;
			} 
			if (x != '_' && !((x >= 'a' && x <= 'z') || x >= 'A' && x <= 'Z' || x >= '0' && x <= '9')){ 
			//字符需为'_'或数字或字母才合法，反过来推是：字符不为'_' 且 不为字母或数字 ->不合法 
				judge = 0;
			}
		}
		cout << judge << endl;
	}
	return 0;
}
