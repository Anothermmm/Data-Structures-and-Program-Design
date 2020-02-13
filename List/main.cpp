#include <iostream>
#include "List.h"
using namespace std;

int main()
{
    int x,y;
    List<int> A;
    A.insert(0,1);//L(1)
    A.insert(1,3);//L(1,3)
    A.insert(2,5);//L(1,3,5)
    A.insert(3,7);//L(1,3,5,7)
    A.replace(2,6);//L(1,3,6,7)
    A.remove(0,x);//x=1,L(3,6,7)
    A.retrieve(1,y);//y=6,L(3,6,7)
    cout<<"x="<<x<<endl;
    cout<<"y="<<y<<endl;
    while(!A.empty())
    {
        int m;
        A.remove(0,m);//从前面全部取出
        cout<<"m="<<m<<endl;
    }
    return 0;
}
