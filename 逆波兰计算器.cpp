//�沨������������
typedef double Stack_entry;
#include "Stack.h"
#include <iostream>

using namespace std;


void introduction()
{
	cout << "�����沨������������" << endl;
}

void instruction()
{
	cout << "����һ���Ϸ��ĺ�׺���ʽ������������������"<<endl;
	cout<<"������������������ʺţ�?����������һ������ǰ�����һ����" << endl;
	cout<<"����������Ϊ+��-��*��/��q(��ʾ����)"<<endl;
}

char get_command()//ֱ���õ�һ���Ϸ����ַ����룬���������
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

bool do_commamd(char command, Stack& numbers)//����һ��ָ����Զ���ջ
{
	double p,q;
	bool waiting=true;

	switch (command)
	{
	case'?':
	    waiting=true;
	    while(waiting)//���û��������ȷ��ʵ����ѭ������
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
	case'='://��ջ��Ԫ��
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
	Stack stored_numbers;//�½��Զ���ջ
	introduction();
	instruction();
	while (do_commamd(get_command(), stored_numbers));
	return 0;
}
