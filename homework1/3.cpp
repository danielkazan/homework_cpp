#include<iostream>
#include<math.h>
using namespace std;

int l(int x, int y, int count)
{
    y = y * 2;
    ++count;
    if (y < x) {
        return l(x, y, count);
    }
    else {
        return count;
    }
}
int main(){

    int x;
    cin>>x;
    cout<<l(x, 2, 0)<<endl;
    return 0;
}