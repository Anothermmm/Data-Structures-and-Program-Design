#ifndef CIRCLE_LINKED_QUEUE_H_INCLUDED
#define CIRCLE_LINKED_QUEUE_H_INCLUDED

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
    Node *rear;//��ָ��
public:
    //standard queue methods
    Queue();
    bool empty()const;//�ӿ�
    Error_code append(const Queue_entry &item);//���
    Error_code serve();//����
    Error_code retrieve(Queue_entry &item)const;//��õ�һ��Ԫ��
    void clear();
    //safety features for linked structures
    ~Queue();//��������
    Queue(const Queue &original);//�������캯��
    void operator = (const Queue &original);//����=������
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

Error_code Queue::append(const Queue_entry &item)//���
{
    Node *new_rear=new Node(item);//�ڶ����½�һ��Node�ڵ㣬����new_rearָ��ָ����

    if(new_rear==NULL) return overflow;//�������ˣ�
    if(rear==NULL)//ջ�գ���Ҫ��ʼ��front�ڵ�
    {
        rear=new_rear;
        new_rear->next=rear;//���һ�����ṹ
    }
    else
    {
        new_rear->next=rear->next;//�½ڵ�����ͷ�ڵ�
        rear->next=new_rear;//ԭ����β��������½ڵ�
        rear=new_rear;//βָ�����
    }
    return success;
}

Error_code Queue::serve()//����,�����޸Ļ�δ����
{
    if(rear==NULL) return underflow;//ջ��
    Node *old_front;
    old_front=rear;
    rear=rear->next;//����ָ�����(Ϊʲô������front=front.next)
    if(rear->next==old_front) rear=NULL;//�������û����
    delete old_front;//old_front��Ψһ��ָ��ԭ���Ķ��׽ڵ��ָ�룬ɾ����û�ˡ�
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

Queue::Queue(const Queue &original)//�������캯��
{
    Queue temp;
    temp=original;
    rear=temp.rear;
}

void Queue::operator = (const Queue &original)
{
    Node *new_rear, *new_copy, *original_Node=original.rear;
    if(original.rear==NULL) new_rear==NULL;//��ջ
    else
    {
        new_copy=new_rear=new Node(original_Node->entry);
        while(original_Node->next!=original.rear)
        {
            original_Node=original_Node->next;//ȡ��entry
            new_copy->next=new Node(original_Node->entry);//���������ڵ�
            new_copy=new_copy->next;//�ƶ�����һ��
        }
        while(!empty())
            serve();
        rear=new_rear;
    }
}

#endif // CIRCLE_LINKED_QUEUE_H_INCLUDED

//82������ʱ����ִ���Ҳ������ԭ��
