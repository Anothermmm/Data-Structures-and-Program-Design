#ifndef SINGLE_LINKED_QUEUE_H_INCLUDED
#define SINGLE_LINKED_QUEUE_H_INCLUDED

using namespace std;
enum Error_code{success, underflow, overflow};
typedef double Node_entry;
typedef double Queue_entry;

struct Node//�ڵ�
{
// data members
    Node_entry entry;//����
    Node *next; //ָ����һ���ڵ��ָ�� use before definition
// constructors
    Node();
    Node(Node_entry item, Node *add_on = NULL);//Ĭ��ָ��ָ���
};

Node::Node()
{
    next=NULL;//Ĭ��Ϊ��
}

Node::Node(Node_entry item, Node *add_on)
{
    entry=item;
    next=add_on;//���ӵ���һ���ڵ�
}

class Queue
{
protected:
    Node *front,*rear;//ǰ��ָ��
public:
    //standard queue methods
    Queue();
    bool empty()const;//�ӿ�
    Error_code append(const Queue_entry &item);//���
    Error_code serve();//����
    Error_code retrieve(Queue_entry &item)const;//��õ�һ��Ԫ��
    //safety features for linked structures
    ~Queue();//��������
    Queue(const Queue &original);//�������캯��
    void operator = (const Queue &original);//����=������
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

Error_code Queue::append(const Queue_entry &item)//���
{
    Node *new_rear=new Node(item);//�ڶ����½�һ��Node�ڵ㣬����new_rearָ��ָ����

    if(new_rear==NULL) return overflow;//�������ˣ�
    if(rear==NULL)//ջ�գ���Ҫ��ʼ��front�ڵ�
    {
        front=new_rear;
        rear=new_rear;
    }
    else
    {
        rear->next=new_rear;//ԭ�������һ���ڵ��ָ��ָ�������Ľڵ�
        rear=new_rear;//βָ���ƶ�
    }
    return success;
}

Error_code Queue::serve()//����
{
    if(front==NULL) return underflow;//ջ��
    Node *old_front=front;
    front=old_front->next;//����ָ�����(Ϊʲô������front=front.next)
    if(front==NULL) rear=NULL;//�������û����
    delete old_front;//old_front��Ψһ��ָ��ԭ���Ķ��׽ڵ��ָ�룬ɾ����û�ˡ�
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

Queue::Queue(const Queue &original)//�������캯��
{
    Queue temp;
    temp=original;
    front=temp.front;
    rear=temp.rear;
}

void Queue::operator = (const Queue &original)//����=������
{
    Node *new_front, *new_copy, *original_Node=original.front;
    //new_front�Ǹ��ƺ��ͷָ��
    //new_copy��һֱ���ƶ�����ֵentry��ָ��
    //original_Node����ȡ��ԭ����entry��ָ��
    if(original.front==NULL) new_front=NULL;//��ջ
    else
    {
        new_copy=new_front=new Node(original_Node->entry);//�ȴ�����һ���ڵ�
        //new_front�Ͳ�����
        //new_copy��ָ���һ��
        while(original_Node->next!=NULL)
        {
            original_Node=original_Node->next;//ȡ��entry
            new_copy->next=new Node(original_Node->entry);//���������ڵ�
            new_copy=new_copy->next;//�ƶ�����һ��
        }
    }
    while(!empty())//���ԭ����
        serve();
    front=new_front;//���غ���µĶ��е�ͷָ��ָ���Ѿ���ֵ���˵Ķ���
    rear=new_copy;//βָ�����new_copyֹͣ�ĵط�
}

#endif // SINGLE_LINKED_QUEUE_H_INCLUDED


