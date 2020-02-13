#ifndef SINGLE_LINKED_LIST_H_INCLUDED
#define SINGLE_LINKED_LIST_H_INCLUDED

enum Error_code {success,underflow,overflow,Range_error,fail};
const int max_list=10000;
using namespace std;

template<class Node_entry>
struct Node
{
    Node_entry entry;//数据域
    Node<Node_entry> *next;//指针域
    Node();
    Node(const Node_entry &item, Node<Node_entry> *link=NULL);//拷贝构造函数，没有指针域则先指向空
};

template<class Node_entry>
Node<Node_entry>::Node()
{
    next=NULL;
}

template<class Node_entry>
Node<Node_entry>::Node(const Node_entry &item, Node<Node_entry> *link)
{
    entry=item;
    next=link;
}



template<class List_entry>
class List
{
public:
    List();
    List(const List<List_entry>& copy);//拷贝构造函数
    void operator=(const List<List_entry>& copy);//重载线性表相等
    int size()const;//线性表长度
    bool empty()const;//判空
    bool full()const;//判满
    void clear();//删除所有节点
    void traverse(void (*visit)(List_entry& ));//遍历操作
    Error_code replace(int position, const List_entry& x);//替换
    Error_code remove(int position, List_entry& x);//去掉position位置的元素
    Error_code retrieve(int position, List_entry& x)const;//提取position位置的元素
    Error_code insert(int position, const List_entry& x);//在position位置插入元素
    void reverse();//倒置
    Error_code append(const List_entry& x);//表尾插入x元素
    Error_code find(const List_entry& x, int &position);//寻找值为x的元素的位置，并返回position。找不到返回-1
    Error_code add_on(const List_entry& x, int &number);//统计值为x的元素的个数

    Error_code findmincost(double &minnum);//最小的cost赋给minnum
    Error_code findmaxcost(double &maxnum);//最大的cost赋给maxnum
    Error_code findavercost(double &avenum);//平均cost
    Error_code one_day_cost(double &total, const string &date);//10月2日一天的花费
    Error_code day_and_proj_find_cost(double &cost, const string &date, const string &proj);//一天的一个项目的花费
    Error_code one_proj_cost(double &total, const string &proj);//一个项目所有的花费

    Error_code showall()const;//打印所有数据
    int unrecursive_removeallx(List_entry x);//非递归去掉所有值为x的元素,返回被删元素个数
    int recursive_removeallx(List_entry x);//递归去掉所有值为x的元素，返回被删元素个数
    int recursive_removeall(Node<List_entry>* &L, List_entry x);//上一函数调用
    ~List();
protected:
    int count;
    Node<List_entry> *head;
    Node<List_entry>* set_position(int position)const;//获得第position个节点的位置，返回指针
};

template<class List_entry>
Node<List_entry>* List<List_entry>::set_position(int position)const
{
    Node<List_entry> *q=head;
    for(int i=0; i<position; i++) //移动到position的位置
        q=q->next;
    return q;//指针返回
}

template<class List_entry>
List<List_entry>::List()
{
    count=0;
    head=NULL;
}

template<class List_entry>
List<List_entry>::List(const List<List_entry>& copy)
{
    Node<List_entry> *temp_node,*new_node;

    count=0;
    head=NULL;
    if(copy.empty())
        count=0;
    temp_node=copy.head;
    new_node=head=new Node<List_entry>(temp_node->entry);
    count++;
    while(temp_node->next!=NULL)
    {
        temp_node=temp_node->next;//取出下一个
        new_node->next=new Node<List_entry>(temp_node->entry);
        new_node=new_node->next;
        count++;
    }
    new_node->next=NULL;
}

template<class List_entry>
int List<List_entry>::size()const
{
    return count;
}

template<class List_entry>
bool List<List_entry>::empty()const
{
    return count==0;
}

template<class List_entry>
bool List<List_entry>::full()const
{
    if (count == max_list)
        return true;
    else
        return false;
}

