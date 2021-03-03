#include "iostream"
using namespace std;
int main(){
int n;
cin >> n;
int a, s;
for(int i = 0; i < n; i++){
    cin >> a;
    s += a;
}
cout << s;
    return 0;
}