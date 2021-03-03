#include<iostream>
using namespace std;

int power(int x, unsigned p)
{
    int answ = 1;
    for (int i = 1; i <= p; ++i)
    {
        answ = answ * x;
    }
    return answ;
}

int main()
{
    int x, p;
    cin>>x>>p;
    cout<<power(x, p)<<endl;
    return 0;
}