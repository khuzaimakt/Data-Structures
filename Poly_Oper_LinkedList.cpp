#include<iostream>
using namespace std;

//Assignment-1 Data Structures
//Khuzaima Tofeeq 20L-1304 BDS-3A



class Term
{
	//Data members of Term class 

	int exponent;
	int coeffecient;
	Term* nextT;

public:


	friend class Polynomial; // Making Polynomial class it's friend so that can access it's private data members

	Term(int exponent = 0, int coeffecient = 0, Term* nextT = nullptr)
		:exponent(exponent), coeffecient(coeffecient), nextT(nextT) {}; // constructor
	~Term()
	{
		nextT = nullptr;
	} // Destructor

};






class Polynomial
{
	// Data Members of Polynomial Class
	int size;

	Term* head;


public:

	Polynomial(int size = 0, Term* head = nullptr)
		:size(size), head(head) {}; //Constructor
	~Polynomial()
	{
		Term* New = nullptr;
		Term* Temp = this->head;

		while (Temp != nullptr)
		{
			New = Temp;
			Temp = New->nextT;
			delete New;
		}

		head = nullptr;
	} //Destructor

	Polynomial(const Polynomial& P)
	{
		size = P.size;

		Term* New = new Term();
		Term* Temp = New;

		for (Term* ptr = P.head; ptr != nullptr; ptr = ptr->nextT)
		{

			New->nextT = new Term(ptr->exponent, ptr->coeffecient, nullptr);
			New = New->nextT;
		}

		this->head = Temp->nextT;
		delete Temp;
		New = nullptr;



	} //Copy Constructor


	//Member functions

	Term* input(); //Input function
	Term* insert(Term* head, int coeff, int exp);//Function that is used to store every term in ascending order
	void print()const; //Print function
	Polynomial AddPoly(Polynomial& P);// Function to add two polynomials
	Polynomial MulPoly(Polynomial& P);// Function to multiply two polynomials
	int Evaluate();//Function to evaluate the polynomial
	Polynomial& operator=(const Polynomial& obj);// Assignment operator overlauding

	// addition operator overloading
	Polynomial operator+(Polynomial& P)
	{
		return this->AddPoly(P);
	}
	// multiplication operator overloading
	Polynomial operator*(Polynomial& P)
	{
		Polynomial Res = this->MulPoly(P);
		Term* New = Res.head;
		Term* temp = nullptr;

		while (New->nextT != nullptr)
		{
			if (New->exponent == New->nextT->exponent)
			{
				New->coeffecient = New->coeffecient + New->nextT->coeffecient;
				temp = New->nextT;
				New->nextT = New->nextT->nextT;
				delete temp;
				Res.size--;
			}
			else
				New = New->nextT;
		}
		//Simplifies the resultant polynomial as it might contain the same exponents with two different coeffecients 
		// and adds them

		return Res;
	}
	// Evaluartion operator overlauding
	int operator[](int n)
	{
		int sum = 0;


		Term* P1 = head;
		if (P1 == nullptr)
		{
			cout << "No polynomial " << endl;
		}

		while (P1 != nullptr)
		{
			if (P1->exponent != 0)
			{
				sum += P1->coeffecient * (P1->exponent * n);
			}
			else
				sum += P1->coeffecient;
			P1 = P1->nextT;
		}

		return sum;
	}
};


//Function to insert the terms in the linked list in ascending order of exponents

Term* Polynomial::insert(Term* head, int coeff, int exp)
{
	Term* temp;
	Term* New = new Term();
	New->coeffecient = coeff;
	New->exponent = exp;
	New->nextT = NULL;
	if (head == nullptr || exp > head->exponent) //Empty check as well as if exponent passed is greater than the first exponent
	{

		New->nextT = head;
		head = New;
	} //Places the passed values at the start of the linked list
	else
	{

		temp = head;
		while (temp->nextT != nullptr && temp->nextT->exponent >= exp)
			temp = temp->nextT;
		New->nextT = temp->nextT;
		temp->nextT = New;


	} //Places the passed values in the desired position with respect to the ascending order of exponents
	return head;
}


//Function to take input values of size of polynomial, and the coeffecients and exponents from user

Term* Polynomial::input()
{
	int i, n;
	int coeff, exp;
	cout << "Enter the size of polynomial: " << endl;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "Enter the " << i + 1 << " coeffecient: " << endl;
		cin >> coeff;
		cout << "Enter the " << i + 1 << " exponent: " << endl;
		cin >> exp;
		if(coeff!=0)
		head = insert(head, coeff, exp);
		size++;
	}
	return head;

}
//Function to print the polynomial

