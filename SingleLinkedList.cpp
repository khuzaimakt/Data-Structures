#include<iostream>
using namespace std;




template<typename T>
class LinkedList
{
	template<typename T>
	class Node
	{

	public:
		T d;
		Node<T>* next;

		Node(T data = 0, Node<T>* next = nullptr) :d(data), next(next) {}
		~Node() { next = nullptr; };
	};

	Node<T>* Tail;
	Node<T>* Head;
	Node<T>* Temp;
public:
	LinkedList(Node<T>* Head = nullptr, Node<T>* Tail = nullptr) :Head(Head), Tail(Tail) 
	{
		Temp = Head; 
	}
	T TempGet()
	{ 
		return Temp->d;
	}
	bool TempMove()
	{
	if(Temp->next)
	{
	Temp=Temp->next;
	return true;
	}
	return false;
	}
	void TempToStart()
	{ 
		Temp = Head;
	};
	void insertAtStart(T const element);
	void insertAtEnd(T const element);
	void print() const;
	bool search(T const& element) const;
	bool isEmpty() const;
	bool insertBefore(T const v1, T const v2);
	void deleteAll(T const value);
	void DeleteAtStart();
	void SortLinkedList();
	~LinkedList();
};


template<typename T>
void LinkedList<T>::insertAtStart(T const e)
{
	Node<T>* temp = new Node<T>(e, Head);
	Head = temp;
	if (Tail == nullptr)
		Tail = Head;
}

template<typename T>
void LinkedList<T>::insertAtEnd(T const e)
{
	Node<T>* temp = new Node<T>(e, nullptr);
	if (Tail)
		Tail->next = temp;
	Tail = temp;
	if (!Head)
		Head = Tail;
}

template<typename T>
void LinkedList<T>::print() const
{
	for (Node<T>* p = Head; p != nullptr; p = p->next)
	{
		cout << p->d << " ";
	}
	cout << endl;
}

template<typename T>
bool LinkedList<T>::search(T const& element) const
{
	for (Node<T>* p = Head; p != nullptr; p = p->next)
		if (p->d == element)
			return true;
	return false;
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	if (Head == Tail && Tail == nullptr)
		return true;
	return false;
}


template<typename T>
bool LinkedList<T>::insertBefore(T const v1, T const v2)
{

	if (isEmpty())
		return false;
	if (v2 == Head->d)
	{
		insertAtStart(v1);
		return true;
	}
	Node<T>* bef = Head;
	for (Node<T>* p = Head; p != nullptr; p = p->next)
	{
		if (p->d == v2)
		{
			Node<T>* temp = new Node<T>(v1, p);
			bef->next = temp;
			return true;
		}
		bef = p;
	}
	return false;
}

template<typename T>
void LinkedList<T>::deleteAll(T const value)
{
	if (isEmpty())
		return;
	Node<T>* bef = Head;
	Node<T>* ptr = Head;
	while (ptr != nullptr)
	{
		if (ptr->d == value)
		{
			bef->next = ptr->next;
			delete ptr;
		}
		else
		{
			bef = ptr;
		}
		if (bef)
			ptr = bef->next;
	}

}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* temp = Head;
	if (isEmpty())
		return;
	while (Head)
	{
		temp = Head->next;
		delete Head;
		Head = temp;
	}
}

template<typename T>
void LinkedList<T>::DeleteAtStart()
{
	if (isEmpty())
		return;
	if (Head == Tail)
	{
		delete Head;
		Tail = nullptr;
		Head = nullptr;
	}
	else {
		Node<T>* t = Head;
		Head = Head->next;
		delete t;
	}
}

