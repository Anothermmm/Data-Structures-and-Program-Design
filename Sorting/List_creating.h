//��������Ҫ�����ݲ��ұ������ļ���
#ifndef LIST_CREATING_H_INCLUDED
#define LIST_CREATING_H_INCLUDED

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

void List_creating()
{
    string order,path,filename;
    char judge='y';

    while(judge=='y')
    {
        cout<<"\n����˳����������˳��";
        cin>>order;

        if(order=="˳��")
        {
            path="D:\\";
            filename="˳��.txt";
            path+=filename;
            ofstream fout(path.c_str());

            cout<<"��ʼ��������......"<<endl;
            if(fout.good())
            {
                for(int i=0; i<1000000; i++)
                {
                    fout<<i<<" ";
                }
                fout.close();
                cout<<"���ɳɹ���"<<endl;
            }
            else
            {
                cout<<"����ʧ�ܣ�"<<endl;
                exit(0);
            }
        }
        else if(order=="����")
        {
            path="D:\\";
            filename="����.txt";
            path+=filename;
            ofstream fout(path.c_str());

            cout<<"��ʼ��������......"<<endl;
            if(fout.good())
            {
                for(int i=1000000; i>0; i--)
                {
                    fout<<i<<" ";
                }
                fout.close();
                cout<<"���ɳɹ���"<<endl;
            }
            else
            {
                cout<<"����ʧ�ܣ�"<<endl;
                exit(0);
            }
        }
        else if(order=="���" || order=="���˳��")
        {
            path="D:\\";
            filename="���˳��.txt";
            path+=filename;
            ofstream fout(path.c_str());

            cout<<"��ʼ��������......"<<endl;
            if(fout.good())
            {
                srand(time(NULL));
                for(int i=1000000; i>0; i--)
                {
                    fout<<rand()<<" ";
                }
                fout.close();
                cout<<"���ɳɹ���"<<endl;
            }
            else
            {
                cout<<"����ʧ�ܣ�"<<endl;
                exit(0);
            }
        }
        cout<<"�Ƿ�����������ݣ���y/n��";
        cin>>judge;
        cout<<endl;
    }
}



#endif // LIST_CREATING_H_INCLUDED
