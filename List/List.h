#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

enum Error_code{success,fail,overflow,underflow,Range_error};
const int max_list = 100000;
using namespace std;

template<class List_entry>
class List
{
public:
	List();
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void(*visit)(List_entry&));//����������performing a given operation on each entry.
	Error_code retrieve(int position, List_entry& x)const;//���Ҳ�����λ��position���±��÷�
	Error_code remove(int position, List_entry& x);//�Ƴ�����
	Error_code replace(int position, const List_entry& x);//�滻����
	Error_code insert(int position, const List_entry& x);//�������
private:
	int count;//the number of List_entry�ܸ���
	List_entry entry[max_list];
};

template<class List_entry> List<List_entry>::List()
{
	count = 0;
}

template<class List_entry> int List<List_entry>::size()const
{
	return count;
}

template<class List_entry> bool List<List_entry>::full()const
{
	if (count == max_list) return true;
	else return false;
}

template<class List_entry> bool List<List_entry>::empty()const
{
	if (count == 0) return true;
	else return false;
}

template<class List_entry> void List<List_entry>::clear()
{
	count = 0;
}

template<class List_entry> void List<List_entry>::traverse(void(*visit)(List_entry&))//the parameter is a function
{
	for(int i = 0; i < count; i++)
	{
		(*visit)(entry[i]);//����Ķ�ÿ��entry[i]�Ĳ���Ҫ��visit����ĺ���
	}
}

template<class List_entry> Error_code List<List_entry>::retrieve(int position, List_entry& x)const
{
	if (position < 0 || position >= count) return Range_error;
	x = entry[position];
	return success;
}

template<class List_entry> Error_code List<List_entry>::insert(int position, const List_entry& x)
{
	if (full()) return overflow;
	if (position<0 || position>count) return Range_error;
	for (int i = count - 1; i >= position; i++)
	{
		entry[i + 1] = entry[i];
	}
	entry[position] = x;
	count++;
	return success;
}

template<class List_entry> Error_code List<List_entry>::remove(int position, List_entry& x)
{
	if (empty()) return underflow;
	if (position < 0 || position >= count) return Range_error;
	x = entry[position];
	for (int i = position; i < count; i++)
	{
		entry[i] = entry[i + 1];
	}
	count--;
	return success;
}

template<class List_entry> Error_code List<List_entry>::replace(int position, const List_entry& x)
{
	if (position < 0 || position >= count) return Range_error;
	entry[position]=x;
	return success;
}

#endif // LIST_H_INCLUDED
