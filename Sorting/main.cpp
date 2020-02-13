//�þ������ݷֱ���Բ�������Insertion Sort����ѡ������Selection Sort����ϣ������Shell Sort����
//�鲢����Mergesort������������Quick Sort����������Heapsort��
//������ʱ�䡢�Ƚϴ������ƶ�����������˳��ṹ
#include <iostream>
#include "List_creating.h"
#include "List.h"
#include <ctime>

using namespace std;

void readfile(List<int> &p, const string &seq, int len)//�Ӷ�Ӧ��txt�ļ����ʼ�������������
{
    int x;
    string path="D:\\";
    string filename;

    if(seq=="˳��") filename="˳��.txt";
    else if(seq=="����") filename="����.txt";
    else filename="���˳��.txt";
    path+=filename;

    ifstream fin(path.c_str());

    if(fin.good())
    {
        for(int i=0;i<len;i++)
        {
            fin>>x;
            p.insert(i,x);
        }
        fin.close();
    }
    else
    {
        cout<<"Readfile error!"<<endl;
        exit(0);
    }
}

void print(const string &seq, const string &name, int len, int number1, int number2, double totaltime)//��һ��������
{
    cout<<name<<"������Գ���Ϊ"<<len<<"��"<<seq<<"��ıȽϴ���Ϊ"<<number1<<"\n"<<"�ƶ�����Ϊ"<<number2<<"\n"<<"����ʱ��Ϊ";
    cout<<totaltime<<'s'<<endl<<endl;
}

