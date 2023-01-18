#include <iostream>
using namespace std;

template <typename k, typename v>
struct TNode
{
	k key;
	v value;
	int height;
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
public:
	TNode<k, v>* root;


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
	void deletep(k const key);
	void deletep(k const key, TNode<k, v>*& ptr);
	void deleteNode(TNode<k, v>*& ptr);
	k getPredecessor(TNode<k, v>* ptr);
};

template<typename k, typename v>
class AVL :public BST<k, v>
{
public:
	/*void remove(k const key, k const value)
	{
		remove(key, value,root);
	}

	void remove(k const key, k const value, TNode<k, v>*& ptr)
	{
		if (!ptr)
			return;
		if (key < ptr->key)
			remove(key, value, ptr->leftChild);
		else if (key > ptr->key)
			remove(key, value, ptr->rightChild);
		else if (ptr->leftChild != nullptr && ptr->rightChild != nullptr)
		{
			ptr->key = getPredecessor(k, ptr->leftChild);
			remove(ptr->key, ptr->leftChild);
		}
		else
		{
			TNode<k, v>* temp = ptr;
			if (ptr->leftChild != nullptr)
				ptr = ptr->leftChild;
			else
				ptr = ptr->rightChild;

		}
		balance(ptr);
	}*/
	void insertA(k const key, v const value)
	{
		insertA(key, value, root);
	}
	void insertA(k const key, v const value, TNode<k, v>*& ptr)
	{
		if (ptr == nullptr)
			ptr = new TNode<k, v>(key, value, nullptr, nullptr);
		else if (ptr->key < key)
			insertA(key, value, ptr->rightChild);
		else if (ptr->key > key)
			insertA(key, value, ptr->leftChild);
		else
			ptr->value = value;
		balance(ptr);
	}

	int height()
	{
		return height(root);
	}
	int height(TNode<k, v>* ptr)
	{
		int h;
		if (ptr == nullptr)
			h = -1;
		else if (ptr->leftChild == nullptr)
		{
			if (ptr->rightChild == nullptr)
				h = 0;
			else
				h = ptr->rightChild->height + 1;
		}
		else if (ptr->rightChild == nullptr)
			h = ptr->leftChild->height + 1;
		else
			h = max(ptr->leftChild->height, ptr->rightChild->height) + 1;
		return h;
	}
	int max(const int v1, const int v2)
	{
		if (v1 > v2)
			return v1;
		else
			return v2;
	}

	void balance(TNode<k, v>*& ptr)
	{
		if (ptr == nullptr)
			return;
		if (height(ptr->rightChild) - height(ptr->lefttChild) >-1)

			if (height(ptr->leftChild->leftChild) >= height(ptr->leftChild->rightChild))
				rightRotation(ptr);

			else
				doubleleftrightrotation(ptr);

		else if (height(ptr->rightChild) - height(ptr->leftChild) > 1)

			if (height(ptr->rightChild->rightChild) >= height(ptr->rightChild->leftChild))
				leftRotation(ptr);

			else
				doublerightleftrotation(ptr);

		ptr->height = max(height(ptr->rightChild), height(ptr->leftChild)) + 1;
	}

	void rightRotation(TNode<k, v>*& ptr)
	{
		TNode<k, v>* orphan = ptr->leftChild->rightChild;
		TNode<k, v>* y = ptr->leftChild;
		y->rightChild = ptr;
		ptr->leftChild = orphan;
		ptr->height = height(ptr);
		y->height = height(y);
		ptr = y;
	}

	void leftRotation(TNode<k, v>*& ptr)
	{
		TNode<k, v>* orphan = ptr->rightChild->leftChild;
		TNode<k, v>* y = ptr->rightChild;
		y->leftChild = ptr;
		ptr->rightChild = orphan;
		ptr->height = height(ptr);
		y->height = height(y);
		ptr = y;
	}
	void doubleleftrightrotation(TNode<k, v>*& ptr)
	{
		leftRotation(ptr->leftChild);
		rightRotation(ptr);
	}
	void doublerightleftrotation(TNode<k, v>*& ptr)
	{
		rightRotation(ptr->rightChild);
		leftRotation(ptr);
	}

	TNode<k, v>* search(k const key)
	{
		return search(key, root);
	}
	TNode<k, v>* search(k const key, TNode<k, v>* ptr)
	{
		if (ptr) {
			if (ptr->key < key)
				return search(key, ptr->rightChild);
			else if (ptr->key > key)
				return search(key, ptr->leftChild);
			else
				return ptr;
		}
		return nullptr;
	}

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
	else if (ptr->key < key)
		insertRec(key, value, ptr->rightChild);
	else if (ptr->key > key)
		insertRec(key, value, ptr->leftChild);
	else
		ptr->value = value;
}

