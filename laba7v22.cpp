#include <iostream>
#include <string>
#include <Windows.h>
#include <locale.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

using namespace std;

class Exception
{
protected:
	int error;
public:
	Exception()
	{
		error = 0;
	}
	Exception(int err)
	{
		error = err;
	}
	~Exception()
	{

	};
	void Print()
	{
		if (this->error == 1)
		{
			cout << "Error! (only int)" << endl;
		}
		if (this->error == 2)
		{
			cout << "Error! (only double)" << endl;
		}if (this->error == 4)
		{
			cout << "Error! " << endl;
		}
	}
};

template<typename T>
class Node
{
public:
	Node<T>* pNext;
	T data;
	Node(T data = T(), Node* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
	T get_data() {
		return data;
	}
};

template<typename T>
class Iterator : public Node<T>
{
	Node<T>* pointer;
	friend class automobile;
public:
	Iterator()
	{
		this->pointer = nullptr;
	}
	Iterator(Node<T>* element)
	{
		this->pointer = element;
	}
	~Iterator()
	{
		this->pointer = nullptr;
	}
	Iterator operator+(int n)
	{
		return *(pointer + n);
	}
	Iterator operator++(int n)
	{
		return *pointer++;
	}
	Iterator operator*()
	{
		return *pointer;
	}
	bool operator!= (const Iterator& it)
	{
		return pointer != it.pointer;
	}
};


template<typename T>
class Stack :public Node<T>
{
public:
	Stack();
	~Stack();
	void pop();
	void clear();
	int GetSize()
	{
		return Size;
	}
	T& operator[](const int index);
	void push(T data);
	Iterator<T> begin()
	{
		return (this->head);
	}
	Iterator<T> end()
	{
		Node<T>* current = this->head;
		for (int i = 0; i < Size; i++)
		{
			current = current->pNext;
		}
		return current;
	}
private:
	int Size;
	Node<T>* head;
	friend ostream& operator<<(ostream& out, const Node<T>& node);
};

/////////////////////////////////////////////////////////////////
class schoolboy {
	int id;
	string name;
	int missed;
public:
	schoolboy() { // конструктор по умолчанию
		missed = 0;
		id = 0;
		name = " - ";
	}
	schoolboy(int id1, string name1, int missed1) { // конструктор инициализации
		id = id1;
		name = name1;
		missed = missed1;
	}

	void print() {
		cout << "Id - " << this->id << endl;
		cout << "Количество пропусков - " << this->missed << endl;
		cout << "Имя - " << this->name << endl;
	}

