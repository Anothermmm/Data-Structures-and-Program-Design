//逆波兰计算器程序
typedef double Stack_entry;
#include "Stack.h"
#include <iostream>

using namespace std;


void introduction()
{
	cout << "启动逆波兰计算器程序。" << endl;
}

void instruction()
{
	cout << "输入一个合法的后缀表达式。运算数和运算数、"<<endl;
	cout<<"运算数和运算符间用问号（?）隔开，即一个数的前面必有一个？" << endl;
	cout<<"另外的运算符为+、-、*、/、q(表示结束)"<<endl;
}

char get_command()//直到得到一个合法的字符输入，并将其输出
{
	char command;
	bool waiting = true;

	cout << "Select command and press < Enter > :" << endl;
	while (waiting)
	{
		cin >> command;
		command = tolower(command);
		if (command == '?' || command == '+' || command == '_' ||
			command == '*' || command == '/' || command == '=' || command == 'q')
			waiting = false;
		else
		{
			cout << "Please enter a valid command:" << endl;
		}
	}
	waiting = true;
	return command;
}

bool do_commamd(char command, Stack& numbers)//接受一个指令和自定义栈
{
	double p,q;
	bool waiting=true;

	switch (command)
	{
	case'?':
	    waiting=true;
	    while(waiting)//如果没有输入正确的实数就循环输入
        {
            cout << "Enter a real number:" << endl;
            cin >> p;
            if(cin.good())
            {
                if (numbers.push(p) == overflow)
                {
                    cout << "Stack full. Exit." <<endl;
                    break;
                }
                waiting=false;
            }
            else
            {
                cin.clear();
                cin.ignore();
            }
        }
		break;
	case'='://出栈顶元素
		if (numbers.top(p) == underflow)
			cout << "Stack empty." << endl;
		else
			cout<<"The result is:" << p << endl;
        break;
	case'+':
		if (numbers.top(p) == underflow)
			cout << "Stack empty." << endl;
		else
		{
			numbers.pop();
			if (numbers.top(q) == underflow)
			{
				cout << "Stack empty." << endl;
				numbers.push(p);
			}
			else
			{
				numbers.pop();
				if (numbers.push(p + q) == overflow)
					cout << "Stack full." << endl;
			}
		}
		break;
	case'-':
		if (numbers.top(p) == underflow)
			cout << "Stack empty." << endl;
		else
		{
			numbers.pop();
			if (numbers.top(q) == underflow)
			{
				cout << "Stack empty." << endl;
				numbers.push(p);
			}
			else
			{
				numbers.pop();
				if (numbers.push(q - p) == overflow)
					cout << "Stack full." << endl;
			}
		}
		break;
	case'*':
		if (numbers.top(p) == underflow)
			cout << "Stack empty." << endl;
		else
		{
			numbers.pop();
			if (numbers.top(q) == underflow)
			{
				cout << "Stack empty." << endl;
				numbers.push(p);
			}
			else
			{
				numbers.pop();
				if (numbers.push(p * q) == overflow)
					cout << "Stack full." << endl;
			}
		}
		break;
	case'/':
		if (numbers.top(p) == underflow)
			cout << "Stack empty." << endl;
		else
		{
			numbers.pop();
			if (numbers.top(q) == underflow)
			{
				cout << "Stack empty." << endl;
				numbers.push(p);
			}
			else
			{
				numbers.pop();
				if (numbers.push(q / p) == overflow)
					cout << "Stack full." << endl;
			}
		}
		break;
	case'q':
		cout << "Calculation finished.\n";
		return false;
	}
	return true;
}

int main()
{
	Stack stored_numbers;//新建自定义栈
	introduction();
	instruction();
	while (do_commamd(get_command(), stored_numbers));
	return 0;
}
