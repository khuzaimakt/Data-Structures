#include<iostream>
using namespace std;

template<typename T>
class Node
{
	T data;
	Node<T>* next;

public:
	template<typename T>
	friend class CircularLinked;

	Node(T data = 0, Node<T>* next = nullptr) :data(data), next(next) {};

};


template<typename T>
class CircularLinked
{
	Node<T>* tail;



public:
	CircularLinked()
	{
		tail = nullptr;
	}
	void insertatstart(T const e)
	{
		Node<T>* t = new Node<T>(e);
		if (!tail)
		{
			tail = t;
			tail->next = t;
		}
		else
		{
			t->next = tail->next;
			tail->next = t;
		}
	}

	void insertatend(T const e)
	{
		Node<T>* t = new Node<T>(e);

		if (tail)
		{
			t->next = tail->next;
			tail->next = t;
			tail = t;
		}
		if (!tail)
		{
			tail = t;
			tail->next = tail;
		}

	}

	void print()const
	{
		if (!tail)
			return;
		Node<T>* t = tail->next;
		cout << t->data << " ";
		t = t->next;
		for (t; t != tail->next; t = t->next)
		{
			cout << t->data << " ";
		}
		cout << endl;

	}


	void insertafter(T const v1, T const v2)
	{
		if (!tail)
			return;

		Node<T>* t = tail->next;

		if (tail)
		{
			if (tail->data == v1)
			{
				Node<T>* T2 = new Node<T>(v2, tail->next);
				tail->next = T2;
				return;
			}
			for (t; t != tail; t = t->next)
			{
				if (v1 == t->data)
				{
					Node<T>* T3 = new Node<T>(v2, t->next);
					t->next = T3;
				}
			}
		}

	}


	void deletefromstart()
	{
		if (!tail)
			return;
		if (tail->next == tail)
		{
			delete tail;
			tail = nullptr;
		}
		else
		{
			Node<T>* t = tail->next;
			tail->next = t->next;
			delete t;
		}
	}

	void deleteafter(T const v1)
	{
		if (!tail)
			return;

		Node<T>* t = tail->next;
		if (tail->data == v1)
		{
			tail->next = t->next;
			delete t;
			return;
		}
		for (; t != tail; t = t->next)
		{
			if (v1 == t->data)
			{
				Node<T>* T3 = t->next;
				t->next = T3->next;
				delete T3;
				return;
			}
		}
	}

	void deleteatend()
	{
		if (!tail)
			return;
		if (tail->next == tail)
		{
			delete tail;
			tail = nullptr;
		}
		else
		{
			Node<T>* t;
			for (t = tail->next; t->next != tail; t = t->next)
			{
				t = t->next;
			}
			t->next = tail->next;
			delete tail;
			tail = t;
		}
	}

	void reverse()
	{
		if (!tail)
			return;
		if (tail->next == tail)
		{
			return;
		}

		/*Node<T>* T1 = tail;
		Node<T>* T2 = tail->next;
		Node<T>* T3;
		do
		{
			T3 = T2->next;
			T2->next = T1;
			T1 = T2;
			T2 = T3;
		} while (T1 != tail);
		tail = T3;*/

		
		Node<T>* prev;
		Node<T>* curr = tail->next;
		Node<T>* next1 = curr->next;

		do
		{
			prev = curr;
			curr = next1;
			next1 = curr->next;
			curr->next = prev;
			

		} while (curr != tail);
		next1->next = tail;
		tail = next1;
		
	}

	void changeTail(int n)
	{
		for (int i = 0; i < n; i++)
			tail = tail->next;
	}
	bool isEmpty()
	{
		return tail == nullptr;
	}
	~CircularLinked()
	{
		Node<T>* temp = tail->next;
		Node<T>* del = temp;
		while (temp != tail)
		{
			del = temp;
			temp = temp->next;
			delete del;
		}
		delete tail;
		tail = nullptr;
	}
};



int main()
{
	CircularLinked<int> C1;
	C1.insertatstart(7);
	C1.insertatstart(9);
	C1.insertatend(10);
	C1.insertatend(2);
	C1.print();
	C1.insertafter(2, 1);
	C1.print();
	C1.deletefromstart();
	C1.deleteatend();
	C1.print();

	C1.deleteafter(10);
	C1.print();
	C1.reverse();
	C1.print();
	C1.isEmpty();
	C1.insertafter(7, 4);
	C1.print();
	system("pause");
	return 0;
}
