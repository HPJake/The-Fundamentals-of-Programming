#include <iostream>
#include <cstring>
using namespace std;

int main(){
	string s,s1,s2;
	int d;
	getline(cin,s,',');
    getline(cin,s1,',');
    getline(cin,s2,'\n');
    if (s.find(s1)==-1 || s.find(s2)==-1) d=-1;
    else d = (s.rfind(s2)-1) - (s.find(s1)+s1.length()-1);
    if (d<-1) d=-1;
	cout<<d<<endl;
	return 0;
}
