#ifndef SINGLE_LINKED_QUEUE_H_INCLUDED
#define SINGLE_LINKED_QUEUE_H_INCLUDED

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
    Node *front,*rear;//前后指针
public:
    //standard queue methods
    Queue();
    bool empty()const;//队空
    Error_code append(const Queue_entry &item);//入队
    Error_code serve();//出队
    Error_code retrieve(Queue_entry &item)const;//获得第一个元素
    //safety features for linked structures
    ~Queue();//析构函数
    Queue(const Queue &original);//拷贝构造函数
    void operator = (const Queue &original);//重载=操作符
};

Queue::Queue()
{
    front=NULL;
    rear=NULL;
}

bool Queue::empty()const
{
    if(front==NULL) return true;
    else return false;
}

Error_code Queue::append(const Queue_entry &item)//入队
{
    Node *new_rear=new Node(item);//在堆区新建一个Node节点，并用new_rear指针指向它

    if(new_rear==NULL) return overflow;//堆区满了？
    if(rear==NULL)//栈空，需要初始化front节点
    {
        front=new_rear;
        rear=new_rear;
    }
    else
    {
        rear->next=new_rear;//原来的最后一个节点的指针指向新增的节点
        rear=new_rear;//尾指针移动
    }
    return success;
}

Error_code Queue::serve()//出队
{
    if(front==NULL) return underflow;//栈空
    Node *old_front=front;
    front=old_front->next;//队首指针后移(为什么不能用front=front.next)
    if(front==NULL) rear=NULL;//如果往后没有了
    delete old_front;//old_front是唯一还指向原来的队首节点的指针，删除就没了。
    return success;
}

Error_code Queue::retrieve(Queue_entry &item)const
{
    if(front==NULL) return underflow;
    item=front->entry;
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
    front=temp.front;
    rear=temp.rear;
}

void Queue::operator = (const Queue &original)//重载=操作符
{
    Node *new_front, *new_copy, *original_Node=original.front;
    //new_front是复制后的头指针
    //new_copy是一直在移动负责赋值entry的指针
    //original_Node用来取出原来的entry的指针
    if(original.front==NULL) new_front=NULL;//空栈
    else
    {
        new_copy=new_front=new Node(original_Node->entry);//先创建第一个节点
        //new_front就不动了
        //new_copy先指向第一个
        while(original_Node->next!=NULL)
        {
            original_Node=original_Node->next;//取出entry
            new_copy->next=new Node(original_Node->entry);//继续创建节点
            new_copy=new_copy->next;//移动到下一个
        }
    }
    while(!empty())//清除原队列
        serve();
    front=new_front;//重载后的新的队列的头指针指向已经赋值好了的队列
    rear=new_copy;//尾指针就是new_copy停止的地方
}

#endif // SINGLE_LINKED_QUEUE_H_INCLUDED


