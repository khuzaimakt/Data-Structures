#include<iostream>
#include<string>
using namespace std;

#define max 10

template<typename T>
class Node
{
	T data;
	Node<T>* next;

public:
	template<typename T>
	friend class SLinked;
	template<typename T>
	friend class Stack;

	Node(T data = 0, Node<T>* next = nullptr) :data(data), next(next) {};
	
};


template<typename T>
class SLinked
{
	Node<T>* head;
	int size;
	

public:
	template<typename T>
	friend class Stack;
	SLinked()
	{
		head = nullptr;
	}
	
	

};


template<typename T>
class Stack
{
	SLinked<T>* S;

public:
	Stack()
	{
		S = new SLinked<T>();
	}
	int size()
	{
		return S->size;
	}

	bool isempty()
	{
		if (S->head == nullptr)
		{
			return true;
		}
		else
			return false;
	}

	bool top(T& t)
	{
		if (S->head == nullptr)
		{
			return false;
		}

		else
		{
			t = S->head->data;
			return true;
		}
	}
	void pop()
	{
		if (!s->head)
			cout << "stack is empty" << endl;
		else
			node<t>* temp = s->head->next;
		delete head;
		s->head = temp;

		size--;
	}

	void push(t const& e)
	{
		node<t>* t = new node<t>(e);
		if (isempty())
		{
			s->head = t;
		}
		else
		{
			t->next = s->head;
			s->head = t;
		}
		s->size++;
	}

	void print()
	{
		if (isempty())
		{
			cout << "stack is empty" << endl;
		}

		for (node<t>* t = s->head; t != nullptr; t = t->next)
		{
			cout << t->data << " " << endl;
		}
	}

	bool isbalance(string exp)
	{
		stack<char> s;
		char t;
		int i = 0;
		while (i<exp.size())
		{
			if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			{
				s.push(exp[i]);
			}

			if (exp[i] == '}' || exp[i] == ']' || exp[i] == ')')
			{
				s.top(t);
				if (s.isempty())
				{
					return false;
				}
				else
				{
					s.pop();
				}
				
			}
			i++;
		}
		return s.isempty();
	}
	
	
	string reverse(string const str) {
		stack<char> s;
		for (int i = 0; i < str.size(); i++)
			s.push(str[i]);

		string newstr;
		char temp;
		while (s.top(temp)) {
			newstr += temp;
			s.pop();
		}

		return newstr;
	}

};


template<typename T>
class Queue
{
	T a[max];
	int size;
	int front;


public:
	Queue()
	{
		size = 0;
		front = 0;
	}
	

	bool qfront(T& t)
	{
		if (size == 0)
		{
			return false;
		}
		else
		{
			t = a[front];
		}
	}

	void dequeue()
	{
		if (size==0)
		{
			cout << "Queue is empty" << endl;
			return;
		}
 	    front = (front + 1) % max;
		size--;

	}

	void enqueue(T const& t)
	{
		if (size == max)
		{
			cout << "Queue is full" << endl;
			return;
		}

 	 a[(front + size) % max] = t;
	    size++;
	}

};
