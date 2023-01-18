#include<iostream>
#include<assert.h>
using namespace std;

template<class k, class v>
class HeapItem
{
    k key;
    v value;
public:
    template<class k, class v>
    friend class MinHeap;
    HeapItem()
    {
        key = 0;    //default constructer
        value = 0;
    }
    HeapItem(k ke, v val)
    { 
        this->key = ke;
        this->value = val;   //overlauded cinstructor
    }
   
};

template<class k, class v>
class MinHeap
{
    HeapItem<k, v>* array;
    int capacity;
    int totalItems;
public:

    MinHeap()
    {
        array = nullptr;
        totalItems = 0;   //default constructor
    }
    MinHeap(int capacity)
    {
        this->capacity = capacity;   //overlauded constructor
        array = new HeapItem<k, v>[capacity];
        totalItems = 0;
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return (2 * i + 1);
    }
    int right(int i)
    {
        return (2 * i + 2);
    }
    void heapUp(int root,int last)
    {
        int parent = (last - 1) / 2;
        if (last>root)
        {
            if (array[parent].value > array[last].value)
            {
                swap(array[last], array[parent]);
                heapUp(0,parent);
            }
        }
    }
    void insertNode(k key, v val)
    {
        if (totalItems == capacity)
        {
            capacity = capacity * 2;
            HeapItem<k, v>* temp = new HeapItem<k, v>[capacity];
            for (int i = 0; i < totalItems; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        HeapItem<k, v> temp(key, val);
        totalItems++; 
        array[totalItems - 1] = temp; 
        heapUp(0,totalItems - 1); 
    }

    void printArray()
    {
        for (int i = 0; i < totalItems; ++i)
        {
            cout << array[i].value << " ";
        }
        cout << endl;
    }
    void getMin(v& _value)
    {
        if (totalItems > 0)
            _value = array[0].value;
        else
            assert(totalItems > 0);
    }
    bool Isempty()
    {
        if (totalItems == 0)
            return true;
        else
            return false;
    }
   /* void heapify(int i)
    {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < totalItems && array[l] < array[smallest])
            smallest = l;


        if (r < totalItems && array[r] < array[smallest)
            smallest = r;


        if (smallest != i)
        {
            swap(array[i], array[smallest]);
            heapify(smallest);
        }
    }*/
    void MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < totalItems && array[l].value < array[i].value)
            smallest = l;
        if (r < totalItems && array[r].value < array[smallest].value)
            smallest = r;
        if (smallest != i)
        {
            swap(array[i], array[smallest]);
            MinHeapify(smallest);
        }
    }
    
    void deleteMin()
    {
        if (totalItems<=0)
            return;
        
        k lastkey = array[totalItems - 1].key;
        v lastvalue = array[totalItems - 1].value;
        HeapItem<k, v> temp(lastkey, lastvalue);
        array[0] = temp;
        totalItems = totalItems - 1;
        MinHeapify(0);
    }

    ~MinHeap()
    {
        delete[] array;
        
    }

};
int main_1()
{
    MinHeap<int, int> H(10);
    
    H.insertNode(10, 10);
    H.insertNode(20, 20);
    H.insertNode(30,30);
    H.insertNode(40,40);
    H.printArray();
    H.deleteMin();
    
    
    H.printArray();
    int n; 
    H.getMin(n);
    cout << n << endl;
    system("pause");
    return 0;
}

