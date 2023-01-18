#include<iostream>
#include<string>
using namespace std;

class PatientRecord
{
public:
	int id;
	string name;
	string date;
	string diagnosis;
	string status;

	PatientRecord(int id, string name=" ", string date=" ", string diagnosis=" ", string status=" ")
	{
		this->id = id;
		this->name = name;
		this->date = date;
		this->diagnosis = diagnosis;
		this->status = status;
	}
	void PrintPR()
	{
		cout << " Patient Record: " << endl;
		cout << " ID: " << id << endl;
		cout << " Name: " << name << endl;
		cout << " Date: " << date << endl;
		cout << " Diagnosis: " << diagnosis << endl;
		cout << " Status: " << status << endl;
		cout << endl << endl;
	}

};



class TNode
{
	PatientRecord P;
	TNode* LChild;
	TNode* RChild;

public:
	
	friend class HospitalData;

	TNode(PatientRecord p,TNode* L=nullptr,TNode* R=nullptr):P(p),LChild(L),RChild(R){}
	


};



class HospitalData
{

	TNode* root;
	int size;

public:
	HospitalData()
	{
		size = 0;
		root = nullptr;
	}
	HospitalData(int n, TNode* p)
	{
		root = nullptr;
		copybst(p);
		size = n;
	}

	void copybst(TNode*& ptr)
	{
		if (ptr)
		{
			copybst(ptr->LChild);
			copybst(ptr->RChild);
			insert(ptr->P);
		}
	}
	~HospitalData()
	{
		desrem(root);
		size = 0;
	}
	void desrem(TNode*& ptr)
	{
		if (ptr) {
			desrem(ptr->LChild);
			desrem(ptr->RChild);
			delete ptr;
		}
			
	}
	void insert(PatientRecord p)
	{
		insert(p, root);
		size++;
	}
	void insert(PatientRecord p,TNode*& ptr)
	{
		TNode* temp = new TNode(p, nullptr, nullptr);
		
			
		if (ptr)
		{
			if (p.id < ptr->P.id)
			{
				insert(p, ptr->LChild);
				rightRotate(ptr);
			}
			if (p.id > ptr->P.id)
			{
				insert(p, ptr->RChild);
				leftRotate(ptr);
			}
		}
		

	
		else
		{
			ptr = temp;
			return;
		}
		
			
	
		
	}
	void remove(int pid)
	{
		if (size == 0)
		{
			cout << "No item exists" << endl;
			return;
		}
		 remove( pid,root);
		 

	}
	void remove(int pid, TNode*& ptr)
	{
		
		if (ptr)
		{
			if (pid > ptr->P.id)
				remove(pid, ptr->RChild);
			else if (pid < ptr->P.id)
				remove(pid, ptr->LChild);
			else
			{
				deleteNode(ptr);
				size--;
			}
		}
	}
	void deleteNode(TNode*& ptr)
	{
		TNode* temp = ptr;
		if (ptr->LChild == nullptr)
		{
			ptr = ptr->RChild;
			delete temp;
		}
		else if (ptr->RChild == nullptr)
		{
			ptr = ptr->LChild;
			delete temp;
		}
		else
		{
			int d = getPredecessor(ptr->LChild);
			ptr->P.id = d;
			remove(d, ptr->LChild);
		}
	}
	int getPredecessor(TNode*& ptr)
	{
		while (ptr->RChild != nullptr)
			ptr = ptr->RChild;
		return ptr->P.id;
	}
	void print(int pid)
	{
		print(pid, root);
	}
	void print(int pid, TNode*& ptr)
	{
		
		while (ptr && ptr->P.id != pid)
		{
			if (pid < ptr->P.id)
				ptr = ptr->LChild;
			else
				ptr = ptr->RChild;
		}
		if (ptr)
		{
			ptr->P.PrintPR();
		}
		else
			cout << "No such patient record exists" << endl;
	}
	void PrintAdmitted()
	{
		PrintAdmitted(root);
	}
	void PrintAdmitted(TNode*& ptr)
	{
		if (size == 0)
		{
			cout << "No item inserted" << endl;
			return;
		}
		if (ptr)
		{
			PrintAdmitted(ptr->LChild);

			if(ptr->P.status=="Admitted")
				ptr->P.PrintPR();
			
			PrintAdmitted(ptr->RChild);
		}
	}
	void printpre(TNode*& ptr)
	{
		if (size == 0)
		{
			cout << "No item inserted " << endl;
			return;
		}
		if (ptr)
		{
			

			if (ptr->P.status == "Admitted")
				ptr->P.PrintPR();
			printpre(ptr->LChild);
			printpre(ptr->RChild);
		}
	}
	void printpre()
	{
		printpre(root);
	}
	void leftRotate(TNode*& x)
	{
		TNode* y = x->RChild;
		TNode* orphan = y->LChild;
		y->LChild = x;
		x->RChild = orphan;
		x = y;
	}

	void rightRotate(TNode*& x)
	{
		TNode* y = x->LChild;
		TNode* orphan = y->RChild;
		y->RChild = x;
		x->LChild = orphan;
		x = y;
	}


	PatientRecord search(int pid, int k)
	{
		int level = 0;
		return search(pid, k, root, level);
	}
	PatientRecord search(int pid, int k, TNode*& ptr, int level)
	{ 
		PatientRecord temp(-1);
		
		bool found = false;
		if (ptr) {
			level++;
			if (ptr->P.id < pid)
			{
			    temp = search(pid, k, ptr->RChild, level);
				if (level > k)
					leftRotate(ptr);
			}
			else if (ptr->P.id > pid)
			{
			    temp = search(pid, k, ptr->LChild, level);
				if (level > k)
					rightRotate(ptr);
			}
			else if (ptr->P.id == pid)
			{
				found = true;
				temp = ptr->P;
			}
		}
		return temp;

	
	}

	PatientRecord Medianfinder(int n)
	{
		PatientRecord temp(-1);
		if (n > size)
		{
			cout << "Index not found " << endl;
			
		}
		else if (n < 0)
		{
			cout << "Index not found " << endl;
			
		}
		else
		{
			
			temp = Medianfinder(n, root);
		}
		return temp;

	}

	PatientRecord Medianfinder(int& n, TNode* ptr)
	{
		PatientRecord temp(-1);
		if (ptr && n > 0) {
			temp = Medianfinder(n, ptr->LChild);
			n--;
			if (n == 0)
				temp = ptr->P, n--;
			if (n > 0) {
				temp = Medianfinder(n, ptr->RChild);
				if (n == 0)
					temp = ptr->P;
			}

		}
		return temp;
	}

	HospitalData split()
	{
		if (size == 0)
		{
			cout << "No item inserted " << endl;
			return HospitalData();
		}
		PatientRecord temp = Medianfinder((size + 1) / 2);
		search(temp.id, 0);

		return HospitalData(size - 1,root->RChild);
	}
	
};


int main() {

	HospitalData tree;
	tree.insert(PatientRecord(2,"K","21","C","Admitted"));
	tree.insert(PatientRecord(5, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(4, "K", "21", "C","Admitted"));
	/*tree.insert(PatientRecord(6, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(10, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(8, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(7, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(9, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(12, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(11, "K", "21", "C","Admitted"));
	tree.insert(PatientRecord(14, "K", "21", "C","Admitted"));
	*/
	tree.printpre();
	

	
	
	

	return 0;
}