#include<iostream>
using namespace std;

template<typename T>
class Node
{
private:
	T data;
	Node<T>* Next;
	Node<T>* Pre;
public:

	Node(T data = 0, Node<T>* Next = nullptr, Node<T>* pre = nullptr) :data(data), Next(Next), Pre(Pre) {};
	~Node()
	{
		Next = Pre = nullptr;
	}

	template<typename T>
	friend class DLinked;
};


template<typename T>
class DLinked
{
	Node<T>* head;
	Node<T>* tail;
	int size;

public:

	DLinked()
	{
		head = new Node<T>();
		tail = new Node<T>();
		head->Next = tail;
		tail->Pre = head;
		size = 0;
	}
	void InsertAtEnd(T const elem)
	{
		Node<T>* temp = new Node<T>(elem);
		if (head->Next == tail && tail->Pre == head)
		{
			head->Next = temp;
			temp->Pre = head;
		}
		else
		{
			tail->Pre->Next = temp;
			temp->Pre = tail->Pre;
		}
		temp->Next = tail;
		tail->Pre = temp;
		size++;

	}
	void InsertAtStart(T const elem)
	{
		Node<T>* temp = new Node<T>(elem);
		if (head->Next == tail && tail->Pre == head)
		{
			tail->Pre = temp;
			temp->Next = tail;
		}
		else
		{
			head->Next->Pre = temp;
			temp->Next = head->Next;
		}
		temp->Pre = head;
		head->Next = temp;
		size++;

	}





	void DeleteNode(Node<T>* P)
	{
		P->Pre->Next = P->Next;
		P->Next->Pre = P->Pre;
		delete P;
		size--;
	}

	void print()const
	{
		for (Node<T>* temp = head->Next; temp != tail; temp = temp->Next)
		{
			cout << temp->data << " ";
		}
		cout << endl;
	}


	bool DeleteValue(T const v)
	{
		Node<T>* temp;
		for (temp = head->Next; temp != tail && temp->data == v; temp = temp->Next);
		if (temp == tail)
		{
			cout << "End of list reached, no value of such exists" << endl;
			return false;
		}
		this->DeleteNode(temp);
		return true;

	}

	bool search(T const V)
	{
		Node<T>* P;
		for (P = head->Next; P != tail && P->data == V; P = P->Next);
		if (P == tail)
			return false;
		return true;
	}
	void AddNodeAfter(Node<T>* P, T const val)
	{
		Node<T>* temp = new Node<T>(val);
		P->Next->Pre = temp;
		temp->Next = P->Next;
		temp->Pre = P;
		P->Next = temp;
		size++;
	}

	void InsertAtMiddle(T const elem)
	{
		Node<T>* P = head;
		for (int i = 0; i < size / 2; i++)
			P = P->Next;

		this->AddNodeAfter(P, elem);

	}

	void reverse()
	{
		/*Node<T>* temp = NULL;
		Node<T>* current = this->head->Next;
		int i = 0;


		while (i < size)
		{
			temp = current->Pre;
			current->Pre = current->Next;
			current->Next = temp;
			current = current->Pre;
			i++;
		}

		temp = head;
		head = tail;
		tail = temp;
		tail->Pre = tail->Next;
		tail->Next = nullptr;
		head->Next = head->Pre;
		head->Pre = nullptr;*/
		Node<T>* curr, prev;
		curr = head->Next;
		ptr1 = curr->Next;

		curr->Next = head;
		curr->Pre = ptr1;
		while (ptr1 != nullptr)
		{
			ptr1->Pre = ptr1->Next;
			ptr1->Next = curr;
			curr = ptr1;
			ptr1 = ptr1->Pre;
		}
		head = ptr1;


	}


	/*~DLinked()
	{
		for (Node<T>* temp = head->Next; temp != nullptr; temp = temp->Next)
			delete  temp;
	}*/



};


int main_2()
{
	DLinked<char> list;
	list.InsertAtStart('A');
	list.InsertAtEnd('F');
	list.InsertAtStart('N');
	list.InsertAtStart('U');
	list.InsertAtMiddle('T');


	list.print();
	list.reverse();
	list.print();
	system("pause");
	return 0;
}

