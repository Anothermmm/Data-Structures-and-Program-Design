#include "utility.h"
#include "Single_Linked_List.h"

using namespace std;

class Entry//������һ����¼
{
private:
    string date;
    string proj;
    double cost;
public:
    Entry(string Date=" ", string Proj=" ", double Cost=0.00);
    void operator=(Entry copy);
    void show();//�������
    string getdate()const{return date;}//get����
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

void readfile(List<Entry> &A, const string &path)//���ļ������¼
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
    List<Entry> A;//A��node����List_entry��Entry
    double maxnum=-1,minnum=-1,avenum=-1;
    double total1,cost2,total2;

    readfile(A,"D:\\data.txt");//���ļ��е����������γ�A����
    A.showall();//�����������
    A.findmincost(minnum);//��С��cost����minnum
    A.findmaxcost(maxnum);//����cost����maxnum
    A.findavercost(avenum);//ƽ��cost
    A.one_day_cost(total1,"10��2��");//10��2��һ��Ļ���
    A.day_and_proj_find_cost(cost2,"10��2��","������");//һ���һ����Ŀ�Ļ���
    A.one_proj_cost(total2,"���緹");//һ����Ŀ���еĻ���
    cout<<"��Сֵ��"<<minnum<<endl;
    cout<<"���ֵ��"<<maxnum<<endl;
    cout<<"ƽ��ֵ��"<<avenum<<endl;
    cout<<"10��2�����л��ѣ�"<<total1<<endl;
    cout<<"10��2�ձ����ѣ�"<<cost2<<endl;
    cout<<"���緹���ƣ�"<<total2<<endl;
    return 0;
}
