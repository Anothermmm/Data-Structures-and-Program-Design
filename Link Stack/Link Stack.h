#ifndef LINK_STACK_H_INCLUDED
#define LINK_STACK_H_INCLUDED

enum Error_code{success, overflow, underflow};
using namespace std;

class Node
{

};

class Stack
{
public:
    Stack();
    bool empty()const;
    Error_code pop();
	Error_code top(Stack_entry& item)const;
	Error_code push(const Stack_entry& item);
	//Safety features for link stack
	Stack(const Stack &original);
	~Stack();
	void operator=(const Stack& original);
protected:
    Node *top_node;
};


#endif // LINK_STACK_H_INCLUDED