	~schoolboy() {};
	friend class Stack<schoolboy>;
	friend void input(schoolboy& sch);
	friend void set(int id, int missed, string name, schoolboy& sch);

};

void set(int id, int missed, string name, schoolboy& sch) {
	sch.id = id;
	sch.missed = missed;
	sch.name = name;
}

void input(schoolboy& sch) {
	int id,missed;
	string name;
	
	cout << "Введите id: \n";
	try
	{
		cin >>id;
		if (cin.fail())
		{
			throw 1;
		}
		
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
		cout << "Error!\n";
		
	}
	
	
		cout << "Введите количество пропусков: ";
		try
		{
			cin >> missed;
			if (cin.fail())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			cout << "Error!\n";
			
		}
	
	cout << "Введите имя школьника - "<<endl;
	cin >> name;

	set(id,missed, name, sch);
};


////////////////////////////////////////////////////////////////

template<typename T>
Stack<T>::Stack()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
Stack<T>::~Stack()
{
	clear();
}

template<typename T>
void Stack<T>::pop()
{
	try
	{
		if (Size == 0)
		{
			throw 4;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
		return;
	}
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

template<typename T>
void Stack<T>::clear()
{
	while (Size)
	{
		pop();
	}
}

template<typename T>
T& Stack<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void Stack<T>::push(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void Sort(int n, T* ms)
{
	int j;
	T m;
	for (int i = 1; i < n; ++i)
	{
		j = i - 1;
		m = ms[i];
		while (j >= 0 && m < ms[j])
		{
			ms[j-- + 1] = ms[j];
		}
		ms[j + 1] = m;
	}
}
///////////////////////////



template<typename T>
ostream& operator<<(ostream& out, const Node<T>& node)
{
	out << node.data;
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const Iterator<T>& it)
{
	out << *it;
	return out;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
		
			Stack<int> stackint;
			int n;
			int* value1;
			cout << "Введите количество элементов (int stack): " << endl;
			try
			{
				cin >> n;
				if (cin.fail())
				{
					throw 1;
				}
			}
			catch (int i)
			{
				Exception ex(i);
				ex.Print();
				return 0;
			}
			value1 = new int[n];
			cout << "Введите значения (int) в stuck: " << endl;
			for (int i = 0; i < n; i++)
			{
				try
				{
					cin >> value1[i];
					if (cin.fail())
					{
						throw 1;
					}
				}
				catch (int i)
				{
					Exception ex(i);
					ex.Print();
					return 0;
				}
				stackint.push(value1[i]);
			}
			Iterator<int> it1(stackint.begin());
			cout << "Стэк (int): " << endl;
			for (int i = 0; i < stackint.GetSize(); i++)
			{
				cout << stackint[i] << endl;
			}
			cout << "Сортировка вставками:" << endl;
			Sort(n, value1);
			stackint.clear();
			for (int i = 0; i < n; i++)
			{
				stackint.push(value1[i]);
			}
			
			for (int i = 0; i < n; i++)
			{
				cout << stackint[i] << "  ";
			}
			cout << endl;
			cout << "Удаление элемента из стэка!\n";
			stackint.pop();
			cout << "Стэк: " << endl;
			for (int i = 0; i < stackint.GetSize(); i++)
			{
				cout << stackint[i] << "  ";
			}
			cout << endl;

			cout << "Добавьте элемент в стэк" << endl;
			int temp;
			try
			{
				cin >> temp;
				if (cin.fail())
				{
					throw 1;
				}
			}
			catch (int i)
			{
				Exception ex(i);
				ex.Print();
				return 0;
			}
			stackint.push(temp);
			cout << "Стэк: " << endl;
			for (int i = 0; i < stackint.GetSize(); i++)
			{
				cout << stackint[i] << endl;
			}
			delete[] value1;
			/////////////////////////////////////////////////////
		

			Stack<double> stackdb;
			double* value2;
			cout << "Введите количество элементов(double stack): " << endl;
			try
			{
				cin >> n;
				if (cin.fail())
				{
					throw 1;
				}
			}
			catch (int i)
			{
				Exception ex(i);
				ex.Print();
				return 0;
			}
			value2 = new double[n];
			cout << "Введите значения (double) в stuck: " << endl;
			for (int i = 0; i < n; i++)
			{
				try
				{
					cin >> value2[i];
					if (cin.fail())
					{
						throw 2;
					}
				}
				catch (int i)
				{
					Exception ex(i);
					ex.Print();
					return 0;
				}
				stackdb.push(value2[i]);
			}
			Iterator<double> it2(stackdb.begin());
			cout << "Стэк: " << endl;
			for (int i = 0; i < stackdb.GetSize(); i++)
			{
				cout << stackdb[i] << endl;
			}
			
			cout << "Удаление элемента из стэка!\n";
			stackdb.pop();
			cout << "Cтэк:" << endl;
			for (int i = 0; i < stackdb.GetSize(); i++)
			{
				cout << stackdb[i] << "  ";
			}
			cout << " " << endl;
			cout << "Добавьте элемент в стэк" << endl;
			double tempdb;
			try
			{
				cin >> tempdb;
				if (cin.fail())
				{
					throw 2;
				}
			}
			catch (int i)
			{
				Exception ex(i);
				ex.Print();
				return 0;
			}
			stackdb.push(tempdb);
			cout << "Стэк: " << endl;
			for (int i = 0; i < stackdb.GetSize(); i++)
			{
				cout << stackdb[i] << endl;
			}
			delete[] value2;
			///////////////////////////////

			Stack<char> stackchar;
			char* value3;
			cout << "Введите количество элементов (char stack): " << endl;
			try
			{
				cin >> n;
				if (cin.fail())
				{
					throw 1;
				}
			}
			catch (int i)
			{
				Exception ex(i);
				ex.Print();
				return 0;
			}
			value3 = new char[n];
			cout << "Введите значения (char) в stuck: " << endl;
			for (int i = 0; i < n; i++)
			{
				cin >> value3[i];
				stackchar.push(value3[i]);
			}
			
			
			cout << "Стэк: " << endl;
			for (int i = 0; i < stackchar.GetSize(); i++)
			{
				cout << stackchar[i] << endl;
			}
			cout << "Сортировка вставками:" << endl;
			Sort(n, value3);
			stackchar.clear();
			for (int i = 0; i < n; i++)
			{
				stackchar.push(value3[i]);
			}

			for (int i = 0; i < n; i++)
			{
				cout << stackchar[i] << "  ";
			}
			cout << endl;
			cout << "Удаление элемента из стэка!\n";
			stackchar.pop();
			cout << "Стэк: " << endl;
			for (int i = 0; i < stackchar.GetSize(); i++)
			{
				cout << stackchar[i] << "  ";
			}
			cout << " " << endl;
			cout << "Добавьте элемент в стэк" << endl;
			char tempch;
			cin >> tempch;
			stackchar.push(tempch);
			cout << "Стэк : " << endl;
			for (int i = 0; i < stackchar.GetSize(); i++)
			{
				cout << stackchar[i] << endl;
			}
			delete[] value3;
			///////////////////////
		
		
			Stack<schoolboy> sch;
			cout << "Введите количество элементов: " << endl;
			try
			{
				cin >> n;
				if (cin.fail())
				{
					throw 1;
				}
			}
			catch (int i)
			{
				Exception ex(i);
				ex.Print();
				return 0;
			}
			schoolboy* value4 = new schoolboy[n];
			for (int i = 0; i < n; i++) {
				cout << "Введите данные школьника\n";
				input(value4[i]);
				sch.push(value4[i]);
			}
			Iterator<schoolboy> it4(sch.begin());
			cout << "Стэк : " << endl;
			for (int i = 0; i < sch.GetSize(); i++)
			{
				sch[i].print();
			}

			cout << "Удаление элемента из стэка!\n";
			sch.pop();
			cout << "Стэк: " << endl;
			for (int i = 0; i < sch.GetSize(); i++)
			{
				sch[i].print();
			}
			cout << " " << endl;
			cout << "Добавьте элемент в стэк" << endl;
			cout << "Введите данные школьника\n";
			input(value4[0]);
			
			sch.push(value4[0]);
			cout << "Стэк : " << endl;
			for (int i = 0; i < sch.GetSize(); i++)
			{
				sch[i].print();
			}

			delete[] value4;
	return 0;
}