


#include <iostream>
using namespace std;

template<typename T>
class Node
{
	T data;
	Node<T>* next;

public:
	template<typename T>
	friend class CLinked;
	Node(T d = 0, Node<T>* next = nullptr) :data(d), next(next) {}
};

template<typename T>
class CLinked
{
	Node<T>* head;
	Node<T>* tail;
public:
	CLinked()
	{
		head = nullptr;
		tail = nullptr;
	}
	void Insert(T d)
	{
		Node<T>* temp = new Node<T>(d);
		if (head == nullptr)
		{
			head = temp;
			tail = temp;
			tail->next = head;
		}
		else
		{
			head = tail->next;
			temp->next = tail->next;
			tail->next = temp;
			tail = temp;
		}
	}

	void print()
	{
		if (head == nullptr)
			cout << "No Circular linked list exists" << endl;
		for (Node<T>* temp = head; temp->next != head; temp = temp->next)
		{
			cout << temp->data << " ";
		}

		cout << tail->data << " ";

		cout << endl;
	}

	void split(CLinked<T>& C2, CLinked<T>& C3)
	{
		
		int count = 1;
		for (Node<T>* temp = tail->next; temp != tail; temp = temp->next)
		{
			count++;

		}

		int middle = count / 2;



		
		Node<T>* temp = head;
		
		
		
		for (int start = 0; start < middle; start++)
		{
			
			
			
			C2.Insert(temp->data);
			temp = temp->next;
			

		}




		
		

		Node<T>* temp1 = head;
		for (int start = 1; start < middle+1; start++)
			temp1 = temp1->next;

		
		
	
	
		for (int start = middle + 1; start <= count; start++)
		{
			
			C3.Insert(temp1->data);
				temp1 = temp1->next;
			
		}
		
		

	}

   int AboveAverage(int value) { // AboveAverage wrapper.
	// needed as we need to traverse over all of the elements of the CSLL
	// hence we need a node so that we can move forward from there.
		return AboveAverage(value, head); // calculates average and returns.
	}

	
	int AboveAverage(int value, Node<T>* ptr) {
		int sum = 0; // sum of all the forward elements for each recursion.
		if (ptr != nullptr) { // if the CSLL is empty, nothing is executed.
			if (ptr->data > value) // if the data is greater then the data is added to sum
				sum += ptr->data;
			ptr = ptr->next; // ptr is moved forward for the next recursive call.
			if (ptr != head) // if ptr is equal to head that means it has gone full circle as caller sends the
							 // head in the start.
				sum += AboveAverage(value, ptr); // recursive call for to calculate the sum of all the forward elements.
		}
		return sum; // returns the sum of all the data greater than the given value.
	}


};

int main_1()
{
	CLinked<int> C1;
	CLinked<int> C2;
	CLinked<int> C3;

	
	C1.Insert(1);
	C1.Insert(4);
	C1.Insert(8);
	C1.Insert(9);
	C1.Insert(12);
	C1.Insert(0);
	C1.Insert(14);
	
	C1.print();
	
	C1.split(C2, C3);
	C2.print();
	C3.print();
	
	 cout<<C2.AboveAverage(2)<< " ";
	


	
	return 0;
}