template<class List_entry>
void List<List_entry>::clear()
{
    Node<List_entry>* temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        delete temp;
    }
    count=0;
}

template<class List_entry>
Error_code List<List_entry>::showall()const
{
    List_entry x;
    if(count==0) return underflow;
    cout<<"日期："<<"\t"<<"项目:"<<"\t"<<"花费："<<endl;
    for(int i=0;i<count;i++)
    {
        retrieve(i,x);
        x.show();
    }
    return success;
}

template<class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry& x)//单纯地修改，并没有创建新的节点，所以不要delete
{
    if(empty())
        return underflow;
    if(position<0 || position>=count)
        return Range_error;
    else
        set_position(position)->entry=x;
    return success;
}

template<class List_entry>
Error_code List<List_entry>::remove(int position, List_entry& x)
{
    Node<List_entry> *temp_node,*previous,*following;
    if(empty())
        return underflow;
    if(position<0 || position>=count)
        return Range_error;
    temp_node=set_position(position);
    x=temp_node->entry;
    if(position>0)
    {
        previous=set_position(position-1);
        if(position<count-1)
            following=set_position(position+1);
        else
            following=NULL;
        delete temp_node;
        previous->next=following;
    }
    if(position==0)
    {
        previous=head;
        if(position<count-1)
            following=set_position(position+1);
        else
            following=NULL;
        delete temp_node;
        head=following;
    }
    count--;
    return success;
}

template<class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry& x)const
{
    if(empty())
        return underflow;
    if(position<0 || position>=count)
        return Range_error;
    x=set_position(position)->entry;
    return success;
}

template<class List_entry>
Error_code List<List_entry>::append(const List_entry& x)
{
    this->insert(count,x);
    return success;
}

template<class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry& x)
{
    Node<List_entry> *new_node,*previous,*following;
    if(position<0 || position>count)
        return Range_error;
    if(position>0)
    {
        previous=set_position(position-1);
        following=previous->next;
    }
    else
        following=head;
    new_node=new Node<List_entry>(x,following);
    if(new_node==NULL)
        return overflow;
    if(position==0)
        head=new_node;
    else
    {
        previous->next=new_node;
    }
    count++;
    return success;
}

template<class List_entry>
List<List_entry>::~List()
{
    clear();
}

template<class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry& ))
{
    if(empty())
        return underflow;
    Node<List_entry>* temp;
    temp=head;
    while(temp!=NULL)
    {
        (*visit)(temp.entry);
        temp=temp->next;
    }
}

template<class List_entry>
void List<List_entry>::operator=(const List<List_entry>& copy)
{
    Node<List_entry> *temp_node,*new_node;

    if(copy.empty())
    {
        count=0;
        head=NULL;
    }
    else
    {
        count=0;
        head=NULL;
        temp_node=copy.head;
        new_node=head=new Node<List_entry>(temp_node->entry);
        count++;
        while(temp_node->next!=NULL)
        {
            temp_node=temp_node->next;//取出下一个
            new_node->next=new Node<List_entry>(temp_node->entry);
            new_node=new_node->next;
            count++;
        }
    }
}

template<class List_entry>
void List<List_entry>::reverse()
{
    if(!empty())
    {
        Node<List_entry> *p,*q;
        p=head->next;
        head->next=NULL;
        while(p!=NULL)
        {
            q=p->next;
            p->next=head;
            head=p;
            p=q;
        }
    }
}

template<class List_entry>
Error_code List<List_entry>::find(const List_entry& x, int &position)
{
    Node<List_entry> *temp_node;
    int loc=0;
    position=-1;
    temp_node=head;
    if(empty())
        return underflow;
    while(temp_node!=NULL)
    {
        if(x==temp_node->entry)
        {
            position=loc;
            break;
        }
        loc++;
        temp_node=temp_node->next;
    }
    return success;
}

