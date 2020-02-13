#ifndef ORDERED_SINGLE_LINKED_LIST_H_INCLUDED
#define ORDERED_SINGLE_LINKED_LIST_H_INCLUDED

enum Error_code {success,underflow,overflow,Range_error};
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
    void show();//打印列表
    Error_code retrieve(int position, List_entry& x)const;//提取position位置的元素
    Error_code insert_pos(int position, const List_entry& x);//在position位置插入元素
    Error_code insert(const List_entry& x);//找到position位置再插入
    Error_code merge(List<List_entry> a, List<List_entry> b);//合并两个有序表
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
Error_code List<List_entry>::insert(const List_entry& x)
{
    Node<List_entry> *new_node,*previous,*temp;
    int position=0;
    temp=head;
    if(head==NULL) return this->insert_pos(0,x);
    while(temp!=NULL)
    {
        if(temp->entry>=x)
        {
            return this->insert_pos(position,x);
        }
        else
        {
            temp=temp->next;
            position++;
        }
    }
    if(temp==NULL)
    {
        return this->insert_pos(count,x);
    }
}

template<class List_entry>
Error_code List<List_entry>::insert_pos(int position, const List_entry& x)
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
void List<List_entry>::show()
{
    Node<List_entry> *temp;
    temp=head;
    while(temp!=NULL)
    {
        cout<<temp->entry<<"\t";
        temp=temp->next;
    }
    cout<<endl;
}

template<class List_entry>
List<List_entry>::~List()
{
    clear();
}

template<class List_entry>
Error_code List<List_entry>::merge(List<List_entry> a, List<List_entry> b)
{
    int i,j,k;
    this->clear();
    List_entry item_a,item_b,item_c;
    i=0;j=0;k=0;//三个position
    while(i<a.size() && j<b.size())//a,b两表都未到表尾，则将较小的元素插入到c表中
    {
        a.retrieve(i,item_a);
        b.retrieve(j,item_b);
        if(item_a<=item_b)
        {
            if(this->insert_pos(k++,item_a)==overflow)
                return overflow;
            i++;
        }
        else
        {
            if(this->insert_pos(k++,item_b)==overflow)
                return overflow;
            j++;
        }
    }
    while (j<b.size())//a表先到达表尾
    {
        b.retrieve(j++,item_b);
        if(this->insert_pos(k++,item_b)==overflow)
            return overflow;
    }
    while(i<a.size())//b表先到达表尾
    {
        a.retrieve(i++,item_a);
        if(this->insert_pos(k++,item_a)==overflow)
            return overflow;
    }
    return success;
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

#endif // SINGLE_LINKED_LIST_H_INCLUDED