template<typename T>
void LinkedList<T>:: SortLinkedList()
{
	Node<T>* node = nullptr, * temp = nullptr;
	int tempvar;
	node = Head;
	//temp = node;//temp node to hold node data and next link
	while (node != nullptr)
	{
		temp = Head;
		while (temp->next != nullptr)//travel till the second last element 
		{
			if (temp->d > temp->next->d)// compare the data of the nodes 
			{
				tempvar = temp->d;
				temp->d = temp->next->d;// swap the data
				temp->next->d = tempvar;
			}
			temp = temp->next;    // move to the next element 
		}
		node = node->next;    // move to the next node
	}
}
template <typename T>
int mode(LinkedList<T>& list) {
	int size;
	list.TempToStart();
	for (size = 1; list.TempMove(); size++);
	int maxfreq = 0, maxelem = 0, freq, elem;
	for (int i = 0; i < size; i++) {
		freq = 0;
		list.TempToStart();
		for (int j = 0; j < i; j++)
			list.TempMove();
		elem = list.TempGet();
		list.TempToStart();
		for (int j = 0; j < size; j++) {
			if (elem == list.TempGet())
				freq++;
			list.TempMove();
		}
		if (freq > maxfreq)
			maxfreq = freq, maxelem = elem;
	}

	return maxelem;
}

template <typename T>
int range(LinkedList<T>& list) {
	list.TempToStart();
	int max = list.TempGet();
	list.TempMove();
	int min;
	int temp = list.TempGet();
	if (max < temp) 
	{
		min = max;
		max = temp;
	}
	else
		min = temp;

	while (list.TempMove())
	{
		temp = list.TempGet();
		if (max < temp)
			max = temp;
		else if (min > temp)
			min = temp;
	}

	return max - min;
}


template <typename T>
int median(LinkedList<T>& list) 
{
	
	int size;
	int median;
	for (size = 1; list.TempMove(); size++);
	list.SortLinkedList();
	for (int i = 0; i < size / 2 && list.TempMove(); i++);
	if (size % 2 == 0)
	{
		median = list.TempGet();
		list.TempMove();
		median += list.TempGet();
		median /= 2;
	}
	else {
		median = list.TempGet();
	}

	return median;
}
int main_1() {
	// 90, 94, 53, 68, 79, 94, 53, 65, 87, 90, 70, 69, 65, 89, 85, 53, 47, 61, 27
	
	LinkedList<int> myList;
	myList.insertAtStart(90);
	myList.insertAtStart(94);
	myList.insertAtStart(53);
	myList.insertAtStart(68);
	myList.insertAtStart(79);
	myList.insertAtStart(94);
	myList.insertAtStart(53);
	myList.insertAtStart(65);
	myList.insertAtStart(87);
	myList.insertAtStart(90);
	myList.insertAtStart(70);
	myList.insertAtStart(69);
	myList.insertAtStart(65);
	myList.insertAtStart(89);
	myList.insertAtStart(85);
	myList.insertAtStart(53);
	myList.insertAtStart(47);
	myList.insertAtStart(61);
	myList.insertAtStart(27);
	cout << "Mode: " << mode(myList) << endl;
	cout << "Median: " << median(myList) << endl;
	cout << "Range: " << range(myList) << endl;
	
	return 0;
}

int main()
{
	LinkedList<int> myList;
	myList.insertAtStart(2);
	myList.insertAtStart(6);
	myList.insertAtStart(7);
	myList.insertAtEnd(9);
	myList.insertAtEnd(7);
	myList.insertAtEnd(8);
	myList.insertAtStart(9);
	myList.print();
	myList.deleteAll(7);
	myList.print();
	myList.insertBefore(10, 6);
	myList.print();
	cout << "searching for 10 :";
	cout << ((myList.search(10)) ? "Found " : "Not Found") << endl;
	cout << "searching for 11 :";
	cout << ((myList.search(11)) ? "Found " : "Not Found") << endl;
	myList.DeleteAtStart();
	myList.print();
	system("pause");
	return 0;
}


[15:19, 13 / 10 / 2021] KT: #include <iostream>
using namespace std;

class Term {
private:
	int exp; // exponent data item
	int coeff; // coefficient data item
	Term* next; // link to the next term to create a proper linked list.

public:
	friend class Polynomial;
	// constructor
	Term(int exp = 0, int coeff = 0, Term* next = nullptr) : exp(exp), coeff(coeff), next(next) {};
	// destructor
	~Term() { next = nullptr; };

};