void Insertion_Sort(const string &seq, int len)//��������
{
    List<int> A;//�����������
    clock_t start_time,end_time;
    string name="����";
    double totaltime;
    int number1,number2;//number1�ǱȽϴ�����number2���ƶ�����
    int i,temp;
    int current,previous;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    readfile(A,seq,len);//���г�ʼ��
    start_time=clock();
    for(int first_unsorted=1;first_unsorted<len;first_unsorted++)
    {
        A.retrieve(first_unsorted,current);
        i=first_unsorted-1;
        A.retrieve(i,previous);
        number1++;
        while(i>=0 && previous>current)
        {
            number1++;
            A.retrieve(i,temp);
            A.replace(i+1,temp);
            number2++;
            i--;
            A.retrieve(i,previous);
        }
        A.replace(i+1,current);
    }
    end_time=clock();
    //A.show();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void Selection_Sort(const string &seq, int len)//ѡ������
{
    List<int> A;//�����������
    clock_t start_time,end_time;
    int totaltime;//��ʱ��
    int number1,number2;//number1�ǱȽϴ�����number2���ƶ�����
    string name="ѡ��";
    int maxentry,current,currentnum;
    int top=len;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    readfile(A,seq,len);//���г�ʼ��
    start_time=clock();
    for(int i=0;i<len-2;i++)
    {
        A.retrieve(0,maxentry);
        currentnum=0;
        for(int j=1;j<top;j++)
        {
            A.retrieve(j,current);
            number1++;
            if(maxentry<current)
            {
                maxentry=current;
                currentnum=j;
            }
        }
        A.change(currentnum,len-1-i);
        number2++;
        top--;
    }
    end_time=clock();
    A.show();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void Insertion_Sort_interval(List<int> &A, int &number1, int &number2)//��д��������
{
    int current,previous;
    int i,temp;

    if(A.size()<=0)
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    for(int first_unsorted=1;first_unsorted<A.size();first_unsorted++)
    {
        A.retrieve(first_unsorted,current);
        i=first_unsorted-1;
        A.retrieve(i,previous);
        number1++;
        while(i>=0 && previous>current)
        {
            number1++;
            A.retrieve(i,temp);
            A.replace(i+1,temp);
            number2++;
            i--;
            A.retrieve(i,previous);
        }
        A.replace(i+1,current);
    }
}

void Sort_interval(List<int> &A, int start, int increment, int &number1, int &number2)//ϣ������������
{
    List<int> B;
    int x;

    for(int j=start,i=0;j<A.size();j+=increment,i++)
    {
        A.retrieve(j,x);
        B.insert(i,x);
    }
    Insertion_Sort_interval(B,number1,number2);
    for(int j=start,i=0;j<A.size();j+=increment,i++)
    {
        B.retrieve(i,x);
        A.replace(j,x);
    }
}

void Shell_Sort(const string &seq, int len)//ϣ������
{
    List<int> A;//�����������
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1�ǱȽϴ�����number2���ƶ�����
    string name="ϣ��";
    int incrememt=len;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    readfile(A,seq,len);//���г�ʼ��
    start_time=clock();
    do
    {
        incrememt=incrememt/3+1;
        for(int start=0;start<incrememt;start++)
        {
            Sort_interval(A,start,incrememt,number1,number2);
        }
    }while(incrememt>1);
    end_time=clock();
    //A.show();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void merge_join(List<int> &A, int bottom, int mid, int top, int &number1, int &number2)//�鲢��Ϻ���
{
    int p=bottom;
    int q=mid+1;
    int pnum,qnum;
    List<int> B;

    while(p<=mid && q<=top)
    {
        A.retrieve(p,pnum);
        A.retrieve(q,qnum);
        number1++;
        if(pnum>qnum)
        {
            B.insert(B.size(),qnum);
            q++;
            number2++;
        }
        else
        {
            B.insert(B.size(),pnum);
            p++;
            number2++;
        }
    }
    if(p==mid+1)
    {
        for(int i=q;i<=top;i++)
        {
            A.retrieve(i,qnum);
            B.insert(B.size(),qnum);
            number2++;
        }
    }
    if(q==top+1)
    {
       for(int i=p;i<=mid;i++)
        {
            A.retrieve(i,pnum);
            B.insert(B.size(),pnum);
            number2++;
        }
    }
    for(int i=bottom;i<=top;i++)
    {
        B.retrieve(i-bottom,qnum);
        A.replace(i,qnum);
    }
}

void merge_sort(List<int> &A, int bottom, int top, int &number1, int &number2)//�鲢�ݹ�
{

    if(bottom==top) return;
    int mid=(bottom+top)/2;

    merge_sort(A,bottom,mid,number1,number2);
    merge_sort(A,mid+1,top,number1,number2);
    merge_join(A,bottom,mid,top,number1,number2);
}

void Merge_Sort(const string &seq, int len)//�鲢����
{
    List<int> A;//�����������
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1�ǱȽϴ�����number2���ƶ�����
    int bottom,top;
    string name="�鲢";

    number1=number2=0;
    bottom=0;
    top=len-1;
    if(len<=0)
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    readfile(A,seq,len);//���г�ʼ��
    start_time=clock();
    merge_sort(A,bottom,top,number1,number2);
    //A.show();
    end_time=clock();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void quick_sort_divide(List<int> &A, int bottom, int top, int &mid, int &number1, int &number2)//��������ָ�
{
    int refnum;
    int tnum,bnum;
    bool judge=true;
    if(bottom>=top) return;

    mid=bottom;
    A.retrieve(mid,refnum);
    bottom=bottom+1;
    while(bottom<=top)
    {
        A.retrieve(top,tnum);
        A.retrieve(bottom,bnum);
        if(judge)
        {
            number1++;
            if(tnum<=refnum)
            {
                A.change(mid,top);
                number2++;
                mid=top;
                judge=false;
            }
            top--;
        }
        else
        {
            number1++;
            if(bnum>=refnum)
            {
                A.change(mid,bottom);
                number2++;
                mid=bottom;
                judge=true;
            }
            bottom++;
        }
    }
}

void  quick_sort(List<int> &A, int bottom, int top, int &number1, int &number2)//��������ݹ�
{
    if(bottom>=top) return;
    int mid=0;

    quick_sort_divide(A,bottom,top,mid,number1,number2);
    quick_sort(A,bottom,mid-1,number1,number2);
    quick_sort(A,mid+1,top,number1,number2);
}

void Quick_Sort(const string &seq, int len)//��������
{
    List<int> A;//�����������
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1�ǱȽϴ�����number2���ƶ�����
    string name="����";
    int bottom=0,top=len-1;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    readfile(A,seq,len);//���г�ʼ��
    start_time=clock();
    quick_sort(A,bottom,top,number1,number2);
    end_time=clock();
    //A.show();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void Insert_Heap(List<int> &A, int &current, int low, int high, int &number1, int &number2)//�ѵ���
{
    int lval,rval;
    int large=2*low+1;//��ʱ������
    while(large<=high)
    {
        if(large<high)
        {
            A.retrieve(large,lval);
            A.retrieve(large+1,rval);
            number1++;
            if(lval<rval)//�ҵ���������������
            {
                large++;
            }
        }
        A.retrieve(large,lval);//����lval��һ������
        number1++;
        if(current>=lval)
        {
            break;//�Ѿ���������
        }
        else
        {
            A.change(low,large);//�����Ҳ����׳���ʲô���⣬���������large��ֵ�ŵ�low��λ�ã�����Ͳ��ԣ�����ֱ�ӽ���ȴ����
            number2++;
            low=large;
            large=2*low+1;//��һ��������
        }
    }
    A.retrieve(low,current);
}

void build_heap(List<int> &A, int &number1, int &number2)//������ʼ��
{
    int low;
    int current;
    for(low=A.size()/2-1;low>=0;low--)//�����ȫ��������һ��Ϊ0��
    {
        A.retrieve(low,current);
        Insert_Heap(A,current,low,A.size()-1,number1,number2);
    }
}

void Heap_Sort(const string &seq, int len)//������
{
    List<int> A;//�����������
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1�ǱȽϴ�����number2���ƶ�����
    string name="��";
    int last_unsorted,current;

    number1=number2=0;
    if(len<=0#include <iostream>

int main()
{
    int x=5,y=3;
    switch(x/y)
    {
    case 0:
        cout<<"*"<<endl;
    case 1:
        cout<<"**"<<endl;
    case 2:
        cout<<"***"<<endl;
    default:
        cout<<"****"<<endl;
    }
    return 0;
})
    {
        cout<<"���г��ȴ���"<<endl;
        return;
    }
    readfile(A,seq,len);//���г�ʼ��
    start_time=clock();

    build_heap(A,number1,number2);
    for(last_unsorted=len-1;last_unsorted>0;last_unsorted--)
    {
        A.retrieve(last_unsorted,current);
        A.change(0,last_unsorted);
        number2++;
        Insert_Heap(A,current,0,last_unsorted-1,number1,number2);
    }
    end_time=clock();
    //A.show();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}


int main()
{
    List_creating();//��D������3��txt�ļ���ÿ���ļ�����1000000���������ֱ���˳���������˳��
    cout << "��������׼����ɡ�" << endl;


//��������Insertion_Sort������
    Insertion_Sort("˳��",20);
    Insertion_Sort("˳��",200);
    Insertion_Sort("˳��",2000);
    Insertion_Sort("����",20);
    Insertion_Sort("����",200);
    Insertion_Sort("����",2000);
    Insertion_Sort("���˳��",20);
    Insertion_Sort("���˳��",200);
    Insertion_Sort("���˳��",2000);

//ѡ������Selection Sort������
    Selection_Sort("˳��",20);
    Selection_Sort("˳��",200);
    Selection_Sort("˳��",2000);
    Selection_Sort("����",20);
    Selection_Sort("����",200);
    Selection_Sort("����",2000);
    Selection_Sort("���˳��",20);
    Selection_Sort("���˳��",200);
    Selection_Sort("���˳��",2000);

//ϣ������Shell Sort�����ԣ�������d=len��֮��d=d/3+1
    Shell_Sort("˳��",20);
    Shell_Sort("˳��",200);
    Shell_Sort("˳��",2000);
    Shell_Sort("����",20);
    Shell_Sort("����",200);
    Shell_Sort("����",2000);
    Shell_Sort("���˳��",7);
    Shell_Sort("���˳��",200);
    Shell_Sort("���˳��",2000);

//�鲢����Divide-and-Conquer Sorting������
    Merge_Sort("˳��",20);
    Merge_Sort("˳��",200);
    Merge_Sort("˳��",2000);
    Merge_Sort("����",20);
    Merge_Sort("����",200);
    Merge_Sort("����",2000);
    Merge_Sort("���˳��",20);
    Merge_Sort("���˳��",200);
    Merge_Sort("���˳��",2000);

//��������Quick Sort������
    Quick_Sort("˳��",20);
    Quick_Sort("˳��",200);
    Quick_Sort("˳��",2000);
    Quick_Sort("����",20);
    Quick_Sort("����",200);
    Quick_Sort("����",2000);
    Quick_Sort("���˳��",20);
    Quick_Sort("���˳��",200);
    Quick_Sort("���˳��",2000);

//������Heapsort������
    Heap_Sort("˳��",20);
    Heap_Sort("˳��",200);
    Heap_Sort("˳��",2000);
    Heap_Sort("����",20);
    Heap_Sort("����",200);
    Heap_Sort("����",2000);
    Heap_Sort("���˳��",20);
    Heap_Sort("���˳��",200);
    Heap_Sort("���˳��",2000);

    return 0;
}
