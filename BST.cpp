#include <iostream>
using namespace std;

template <typename k, typename v>
struct TNode
{
	k key;
	v value;
	TNode<k, v>* leftChild;
	TNode<k, v>* rightChild;
	TNode(k key, v value, TNode<k, v>* left, TNode<k, v>* right) {
		this->key = key;
		this->value = value;
		leftChild = left;
		rightChild = right;
	}
};


template <typename k, typename v>
class BST {
private:
	TNode<k, v>* root;

public:

	BST();
	void insertRec(k const key, v const value);
	void insertRec(k const key, v const value, TNode<k, v>*& ptr);
	void insert(k const key, v const value);
	v* search(k const key);
	v* search(k const key, TNode<k, v>* ptr);
	void inorderPrintKeysRec() const;
	void inorderPrintKeysRec(TNode<k, v>* ptr) const;
	int length() const;
	int length(TNode<k, v>* ptr) const;
	void printAllAncestors(k const key) const;
};

template<typename k, typename v>
BST<k, v>::BST() {
	root = nullptr;
}

template<typename k, typename v>
void BST<k, v>::insertRec(k const key, v const value) {
	insertRec(key, value, root);
}

template<typename k, typename v>
void BST<k, v>::insertRec(k const key, v const value, TNode<k, v>*& ptr) {

	if (ptr == nullptr)
		ptr = new TNode<k, v>(key, value, nullptr, nullptr);
	else if (key>ptr->key)
		insertRec(key, value, ptr->rightChild);
	else if (key<ptr->key)
		insertRec(key, value, ptr->leftChild);
	else
		ptr->value = value;
}

template<typename k, typename v>
void BST<k, v>::insert(k const key, v const value) {
	if (!root)
		root = new TNode<k, v>(key, value, nullptr, nullptr);

	TNode<k,v>* x = root;
	TNode<k, v>* y = NULL;;
	while (x != nullptr)
	{
		y = x;
		if (key < x->key)
			x = x->leftChild;
		else
			x = x->rightChild;

	}
	if (y == NULL)
		y = new TNode<k, v>(key, value, nullptr, nullptr);
	else if (key < y->key)
		y->leftChild = new TNode<k, v>(key, value, nullptr, nullptr);
	else
		y->rightChild = new TNode<k, v>(key, value, nullptr, nullptr);

	
}

template<typename k, typename v>
v* BST<k, v>::search(k const key) {
	return search(key, root);
}

template<typename k, typename v>
v* BST<k, v>::search(k const key, TNode<k, v>* ptr) {

	if (ptr == nullptr)
		return nullptr;
	if(ptr->key==key)
		return &ptr->value;
	
	if (key > ptr->key)
		return search(key, ptr->rightChild);
	else if (key < ptr->key)
		return search(key, ptr->leftChild);
	

	
}

template<typename k, typename v>
void BST<k, v>::inorderPrintKeysRec() const {
	inorderPrintKeysRec(root);
	cout << endl;
}


template<typename k, typename v>
void BST<k, v>::inorderPrintKeysRec(TNode<k, v>* ptr) const {
	if (ptr != nullptr)
	{
		inorderPrintKeysRec(ptr->leftChild);
		cout << ptr->key << " ";
		inorderPrintKeysRec(ptr->rightChild);
	}
	
}

template<typename k, typename v>
void BST<k, v>::printAllAncestors(k const key) const {
	TNode<k, v>* tmp = root;
	while (true)
	{
		if (tmp == nullptr)
			return;
		if (tmp->key == key)
			return;
		cout << tmp->key << " ";
		if (tmp->key < key)
			tmp = tmp->rightChild;
		else if (tmp->key > key)
			tmp = tmp->leftChild;
	}
	
}

template<typename k, typename v>
int BST<k, v>::length() const {
	return length(root);
}

template<typename k, typename v>
int BST<k, v>::length(TNode<k, v>* ptr) const {
	int l = 0;
	if (ptr == nullptr)
		return l;
	if (ptr!=nullptr) {
	    l += length(ptr->leftChild);
		l += 1;
		l += length(ptr->rightChild);
	}
	return l;
}

int main()
{
	BST<int, int> tree; 

	tree.insert(500, 500);
	tree.insertRec(1000, 1000);
	tree.insert(1, 1);
	tree.insert(600, 600);
	tree.insertRec(700, 700);
	tree.insert(10, 10);
	tree.insert(30, 30);
	tree.insertRec(9000, 9000);
	tree.insert(50000, 50000);
	tree.insertRec(20, 20);

	cout << endl << endl << "Printing keys using recursive inorder traversal: ";
	tree.inorderPrintKeysRec();

	cout << endl << endl << "Tree Length: " << tree.length() << endl << endl;

	int* val = tree.search(1);

	if (val != nullptr)
	{
		cout << "1 found" << endl;
	}

	val = tree.search(123);

	if (val == nullptr)
	{
		cout << "123 not found" << endl;
	}

	cout << endl << "Printing the keys of ancestor nodes of 20: ";
	tree.printAllAncestors(20);

	system("pause");
}