// helper function needed in polynomial functions.
// It is created template to work with any data type.
template<typename T>
T power(T base, T exp) {
	// The resultant variable that will be returned. As it is going to be used for multiplication, it is initialized
	// with multiplicative identity(1).
	T res = 1;
	// This loop will run as long as it doesn't reach the exponent.
	for (int i = 0; i < exp; i++) {
		// power is repeated multiplication.
		res *= base;
	}
	return res;
}

class Polynomial {
private:
	Term* head; // The start of the polynomial
	int size; // Total terms in it

public:
	// Constructor
	Polynomial(Term* head = nullptr, int size = 0) : head(head), size(size) {};
	// Copy Constructor
	Polynomial(const Polynomial& obj);
	// assignment operator overloading.
	Polynomial& operator=(const Polynomial& obj);
	// input function for Polynomial
	void input();
	// output function for Polynomial
	void output();
	// add function for Polynomial
	Polynomial add(const Polynomial& other);
	// operator+ overloading
	Polynomial operator+(const Polynomial& other);
	// Function that equates the polynomial
	float evaluate(float n);
	// operator overloading to make it easier to use the evaluate function.
	float operator[](float n);
	// Destructor
	~Polynomial();
};

// This is a simple copy constructor that takes in an object to copy.
Polynomial::Polynomial(const Polynomial& obj) {
	// As it is being copied hence the size will be the same.
	this->size = obj.size;
	// Dummy is created to make the loop below easier. It is a term that points to a term from where our polynomial should
	// started, hence it points to the head of the polynomial. This is used so later the polynomial is updated with its
	// terms' list and the dummy created will be deleted.
	Term* curr = new Term();
	Term* dummy = curr;
	// The loop goes over the entirety of the parameter polynomial.
	for (Term* ptr = obj.head; ptr != nullptr; ptr = ptr->next) {
		// For each iteration a new term will be created on the next of the previous polynomial.
		// Hence next doesn't need to be updated, for this only a dummy Term will be left in the very start that is useless.
		curr->next = new Term(ptr->exp, ptr->coeff, nullptr);
		curr = curr->next;
	}
	// The head for this polynomial is updated and the dummy term in the start is later deleted to avoid any memory leakage.
	this->head = dummy->next;
	delete dummy;
	curr = nullptr;
}

// This an assigment operator that deep copies that object.
// The return type is Polynomial so that it is easier to assign multiple objects, e.g a = b = c.
// The return type is also a reference to avoid copies of the same object.
Polynomial& Polynomial::operator=(const Polynomial& obj) {
	// As it is being copied hence the size will be the same.
	this->size = obj.size;
	// Dummy is created to make the loop below easier. It is a term that points to a term from where our polynomial should
	// started, hence it points to the head of the polynomial. This is used so later the polynomial is updated with its
	// terms' list and the dummy created will be deleted.
	Term* curr = new Term();
	Term* dummy = curr;
	// The loop goes over the entirety of the parameter polynomial.
	for (Term* ptr = obj.head; ptr != nullptr; ptr = ptr->next) {
		// For each iteration a new term will be created on the next of the previous polynomial.
		// Hence next doesn't need to be updated, for this only a dummy Term will be left in the very start that is useless.
		curr->next = new Term(ptr->exp, ptr->coeff, nullptr);
		curr = curr->next;
	}
	// The head for this polynomial is updated and the dummy term in the start is later deleted to avoid any memory leakage.
	this->head = dummy->next;
	delete dummy;
	curr = nullptr;

	return *this;
}

