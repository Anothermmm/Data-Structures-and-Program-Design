#include <iostream>
#include "circle_linked_queue.h"
using namespace std;

int main()
{
    double item,xx;

    Queue a,b;
    a.append(3);
    a.append(4);
    a.serve();
    a.retrieve(xx);
    cout<<xx;
    return 0;
}
