#ifndef CIRCLE_LINKED_QUEUE_H_INCLUDED
#define CIRCLE_LINKED_QUEUE_H_INCLUDED

using namespace std;
enum Error_code{success, underflow, overflow};
typedef double Node_entry;
typedef double Queue_entry;

struct Node//节点
{
// data members
    Node_entry entry;//内容
    Node *next; //指向下一个节点的指针 use before definition
// constructors
    Node();
    Node(Node_entry item, Node *add_on = NULL);//默认指针指向空
};

Node::Node()
{
    next=NULL;//默认为空
}

Node::Node(Node_entry item, Node *add_on)
{
    entry=item;
    next=add_on;//连接到下一个节点
}

class Queue
{
protected:
    Node *rear;//后指针
public:
    //standard queue methods
    Queue();
    bool empty()const;//队空
    Error_code append(const Queue_entry &item);//入队
    Error_code serve();//出队
    Error_code retrieve(Queue_entry &item)const;//获得第一个元素
    void clear();
    //safety features for linked structures
    ~Queue();//析构函数
    Queue(const Queue &original);//拷贝构造函数
    void operator = (const Queue &original);//重载=操作符
};

Queue::Queue()
{
    rear=NULL;
}

bool Queue::empty()const
{
    if(rear==NULL) return true;
    else return false;
}

Error_code Queue::append(const Queue_entry &item)//入队
{
    Node *new_rear=new Node(item);//在堆区新建一个Node节点，并用new_rear指针指向它

    if(new_rear==NULL) return overflow;//堆区满了？
    if(rear==NULL)//栈空，需要初始化front节点
    {
        rear=new_rear;
        new_rear->next=rear;//组成一个环结构
    }
    else
    {
        new_rear->next=rear->next;//新节点连接头节点
        rear->next=new_rear;//原来的尾结点连接新节点
        rear=new_rear;//尾指针后移
    }
    return success;
}

Error_code Queue::serve()//出队,经过修改还未测试
{
    if(rear==NULL) return underflow;//栈空
    Node *old_front;
    old_front=rear;
    rear=rear->next;//队首指针后移(为什么不能用front=front.next)
    if(rear->next==old_front) rear=NULL;//如果往后没有了
    delete old_front;//old_front是唯一还指向原来的队首节点的指针，删除就没了。
    return success;
}

void Queue::clear()
{
    while(rear!=NULL)
    {
        serve();
    }
}

Error_code Queue::retrieve(Queue_entry &item)const
{
    if(rear==NULL) return underflow;
    item=rear->next->entry;
    return success;
}

Queue::~Queue()
{
    while(!empty())
    {
        serve();
    }
}

Queue::Queue(const Queue &original)//拷贝构造函数
{
    Queue temp;
    temp=original;
    rear=temp.rear;
}

void Queue::operator = (const Queue &original)
{
    Node *new_rear, *new_copy, *original_Node=original.rear;
    if(original.rear==NULL) new_rear==NULL;//空栈
    else
    {
        new_copy=new_rear=new Node(original_Node->entry);
        while(original_Node->next!=original.rear)
        {
            original_Node=original_Node->next;//取出entry
            new_copy->next=new Node(original_Node->entry);//继续创建节点
            new_copy=new_copy->next;//移动到下一个
        }
        while(!empty())
            serve();
        rear=new_rear;
    }
}

#endif // CIRCLE_LINKED_QUEUE_H_INCLUDED

//82行析构时会出现错误，也不明白原因
