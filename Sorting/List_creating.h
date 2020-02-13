//生成所需要的数据并且保存在文件里
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
        cout<<"\n输入顺序、逆序或随机顺序：";
        cin>>order;

        if(order=="顺序")
        {
            path="D:\\";
            filename="顺序.txt";
            path+=filename;
            ofstream fout(path.c_str());

            cout<<"开始生成数据......"<<endl;
            if(fout.good())
            {
                for(int i=0; i<1000000; i++)
                {
                    fout<<i<<" ";
                }
                fout.close();
                cout<<"生成成功！"<<endl;
            }
            else
            {
                cout<<"生成失败！"<<endl;
                exit(0);
            }
        }
        else if(order=="逆序")
        {
            path="D:\\";
            filename="逆序.txt";
            path+=filename;
            ofstream fout(path.c_str());

            cout<<"开始生成数据......"<<endl;
            if(fout.good())
            {
                for(int i=1000000; i>0; i--)
                {
                    fout<<i<<" ";
                }
                fout.close();
                cout<<"生成成功！"<<endl;
            }
            else
            {
                cout<<"生成失败！"<<endl;
                exit(0);
            }
        }
        else if(order=="随机" || order=="随机顺序")
        {
            path="D:\\";
            filename="随机顺序.txt";
            path+=filename;
            ofstream fout(path.c_str());

            cout<<"开始生成数据......"<<endl;
            if(fout.good())
            {
                srand(time(NULL));
                for(int i=1000000; i>0; i--)
                {
                    fout<<rand()<<" ";
                }
                fout.close();
                cout<<"生成成功！"<<endl;
            }
            else
            {
                cout<<"生成失败！"<<endl;
                exit(0);
            }
        }
        cout<<"是否继续生成数据？（y/n）";
        cin>>judge;
        cout<<endl;
    }
}



#endif // LIST_CREATING_H_INCLUDED