// void as the function is not supposed to return anything and is only needed to
// populate the polynomial object that was used to call the function.
void Polynomial::input() {
	// Two variables, one used to create a term that later will be added to the polynomial and 
	// the other used to run a loop for the amount of polynomials needed to be entered.
	int no;
	Term* temp = new Term();
	// Will be used later. Need to retain the last value in it hence it is declared here.
	Term* ptr = nullptr;
	// flag to check whether the loop checking where to fit the polynomial ended or not
	bool flag;

	// No. of terms input.
	cout << "Enter the number of terms you want to enter: ";
	cin >> no;

	for (int i = 0; i < no; i++) { // O(no) where no are the number of terms.
		cout << "Enter the coefficient and space separated exponent for term " << i + 1 << ": ";
		cin >> temp->coeff >> temp->exp;

		// if the coefficient is zero then the term does not exist and hence doesn't need to be stored.
		if (temp->coeff == 0)
			continue;

		// in case the polynomial object is empty
		if (head == nullptr)
			head = temp, size++;
		// in case it has 1 or more items in it.
		else {
			/*
			 If the head's exponent is same as the newly entered one then the coefficients are added.
			 This is done because the loop used to check the rest of the terms will be checking from "term"->next
			 Because in that way we can find the exact location of where to place the polynomial in case that
			 exponent doesn't already exist.
			 */
			if (head->exp == temp->exp) {
				head->coeff += temp->coeff;
				delete temp;
			}
			// In the case that the term should be added to the very start of the polynomial.
			else if (head->exp < temp->exp) {
				temp->next = head;
				head = temp;
				size++;
			}
			else {
				// Loop to check the rest of the terms.
				flag = true;
				// ptr was declared above as in the case where the new term should be at the end, we need
				// the last term in the polynomial to properly update it.
				// Worst case O(n) n being the size of polynomial. Best case O(1).
				for (ptr = head; ptr->next != nullptr; ptr = ptr->next) {
					/*
					The reason to check the next term's exponent is so that we can fix the else if's case
					where we need the previous term in order to place our new term in between two terms.
					Otherwise we would need to also update a prev pointer that will point to the last iteration's ptr.
					*/
					if (ptr->next->exp == temp->exp) {
						ptr->next->coeff += temp->coeff;
						delete temp;
						// The flag used here and in the next if is simply to check whether the whole loop
						// ran and there was no equivalent polynomial i.e the new term fits at the end of the polynomial.
						flag = false;
						// We found our term so we do not need to run the loop anymore.
						break;
					}
					else if (ptr->next->exp < temp->exp) {
						temp->next = ptr->next;
						ptr->next = temp;
						flag = false;
						size++;
						break;
					}

				}
				// This if will run only in the case that the new term should be at the end of the polynomial.
				if (flag)
					ptr->next = temp, size++;
			}
		}

		// In any case, the term should be reinitialized with new memory as the old one is either added to the polynomial
		// or is destroyed.	
		temp = new Term();
	}
	// update size.
}

// void as it is not supposed to return anything and only outputs to the console.
void Polynomial::output() {
	// Loop traversing over the entire polynomial.
	// O(n) where n is the size of the polynomial.
	cout << "Size: " << size << endl;
	for (Term* ptr = head; ptr != nullptr; ptr = ptr->next) {
		if (ptr != head && ptr->coeff > 0)
			cout << "+";
		cout << ptr->coeff;
		if (ptr->exp > 1 || ptr->exp < 0)
			cout << "n^" << ptr->exp;
		else if (ptr->exp == 1)
			cout << "n";
	}
	cout << endl;
}

