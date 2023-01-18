#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

template<typename v>
struct HashItem
{
	int key;
	v value;
	HashItem* next;

	HashItem(int key = NULL, v value = NULL, HashItem* next = nullptr) : key(key), value(value), next(next) {};
};

template<typename v>
class HashMap {
private:
	vector<HashItem<v>> hashVector;
	int currentElements;

	int	hashKey(int key) const
	{
		return key % hashVector.size();
	}
public:
	HashMap()
	{
		hashVector.resize(10, v());
		currentElements = 0;
	}
	HashMap(int const capacity)
	{
		assert(capacity > 1);
		hashVector.resize(capacity, v());
		currentElements = 0;
	}
	void insert(int const key, v const value)
	{
		
		int index = hashKey(key);
		HashItem<v>* en = &hashVector[index];
		while (en->next != nullptr)
		{
			en =en->next;
		}
		en->next = new HashItem<v>(key, value);
		currentElements++;
	}
	bool deleteKey(int const key)
	{
		int index = hashKey(key);
		HashItem<v>* tempdel = &hashVector[index];
		while (tempdel != nullptr && tempdel->key != key)
		{
			tempdel = tempdel->next;
		}
		if (tempdel)
			tempdel->key = -1;
		currentElements--;
		return tempdel;
	}
	v* get(int const key)
	{
		int index = hashKey(key);
		HashItem<v>* toget = &hashVector[index];
		while (toget != nullptr && toget->key != key)
		{
			toget = toget->next;
		}
		if (toget)
			return &toget->value;
		else
			return nullptr;
	}
	void printTable() const
	{
		int size = hashVector.size();
		for (int i = 0; i < size; i++) {
			cout << i << "   ";
			cout << "   ->";
			for (HashItem<v>* ptr = hashVector[i].next; ptr != nullptr; ptr = ptr->next)
				cout << ptr->key << ":" << ptr->value << "->";
			cout << endl;
		}
	}
	~HashMap()
	{
		hashVector.~vector();
		currentElements = 0;
	}
};



int main_7()
{

	HashMap<int> H;

	H.insert(1, 1);
	H.insert(81, 81);
	H.insert(4, 4);
	H.insert(64, 64);
	H.insert(25, 25);
	H.insert(16, 16);
	H.insert(36, 36);
	H.insert(9, 9);
	H.insert(49, 49);
	H.printTable();
	cout << endl << endl;
	int* val = H.get(64);
	if (val)
		cout << "Value at key 64: " << *val << endl << endl;
	else
		cout << "Key: 64 does not exist." << endl << endl;

	val = H.get(88);
	if (val)
		cout << "Value at key 88: " << *val << endl << endl;
	else
		cout << "Key: 88 does not exist." << endl << endl;

	if (H.deleteKey(1))
		cout << "Key 1 deleted successfully." << endl << endl;
	else
		cout << "Key: 1 does not exist." << endl << endl;

	if (H.deleteKey(64))
		cout << "Key 64 deleted successfully." << endl << endl;
	else
		cout << "Key: 64 does not exist." << endl << endl;

	if (H.deleteKey(77))
		cout << "Key 77 deleted successfully." << endl << endl;
	else
		cout << "Key: 77 does not exist." << endl << endl;

	H.printTable();
	cout << endl << endl;

	//HashMap<int> H2(0);
	/*HashMap<int> H3(10);*/
	return 0;
	
	
}