template<class List_entry>
Error_code List<List_entry>::add_on(const List_entry& x, int &number)
{
    Node<List_entry> *temp_node;
    number=0;
    temp_node=head;
    if(empty())
        return underflow;
    while(temp_node!=NULL)
    {
        if(x==temp_node->entry)
        {
            number++;
        }
        temp_node=temp_node->next;
    }
    return success;
}

template<class List_entry>
int List<List_entry>::unrecursive_removeallx(List_entry x)
{
    Node<List_entry> dummy,*p,*q;
    int number=0;
    dummy.next=head;
    p=&dummy;//制造一个头指针，让后面好判断
    while(p->next)
    {
        if (p->next->entry==x)
        {
            q=p->next;
            p->next=q->next;
            delete q;
            number++;
        }
        else
            p=p->next;
    }
    head=dummy.next;
    return number;
}

template<class List_entry>
int List<List_entry>::recursive_removeallx(List_entry x)
{
    int number=recursive_removeall(head,x);
    return number;
}

template <class List_entry>
int List<List_entry>::recursive_removeall(Node<List_entry>* &L, List_entry x)
{
    if (L==NULL)
        return 0;
    if (L->entry==x)
    {
        Node<List_entry> * temp=L;
        L=L->next;
        delete temp;
        return  1+recursive_removeall(L,x);
    }
    else
    {
        return recursive_removeall(L->next,x);
    }
}

template <class List_entry>
Error_code List<List_entry>::findmincost(double &minnum)
{
    List_entry x;
    if(count==0)
    {
        cout<<"无最小值。输出-1。"<<endl;
        return underflow;
    }
    if(count==1)
    {
        retrieve(0,x);
        minnum=x.getcost();
        return success;
    }
    retrieve(0,x);
    minnum=x.getcost();
    for(int i=1;i<count;i++)
    {
        retrieve(i,x);
        if(minnum>x.getcost()) minnum=x.getcost();
    }
    return success;
}

template <class List_entry>
Error_code List<List_entry>::findmaxcost(double &maxnum)
{
    List_entry x;
    if(count==0)
    {
        cout<<"无最大值。输出-1。"<<endl;
        return underflow;
    }
    if(count==1)
    {
        retrieve(0,x);
        maxnum=x.getcost();
        return success;
    }
    retrieve(0,x);
    maxnum=x.getcost();
    for(int i=1;i<count;i++)
    {
        retrieve(i,x);
        if(maxnum<x.getcost()) maxnum=x.getcost();
    }
    return success;
}

template <class List_entry>
Error_code List<List_entry>::findavercost(double &avenum)
{
    List_entry x;
    double sum=0;

    if(count==0)
    {
        cout<<"无平均值。输出-1。"<<endl;
        return underflow;
    }
    for(int i=0;i<count;i++)
    {
        retrieve(i,x);
        sum+=x.getcost();
    }
    avenum=sum/count;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::one_day_cost(double &total, const string &date)
{
    double sum;
    List_entry x;

    if(count==0)
    {
        cout<<"无数据。"<<endl;
        return underflow;
    }
    for(int i=0;i<count;i++)
    {
        retrieve(i,x);
        if(x.getdate()==date) sum+=x.getcost();
    }
    total=sum;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::day_and_proj_find_cost(double &cost, const string &date, const string &proj)
{
    List_entry x;
    if(count==0)
    {
        cout<<"无数据。"<<endl;
        return underflow;
    }
    for(int i=0;i<count;i++)
    {
        retrieve(i,x);
        if(x.getdate()==date && x.getproj()==proj)
        {
            cost=x.getcost();
            break;
        }
    }
    return success;
}

template <class List_entry>
Error_code List<List_entry>::one_proj_cost(double &total, const string &proj)
{
    List_entry x;
    double sum=0;
    if(count==0)
    {
        cout<<"无数据。"<<endl;
        return underflow;
    }
    for(int i=0;i<count;i++)
    {
        retrieve(i,x);
        if(x.getproj()==proj)
        {
            sum+=x.getcost();
        }
    }
    total=sum;
    return success;
}
#endif // SINGLE_LINKED_LIST_H_INCLUDED