// return type Polynomial as this function is supposed to return a new polynomial after two given Polynomials together.
// parameter other is being passed as the other polynomial to be added and to avoid duplocation, it is sent as a reference.
// Parameter is constant as it and the "this" polynomial will not be changed
Polynomial Polynomial::add(const Polynomial& other) {
	Polynomial res; // resultant polynomial after addition, will be returned.

	// These three pointers will be used to traverse through our polynomials and add and store the data.
	// They are started at the head of each polynomial and will work their way ahead as the resultant polynomial is updated.
	Term* poly1ptr = this->head;
	Term* poly2ptr = other.head;
	Term* reshead = new Term();
	Term* resptr = reshead;


	// if either one of them have not reached the end of their designated polynomial, that means addition is still not 
	// complete.
	while (poly1ptr != nullptr || poly2ptr != nullptr) {
		// in case one pointer has reached the end of its polynomial, we do not need to check anything else
		// and just update the resultant polynomial with the values left.
		if (poly1ptr == nullptr) {
			resptr->next = new Term(poly2ptr->exp, poly2ptr->coeff, nullptr);
			// updating the pointers as the current terms are already updated.
			resptr = resptr->next;

			poly2ptr = poly2ptr->next;
			// updating size.
			res.size++;
		}
		// same as the above but for the pointer.
		else if (poly2ptr == nullptr) {
			resptr->next = new Term(poly1ptr->exp, poly1ptr->coeff, nullptr);
			// updating the pointers as the current terms are already updated.
			resptr = resptr->next;

			poly1ptr = poly1ptr->next;
			res.size++;

		}
		// The ifs below will only be reached in case both of the pointers are not pointing to nullptr.
		// in that case we have to check whether exponents are equal, or one is less than the other.

		// This else if checks the equal case and if the exponents are equal it performs the addition respectively.
		else if (poly1ptr->exp == poly2ptr->exp) {
			// in the case that both polynomials' coefficient are added, if their sum equates to zero then that
			// polynomial doesn't exist and doesn't affect the equation in any way and hence should be removed.
			// This if only runs in case both polynomials terms' addition does not equate to zero.
			if (poly1ptr->coeff + poly2ptr->coeff != 0) {
				resptr->next = new Term(poly1ptr->exp, poly1ptr->coeff + poly2ptr->coeff, nullptr);
				resptr = resptr->next;
				res.size++;
			}

			poly1ptr = poly1ptr->next;
			poly2ptr = poly2ptr->next;
		}
		// This if checks whether one pointer points to a greater exp, in that case, only that term will be added
		// to keep it in a sorted order.
		else if (poly1ptr->exp > poly2ptr->exp) {
			resptr->next = new Term(poly1ptr->exp, poly1ptr->coeff, nullptr);
			// updating the pointers as the current terms are already updated.
			resptr = resptr->next;

			poly1ptr = poly1ptr->next;
			res.size++;
		}
		// same as the above if, but for the other polynomial. Else as there is no other condition left other than
		// the one where one polynomial points to a smaller exponent than the other.
		else {
			resptr->next = new Term(poly2ptr->exp, poly2ptr->coeff, nullptr);
			// updating the pointers as the current terms are already updated.
			resptr = resptr->next;

			poly2ptr = poly2ptr->next;
			res.size++;
		}
	}
	res.head = reshead->next;
	delete reshead;
	return res;
}

// Same as the add function, just adds the functionality of + sign in Polynomials.
Polynomial Polynomial::operator+(const Polynomial& other) {
	return this->add(other);
}

// return type float as it is supposed to return the result aftr evaluating the polynomial's equation.
float Polynomial::evaluate(float n) {
	// the result will be accumalated in this variable and later be returned.
	float res = 0;
	// This loop will traverse over the entirety of the polynomial.
	for (Term* ptr = this->head; ptr != nullptr; ptr = ptr->next) {
		// Each term is in the form of coeff*n^exp. while having all three values this is how it should be calculated.
		res += ptr->coeff * power<float>(n, ptr->exp);
	}
	// result is returned.
	return res;
}

// works the same as the evaluate function, just the parameters are passed using [] in main.
float Polynomial::operator[](float n) {
	return this->evaluate(n);
}

// Simple destructor to free up all the memory the polynomial was taking.
Polynomial::~Polynomial() {
	// prev is used to destroy the last element as the ptr moves forward, this is done because
	// if an element is removed before the next of it is stored somewhere, the rest of the list is lost.
	Term* prev = nullptr;
	Term* ptr = this->head;
	// The loop traverses over the entire length of the polynomial.
	while (ptr != nullptr) { // O(n) where n = size of polynomial.
		// In the body, ptr moves forward while prev destroys the previous memory.
		prev = ptr;
		ptr = ptr->next;
		delete prev;
	}
	// Just to avoid dangling pointers.
	this->head = nullptr;
}

int main() {

	Polynomial poly1;
	poly1.input();
	Polynomial poly2(poly1);
	poly2.output();
	return 0;
}