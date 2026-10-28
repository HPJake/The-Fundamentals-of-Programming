#include <iostream>
#include <algorithm>
using namespace std;

struct Student{
	int id;
	double score;
};

bool cmp(Student a, Student b){
	return (a.score > b.score);
}

int main(){
	int n,k;
	cin >> n >> k;
	Student s[105];
	for (int i = 0; i< n; i++){
		cin >> s[i].id >> s[i].score;
	} 
	sort(s, s + n, cmp);
	printf("%d %g\n", s[k-1].id, s[k-1].score);
	return 0;
}
