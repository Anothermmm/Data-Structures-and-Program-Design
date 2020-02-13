#include <iostream>
#include "Ordered_Single_Linked_List.h"

using namespace std;

int main()
{
    List<int> A;
    List<int> B;
    List<int> C;
    A.insert(1);
    A.insert(2);
    A.insert(3);
    A.insert(9);
    A.insert(4);
    A.insert(5);
    A.show();
    B.insert(10);
    B.insert(6);
    B.insert(8);
    B.insert(7);
    B.insert(15);
    B.show();
    C.merge(A,B);
    C.show();
    return 0;
}
