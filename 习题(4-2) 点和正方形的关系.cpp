#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

int main(){
    float x,y;
    scanf("%f,%f", &x, &y);
    //cout<<x<<y; 
    if (abs(x) <= 1 && abs(y) <= 1) cout<<"yes";
    else cout<<"no";
    return 0;
}
