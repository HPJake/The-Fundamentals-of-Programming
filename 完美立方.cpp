#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int N;
	cin>>N;
	for (int i=2; i<=N; i++){
		for (int j=i+1; j<=N; j++){
			for (int k=j+1; k<=N; k++){
				int sum = (i*i*i + j*j*j + k*k*k);
				int t= round(cbrt(sum));
				if (t > 24) break;
				//cout<<t<<" "<<i<<" "<<j<<" "<<k<<endl;
				//cout<<floor(t)<<endl;
				if (t*t*t == sum){
					cout<<t<<" "<<i<<" "<<j<<" "<<k<<endl;
				}
			}
		}
	}
	return 0;
} 
