#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int N;
	cin>>N;
	for (int p=2; p<=N; p++){
		for (int i=2; i<=N; i++){
		for (int j=i+1; j<=N; j++){
			for (int k=j+1; k<=N; k++){
				if (p*p*p == i*i*i + j*j*j + k*k*k) cout<<"Cube = "<<p<<", Triple = ("<<i<<','<<j<<','<<k<<')'<<endl;
				}
			}
		}
	}
	return 0;
} 