template<typename k, typename v>
void BST<k, v>::insert(k const key, v const value) {
	if (!root)
		root = new TNode<k, v>(key, value, nullptr, nullptr);
	else {
		TNode<k, v>* temp = root;
		while (true) {
			if (temp->key == key) {
				temp->value = value;
				break;
			}
			else if (temp->key < key) {
				if (temp->rightChild)
					temp = temp->rightChild;
				else {
					temp->rightChild = new TNode<k, v>(key, value, nullptr, nullptr);
					break;
				}
			}
			else {
				if (temp->leftChild)
					temp = temp->leftChild;
				else {
					temp->leftChild = new TNode<k, v>(key, value, nullptr, nullptr);
					break;
				}
			}
		}
	}
}

template<typename k, typename v>
v* BST<k, v>::search(k const key) {
	return search(key, root);
}

template<typename k, typename v>
v* BST<k, v>::search(k const key, TNode<k, v>* ptr) {

	if (ptr) {

		if (ptr->key < key)
			return search(key, ptr->rightChild);
		else if (ptr->key > key)
			return search(key, ptr->leftChild);
		else
			return &ptr->value;
	}
	return nullptr;
}

template<typename k, typename v>
void BST<k, v>::inorderPrintKeysRec() const {
	inorderPrintKeysRec(root);
	cout << endl;
}


template<typename k, typename v>
void BST<k, v>::inorderPrintKeysRec(TNode<k, v>* ptr) const {
	if (ptr) {
		inorderPrintKeysRec(ptr->leftChild);
		cout << ptr->key << " ";
		inorderPrintKeysRec(ptr->rightChild);
	}

}

template<typename k, typename v>
void BST<k, v>::printAllAncestors(k const key) const {
	TNode<k, v>* tmp = root;
	while (tmp->key != key && tmp) {
		cout << tmp->key << " ";
		if (tmp->key < key)
			tmp = tmp->rightChild;
		else if (tmp->key > key)
			tmp = tmp->leftChild;
	}
	cout << endl;
}

template<typename k, typename v>
int BST<k, v>::length() const {
	return length(root);
}

template<typename k, typename v>
int BST<k, v>::length(TNode<k, v>* ptr) const {
	int count = 0;
	if (ptr) {
		count += length(ptr->leftChild);
		count += 1;
		count += length(ptr->rightChild);
	}
	return count;
}


template<typename k, typename v>
void BST<k, v>::deletep(k const key)
{
	deletep(key, root);
}

template<typename k, typename v>
void BST<k, v>::deletep(k const key, TNode<k, v>*& ptr)
{
	if (ptr)
	{
		if (key > ptr->key)
			deletep(key, ptr->rightChild);
		else if (key < ptr->key)
			deletep(key, ptr->leftChild);
		else
			deleteNode(ptr);
	}
}

template<typename k, typename v>
void BST<k, v>::deleteNode(TNode<k, v>*& ptr)
{
	TNode<k, v>* temp = ptr;
	if (ptr->leftChild == nullptr)
	{
		ptr = ptr->rightChild;
		delete temp;
	}
	else if (ptr->rightChild == nullptr)
	{
		ptr = ptr->leftChild;
		delete temp;
	}
	else
	{
		k d = getPredecessor(ptr->leftChild);
		ptr->key = d;
		deletep(d, ptr->leftChild);
	}
}

template<typename k, typename v>
k BST<k, v>::getPredecessor(TNode<k, v>* ptr)
{
	while (ptr->rightChild != nullptr)
		ptr = ptr->rightChild;
	return ptr->key;
}




int main_2()
{
	BST<int, int> tree; //the key and value both are of type int

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

	tree.deletep(30);
	tree.inorderPrintKeysRec();

	system("pause");
	return 0;
}



int main_1()
{
	AVL<int, int> tree;


	for (int i = 1; i <= 100; i++)
		tree.insertA(i, i);

	for (int i = -1; i >= -100; i--)
		tree.insertA(i, i);

	for (int i = 150; i > 100; i--)
		tree.insertA(i, i);

	for (int i = -150; i < -100; i++)
		tree.insertA(i, i);





	tree.inorderPrintKeysRec();
	cout << endl << endl;
	cout << "Tree Height: " << tree.height() << endl;

	TNode<int, int>* val = tree.search(-100);

	if (val != nullptr)
	{
		cout << "Key= -100 found" << endl;
	}

	val = tree.search(-151);
	if (val == nullptr)
	{
		cout << "Key= -151 not found" << endl;
	}

	system("pause");
	return 0;
}