void Polynomial::print()const
{
	if (head == nullptr)
	{
		cout << "No polynomial " << endl;

	}

	else
		for (Term* temp = head; temp != nullptr; temp = temp->nextT)
		{
			if (temp->exponent > 1 || temp->exponent < 0)
				cout << temp->coeffecient << "x^" << temp->exponent;
			if (temp->exponent == 0)
				cout << temp->coeffecient;
			if (temp->exponent == 1)
				cout << temp->coeffecient << "x";
			if (temp->nextT != nullptr)
				cout << "+";
			else
				cout << " ";
		}

	cout << endl;

}

//Function to add two polynomials

Polynomial Polynomial::AddPoly(Polynomial& P)
{
	Term* P1 = this->head;
	Term* P2 = P.head;
	Term* P3 = NULL;
	Polynomial Res;

	if (this->head == nullptr || P.head == nullptr)
	{
		cout << "No polynomial " << endl;
	}//Empty check

	else
	{
		while (P1 != nullptr && P2 != nullptr)
		{
			if (P1->exponent == P2->exponent)
			{
				P3 = insert(P3, P1->coeffecient + P2->coeffecient, P1->exponent);
				P1 = P1->nextT;
				P2 = P2->nextT;
				Res.size++;
			}
			else if (P1->exponent > P2->exponent)
			{
				P3 = insert(P3, P1->coeffecient, P1->exponent);
				P1 = P1->nextT;
				Res.size++;
			}
			else if (P1->exponent < P2->exponent)
			{
				P3 = insert(P3, P2->coeffecient, P2->exponent);
				P2 = P2->nextT;
				Res.size++;
			}
		}
		while (P1 != nullptr)
		{
			P3 = insert(P3, P1->coeffecient, P1->exponent);
			P1 = P1->nextT;
			Res.size++;
		}
		while (P2 != nullptr)
		{
			P3 = insert(P3, P2->coeffecient, P2->exponent);
			P2 = P2->nextT;
			Res.size++;
		}

	}


	Res.head = P3;
	P3 = nullptr;
	return Res;



}


//Function to multiply two polynomials

Polynomial Polynomial::MulPoly(Polynomial& P)
{
	Term* P1 = this->head;
	Term* P2 = P.head;
	Term* P3 = NULL;
	Polynomial  Res;
	if (this->head == nullptr || P.head == nullptr)
	{
		cout << "No polynomial " << endl;
	}//Empty check

	while (P1 != nullptr)
	{
		while (P2 != nullptr)
		{
			P3 = insert(P3, P1->coeffecient * P2->coeffecient, P1->exponent + P2->exponent);
			Res.size++;
			P2 = P2->nextT;
		}
		P1 = P1->nextT;
		P2 = P.head;

	}//Multiplies each value of the first polynomial with the each value of second polynomial





	Res.head = P3;
	P3 = nullptr;
	return Res;
}


//Function to evaluate the polynomial by takin the x value from user

int Polynomial::Evaluate()
{
	int n;
	int sum = 0;
	cout << "Enter the value of n " << endl;
	cin >> n;
	Term* P1 = head;
	if (P1 == nullptr)
	{
		cout << "No polynomial " << endl;
	}

	while (P1 != nullptr)
	{
		if (P1->exponent != 0)
		{
			sum += P1->coeffecient * (P1->exponent * n);
		}
		else
			sum += P1->coeffecient;
		P1 = P1->nextT;
	} //Eva;uates the value of polynomial by storing it in the variable sum

	return sum;

}

//Assignment operator overlauding
Polynomial& Polynomial::operator=(const Polynomial& P) {

	size = P.size;

	Term* New = NULL;
	Term* Temp = New;

	for (Term* ptr = P.head; ptr != nullptr; ptr = ptr->nextT)
	{

		New = insert(New, ptr->exponent, ptr->coeffecient);

	}

	this->head = Temp->nextT;
	delete Temp;
	New = nullptr;

	return *this;
}

int main_1()
{
	Polynomial P1;
	Polynomial P2;

	int eva;
	P1.input();
	P1.print();
	P2.input();
	P2.print();
	Polynomial P3 = P1 + P2; //Addition of polynomials
	P3.print();
	Polynomial P4 = P1 * P2; //Multiplication of polynomials
	P4.print();
	eva = P1.Evaluate(); //Evaluation of polynomial
	cout << eva << endl;



	return 0;
}

