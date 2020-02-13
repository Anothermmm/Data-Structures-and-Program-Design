#include "utility.h"
#include "Single_Linked_List.h"

using namespace std;

class Entry//定义了一条记录
{
private:
    string date;
    string proj;
    double cost;
public:
    Entry(string Date=" ", string Proj=" ", double Cost=0.00);
    void operator=(Entry copy);
    void show();//输出数据
    string getdate()const{return date;}//get数据
    string getproj()const{return proj;}
    double getcost()const{return cost;}
};

Entry::Entry(string Date, string Proj, double Cost)
{
    date=Date;
    proj=Proj;
    cost=Cost;
}

void Entry::operator=(Entry copy)
{
    cost=copy.cost;
    date=copy.date;
    proj=copy.proj;
}

void Entry::show()
{
    cout<<"date:"<<getdate()<<"  project:"<<getproj()<<"  cost:"<<getcost()<<endl;
    cout<<endl;
}

void readfile(List<Entry> &A, const string &path)//从文件里读记录
{
    ifstream fin(path.c_str());
    string date,proj,Cost;
    double cost;

    A.clear();
    if(fin.good())
    {
        fin>>date>>proj>>Cost;
        while(fin>>date>>proj>>cost)
        {
            Entry temp(date,proj,cost);
            A.append(temp);
        }
        fin.close();
    }
    else
    {
        cout<<"Readfile Error!"<<endl;
        exit(0);
    }
}


int main()
{
    List<Entry> A;//A是node链，List_entry是Entry
    double maxnum=-1,minnum=-1,avenum=-1;
    double total1,cost2,total2;

    readfile(A,"D:\\data.txt");//将文件中的所有数据形成A链表
    A.showall();//输出所有数据
    A.findmincost(minnum);//最小的cost赋给minnum
    A.findmaxcost(maxnum);//最大的cost赋给maxnum
    A.findavercost(avenum);//平均cost
    A.one_day_cost(total1,"10月2日");//10月2日一天的花费
    A.day_and_proj_find_cost(cost2,"10月2日","报名费");//一天的一个项目的花费
    A.one_proj_cost(total2,"吃午饭");//一个项目所有的花费
    cout<<"最小值："<<minnum<<endl;
    cout<<"最大值："<<maxnum<<endl;
    cout<<"平均值："<<avenum<<endl;
    cout<<"10月2日所有花费："<<total1<<endl;
    cout<<"10月2日报名费："<<cost2<<endl;
    cout<<"吃午饭共计："<<total2<<endl;
    return 0;
}
