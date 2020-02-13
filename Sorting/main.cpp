//用九组数据分别测试插入排序（Insertion Sort）、选择排序（Selection Sort）、希尔排序（Shell Sort）、
//归并排序（Mergesort）、快速排序（Quick Sort）、堆排序（Heapsort）
//的运行时间、比较次数、移动次数，采用顺序结构
#include <iostream>
#include "List_creating.h"
#include "List.h"
#include <ctime>

using namespace std;

void readfile(List<int> &p, const string &seq, int len)//从对应的txt文件里初始化待排序的序列
{
    int x;
    string path="D:\\";
    string filename;

    if(seq=="顺序") filename="顺序.txt";
    else if(seq=="逆序") filename="逆序.txt";
    else filename="随机顺序.txt";
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

void print(const string &seq, const string &name, int len, int number1, int number2, double totaltime)//将一条结果输出
{
    cout<<name<<"排序测试长度为"<<len<<"的"<<seq<<"表的比较次数为"<<number1<<"\n"<<"移动次数为"<<number2<<"\n"<<"排序时间为";
    cout<<totaltime<<'s'<<endl<<endl;
}

void Insertion_Sort(const string &seq, int len)//插入排序
{
    List<int> A;//待排序的序列
    clock_t start_time,end_time;
    string name="插入";
    double totaltime;
    int number1,number2;//number1是比较次数，number2是移动次数
    int i,temp;
    int current,previous;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"序列长度错误！"<<endl;
        return;
    }
    readfile(A,seq,len);//序列初始化
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

void Selection_Sort(const string &seq, int len)//选择排序
{
    List<int> A;//待排序的序列
    clock_t start_time,end_time;
    int totaltime;//总时间
    int number1,number2;//number1是比较次数，number2是移动次数
    string name="选择";
    int maxentry,current,currentnum;
    int top=len;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"序列长度错误！"<<endl;
        return;
    }
    readfile(A,seq,len);//序列初始化
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

void Insertion_Sort_interval(List<int> &A, int &number1, int &number2)//重写插入排序
{
    int current,previous;
    int i,temp;

    if(A.size()<=0)
    {
        cout<<"序列长度错误！"<<endl;
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

void Sort_interval(List<int> &A, int start, int increment, int &number1, int &number2)//希尔排序内排序
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

void Shell_Sort(const string &seq, int len)//希尔排序
{
    List<int> A;//待排序的序列
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1是比较次数，number2是移动次数
    string name="希尔";
    int incrememt=len;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"序列长度错误！"<<endl;
        return;
    }
    readfile(A,seq,len);//序列初始化
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

void merge_join(List<int> &A, int bottom, int mid, int top, int &number1, int &number2)//归并结合函数
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

void merge_sort(List<int> &A, int bottom, int top, int &number1, int &number2)//归并递归
{

    if(bottom==top) return;
    int mid=(bottom+top)/2;

    merge_sort(A,bottom,mid,number1,number2);
    merge_sort(A,mid+1,top,number1,number2);
    merge_join(A,bottom,mid,top,number1,number2);
}

void Merge_Sort(const string &seq, int len)//归并排序
{
    List<int> A;//待排序的序列
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1是比较次数，number2是移动次数
    int bottom,top;
    string name="归并";

    number1=number2=0;
    bottom=0;
    top=len-1;
    if(len<=0)
    {
        cout<<"序列长度错误！"<<endl;
        return;
    }
    readfile(A,seq,len);//序列初始化
    start_time=clock();
    merge_sort(A,bottom,top,number1,number2);
    //A.show();
    end_time=clock();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void quick_sort_divide(List<int> &A, int bottom, int top, int &mid, int &number1, int &number2)//快速排序分割
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

void  quick_sort(List<int> &A, int bottom, int top, int &number1, int &number2)//快速排序递归
{
    if(bottom>=top) return;
    int mid=0;

    quick_sort_divide(A,bottom,top,mid,number1,number2);
    quick_sort(A,bottom,mid-1,number1,number2);
    quick_sort(A,mid+1,top,number1,number2);
}

void Quick_Sort(const string &seq, int len)//快速排序
{
    List<int> A;//待排序的序列
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1是比较次数，number2是移动次数
    string name="快速";
    int bottom=0,top=len-1;

    number1=number2=0;
    if(len<=0)
    {
        cout<<"序列长度错误！"<<endl;
        return;
    }
    readfile(A,seq,len);//序列初始化
    start_time=clock();
    quick_sort(A,bottom,top,number1,number2);
    end_time=clock();
    //A.show();
    totaltime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    print(seq,name,len,number1,number2,totaltime);
}

void Insert_Heap(List<int> &A, int &current, int low, int high, int &number1, int &number2)//堆调整
{
    int lval,rval;
    int large=2*low+1;//暂时左子树
    while(large<=high)
    {
        if(large<high)
        {
            A.retrieve(large,lval);
            A.retrieve(large+1,rval);
            number1++;
            if(lval<rval)//找到左右子树中最大的
            {
                large++;
            }
        }
        A.retrieve(large,lval);//借用lval放一下最大的
        number1++;
        if(current>=lval)
        {
            break;//已经满足大根堆
        }
        else
        {
            A.change(low,large);//这里我不明白出了什么问题，如果仅仅把large的值放到low的位置，结果就不对，但是直接交换却可以
            number2++;
            low=large;
            large=2*low+1;//下一个左子树
        }
    }
    A.retrieve(low,current);
}

void build_heap(List<int> &A, int &number1, int &number2)//构建初始堆
{
    int low;
    int current;
    for(low=A.size()/2-1;low>=0;low--)//这棵完全二叉树第一层为0号
    {
        A.retrieve(low,current);
        Insert_Heap(A,current,low,A.size()-1,number1,number2);
    }
}

void Heap_Sort(const string &seq, int len)//堆排序
{
    List<int> A;//待排序的序列
    clock_t start_time,end_time;
    int totaltime;
    int number1,number2;//number1是比较次数，number2是移动次数
    string name="堆";
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
        cout<<"序列长度错误！"<<endl;
        return;
    }
    readfile(A,seq,len);//序列初始化
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
    List_creating();//在D盘生成3个txt文件，每个文件保存1000000个整数，分别是顺序，逆序，随机顺序
    cout << "所有数据准备完成。" << endl;


//插入排序（Insertion_Sort）测试
    Insertion_Sort("顺序",20);
    Insertion_Sort("顺序",200);
    Insertion_Sort("顺序",2000);
    Insertion_Sort("逆序",20);
    Insertion_Sort("逆序",200);
    Insertion_Sort("逆序",2000);
    Insertion_Sort("随机顺序",20);
    Insertion_Sort("随机顺序",200);
    Insertion_Sort("随机顺序",2000);

//选择排序（Selection Sort）测试
    Selection_Sort("顺序",20);
    Selection_Sort("顺序",200);
    Selection_Sort("顺序",2000);
    Selection_Sort("逆序",20);
    Selection_Sort("逆序",200);
    Selection_Sort("逆序",2000);
    Selection_Sort("随机顺序",20);
    Selection_Sort("随机顺序",200);
    Selection_Sort("随机顺序",2000);

//希尔排序（Shell Sort）测试，设增量d=len，之后d=d/3+1
    Shell_Sort("顺序",20);
    Shell_Sort("顺序",200);
    Shell_Sort("顺序",2000);
    Shell_Sort("逆序",20);
    Shell_Sort("逆序",200);
    Shell_Sort("逆序",2000);
    Shell_Sort("随机顺序",7);
    Shell_Sort("随机顺序",200);
    Shell_Sort("随机顺序",2000);

//归并排序（Divide-and-Conquer Sorting）测试
    Merge_Sort("顺序",20);
    Merge_Sort("顺序",200);
    Merge_Sort("顺序",2000);
    Merge_Sort("逆序",20);
    Merge_Sort("逆序",200);
    Merge_Sort("逆序",2000);
    Merge_Sort("随机顺序",20);
    Merge_Sort("随机顺序",200);
    Merge_Sort("随机顺序",2000);

//快速排序（Quick Sort）测试
    Quick_Sort("顺序",20);
    Quick_Sort("顺序",200);
    Quick_Sort("顺序",2000);
    Quick_Sort("逆序",20);
    Quick_Sort("逆序",200);
    Quick_Sort("逆序",2000);
    Quick_Sort("随机顺序",20);
    Quick_Sort("随机顺序",200);
    Quick_Sort("随机顺序",2000);

//堆排序（Heapsort）测试
    Heap_Sort("顺序",20);
    Heap_Sort("顺序",200);
    Heap_Sort("顺序",2000);
    Heap_Sort("逆序",20);
    Heap_Sort("逆序",200);
    Heap_Sort("逆序",2000);
    Heap_Sort("随机顺序",20);
    Heap_Sort("随机顺序",200);
    Heap_Sort("随机顺序",2000);

    return 0;
}
