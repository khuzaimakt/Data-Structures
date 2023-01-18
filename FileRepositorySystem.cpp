#include<iostream>

#include<vector>
#include<string>
#include<list>
#include<fstream>
#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
using namespace std;

template<typename  v>
class HeapItem
{
public:
    v key;
    int id;
    char status;
    bool access;

    template<typename v>
    friend class MaxHeap;


    HeapItem()
    {
        key = 0;    //default constructer
        access = false;
        id = 0;
        status = '-';

    }
    HeapItem(v ke, int id, char status)
    {
        this->key = ke;
        this->id = id;
        this->status = status;
        this->access = access;

        //overlauded cinstructor
    }
    HeapItem(const HeapItem<v>& H)
    {
        this->key = H.key;
        this->id = H.id;
        this->status = H.status;
        this->access = H.access;
    }
    void PrintItem()
    {
        cout << key << " " << status << " " << id << endl;
    }
};

template<typename v>
class MaxHeap
{
public:
    vector<HeapItem<v>> MaxHeapVector;
    int totalItems;

    HeapItem<v> min;
    template<typename v>
    friend class HashItem;

    MaxHeap()
    {

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
    void buildheap(HeapItem<int> a[], int total)
    {

        for (int i = (total / 2) - 1; i >= 0; i--)
        {
            heapifymax(a, total, i);
        }
        for (int i = 0; i < total; i++)
        {
            MaxHeapVector.push_back(a[i]);
            totalItems++;
        }
        setMin();
    }
    void heapUp(int root, int last)
    {
        int parent = (last - 1) / 2;
        if (last > root)
        {
            if (MaxHeapVector[parent].key < MaxHeapVector[last].key)
            {
                swap(MaxHeapVector[last], MaxHeapVector[parent]);
                heapUp(0, parent);
            }
        }
    }
    void insert(v key, int id, char status)
    {

        HeapItem<v> temp(key, id, status);
        totalItems++;
        MaxHeapVector.push_back(temp);
        heapUp(0, totalItems - 1);
        setMin();
    }
    void printHeap()
    {
        for (int i = 0; i < totalItems; ++i)
        {
            cout << MaxHeapVector[i].key << " ";
            cout << MaxHeapVector[i].id << " ";
            cout << MaxHeapVector[i].status << " ";
        }
        cout << endl << endl;;
    }
    void heapifymax(HeapItem<int> arr[], int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;


        if (l < n && arr[l].key > arr[largest].key)
            largest = l;


        if (r < n && arr[r].key > arr[largest].key)
            largest = r;


        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifymax(arr, n, largest);
        }
    }
    void heapifymin(vector<HeapItem<v>>& arr, int n, int i)
    {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;


        if (l < n && arr[l] < arr[smallest])
            smallest = l;


        if (r < n && arr[r] < arr[smallest])
            smallest = r;


        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            heapifymin(arr, n, smallest);
        }
    }
    HeapItem<v> getMax()
    {
        if (totalItems > 0)
            return  MaxHeapVector[0];

    }
    HeapItem<v> getMin()
    {

        if (totalItems > 0)
        {
            if (totalItems == 1)
            {
                return MaxHeapVector[0];
            }
            return min;
        }
    }
    void setMin()
    {

        if (totalItems > 0)
        {
            MaxHeap<v> temp;
            for (int i = 0; i < MaxHeapVector.size(); i++)
            {
                temp.MaxHeapVector.push_back(MaxHeapVector[i]);
                temp.totalItems++;
            }
            temp.MinHeap();
            min = temp.MaxHeapVector[0];
        }
    }
    void MinHeap()
    {
        int n = totalItems;
        int i = (n - 2) / 2;
        while (i >= 0) {
            MinHeapify(i);
            i--;
        }
    }
    bool Isempty()
    {
        if (totalItems == 0)
            return true;
        else
            return false;
    }
    bool Isnotempty()
    {
        if (totalItems >= 1)
        {
            return true;
        }
        if (totalItems == 0)
        {
            return false;
        }
    }
    void MaxHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < totalItems && MaxHeapVector[l].key > MaxHeapVector[i].key)
            largest = l;
        if (r < totalItems && MaxHeapVector[r].key > MaxHeapVector[largest].key)
            largest = r;
        if (largest != i)
        {
            swap(MaxHeapVector[i], MaxHeapVector[largest]);
            MaxHeapify(largest);
        }
        setMin();
    }
    void MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < totalItems && MaxHeapVector[l].key < MaxHeapVector[i].key)
            smallest = l;
        if (r < totalItems && MaxHeapVector[r].key < MaxHeapVector[smallest].key)
            smallest = r;
        if (smallest != i)
        {
            swap(MaxHeapVector[i], MaxHeapVector[smallest]);
            MinHeapify(smallest);
        }
    }
    HeapItem<v> ExtractMax()
    {
        HeapItem<v> max = MaxHeapVector[0];

        if (totalItems == 1)
        {
            totalItems--;
            MaxHeapVector.pop_back();
            return max;
        }

        HeapItem<v> lastkey = MaxHeapVector[totalItems - 1];
        HeapItem<v> temp(lastkey);
        MaxHeapVector[0] = temp;
        MaxHeapVector.pop_back();
        totalItems = totalItems - 1;
        MaxHeapify(0);

        return max;
    }

    ~MaxHeap()
    {

    }
};


template<typename v>
class HashItem
{
private:
    int FileID;
  
    MaxHeap<int> H;
    MaxHeap<int> tracker;

    bool access;
   
public:
    template<typename v>
    friend class HashTable;
    HashItem(int FileID = NULL, bool access = false) : FileID(FileID), access(access){};
    ~HashItem()
    {
      
    }

};


template<typename v>
class HashTable
{
private:
    vector<list<HashItem<v>>> hashVector;

    int currentElements;
    int HashFunc(int key)
    {
        return key % hashVector.size();
    }

public:
    HashTable()
    {
        hashVector.resize(10);
        currentElements = 0;
    }
    HashTable(int const capacity)
    {

        hashVector.resize(capacity);
        currentElements = 0;

    }
    void insert(int FileID)
    {
        
        int idx = HashFunc(FileID);
        typename list<HashItem<v>>::iterator i;
        bool found = false;
        for (i = hashVector[idx].begin(); i != hashVector[idx].end() && !found; ++i) { 
            if (i->FileID == FileID) {
                found = true;
                break;
            }
        }
        if (!found) { 
            HashItem<v> item(FileID);

            hashVector[idx].push_back(item);
        }
        else
            cout << "File with file ID " << FileID << " already exists." << endl;

    }

    void request(int FileID, int UserID, int Priority, char status)
    {
        int index = HashFunc(FileID);
       
        typename list<HashItem<v>>::iterator en;
        bool found = false;
        for (en = hashVector[index].begin(); en != hashVector[index].end() && !found; ++en) { // find the given fileID
            if (en->FileID == FileID) {
                found = true;
                break;
            }
        }
        if (found)
        {
            if (en->H.Isempty())
            {
                if (en->tracker.Isempty())
                {
                    en->tracker.insert(Priority, UserID, status);

                    en->access = true;
                    return;
                }
                else if (en->tracker.getMax().status == 'R' && status == 'R')
                {
                    en->tracker.insert(Priority, UserID, status);
                    en->access = true;
                    return;
                }
                else
                {
                    en->H.insert(Priority, UserID, status);
                    return;
                }
            }

            else if (Priority >= en->H.getMax().key)
            {
                if (en->tracker.Isempty())
                {
                    en->tracker.insert(Priority, UserID, status);

                    en->access = true;
                    return;
                }
                else if (en->tracker.getMax().status == 'R' && status == 'R')
                {
                    en->tracker.insert(Priority, UserID, status);

                    en->access = true;
                    return;
                }

                en->H.insert(Priority, UserID, status);
                return;
            }
            else if (Priority > en->H.getMax().key)
            {
                if (en->tracker.Isempty())
                {
                    en->tracker.insert(Priority, UserID, status);
                    en->H.insert(Priority, UserID, status);
                    en->access = true;
                    return;
                }
                else
                {
                    en->H.insert(Priority, UserID, status);
                    return;
                }
            }
            else
            {
                en->H.insert(Priority, UserID, status);
                return;
            }



        }
        else
        {
            cout << "File Not Found" << endl;
            return;
        }


    }
    void request(int FileID, int UserID,char Priority, char status)
    {
        int index = HashFunc(FileID);
      
        typename list<HashItem<v>>::iterator en;
        bool found = false;
        for (en = hashVector[index].begin(); en != hashVector[index].end() && !found; ++en) 
        { 
            if (en->FileID == FileID) {
                found = true;
                break;
            }
        }
        if (found)
        {
            if (en->H.Isempty())
            {
                if (Priority == 'H')
                {
                    
                    request(FileID, UserID,100, status);
                    return;
                }
                else if (Priority == 'L')
                {
                    int min = en->H.getMin().key - 1;
                    request(FileID,UserID,0, status);
                    return;
                }

            }
            if (Priority == 'H')
            {
                int max = en->H.getMax().key + 1;
                request(FileID,UserID,max, status);
                return;
            }
            else if (Priority == 'L')
            {
                int min = en->H.getMin().key - 1;
                request(FileID, UserID,min, status);
                return;
            }
        }
        else
        {
            cout << "File Not Found" << endl;
            return;
        }


    }
    void release(int FileID, int UserID)
    {
        int index = HashFunc(FileID);
        typename list<HashItem<v>>::iterator en;
        bool found = false;
        for (en = hashVector[index].begin(); en != hashVector[index].end() && !found; ++en) { 
            if (en->FileID == FileID) {
                found = true;
                break;
            }
        }

        if (found)
        {
            if (en->tracker.Isempty())
            {
                cout << "Nobody is currently accessing the file " << FileID << endl;
                return;

            }
            if (en->tracker.Isnotempty())
            {
                if (en->tracker.getMax().id == UserID)
                {
                    en->tracker.ExtractMax();


                    if (en->tracker.Isempty())
                    {
                        en->access = false;
                        if (en->H.totalItems >= 1)
                        {
                            if (en->H.getMax().status == 'W')
                            {


                                this->request(FileID, en->H.getMax().id, en->H.getMax().key, en->H.getMax().status);
                                en->H.ExtractMax();
                                return;


                            }
                            else if (en->H.MaxHeapVector[0].status == 'R')
                            {

                                while (en->H.MaxHeapVector[0].status == 'R')
                                {
                                    this->request(FileID, en->H.MaxHeapVector[0].id, en->H.MaxHeapVector[0].key ,en->H.MaxHeapVector[0].status);
                                    en->H.ExtractMax();
                                }

                                return;
                            }
                        }
                        else
                        {
                            cout << "No user in waiting queue " << endl;
                            return;
                        }


                    }
                    else
                    {
                        cout << UserID << " isn't accessing the file currently hence can't be released" << endl;
                        return;
                    }
                }
            }




        }
        else
            cout << "File not found" << endl;
    }
    void remove(int FileID)
    {
        int index = HashFunc(FileID);
        bool found = false;
        
        typename list<HashItem<v>>::iterator en;
        for (en = hashVector[index].begin(); en != hashVector[index].end() && !found; ++en) { 
            if (en->FileID == FileID) {
                found = true;
                break;
            }
        }
        if(found)
        {
            if (en->access == false)
            {
                hashVector[index].erase(en);
            }
        }
    }



    
    void print()
    {
        typename list<HashItem<v>>::iterator ptr;
        
        for (int i = 0; i < hashVector.size(); i++) {
            cout << "H" << i + 1 << "   ";
            cout << "   ->";
            for ( ptr = hashVector[i].begin(); ptr != hashVector[i].end(); ptr++)
            {
                if (ptr->H.totalItems == 0 && ptr->tracker.Isempty())
                {
                    cout << ptr->FileID << "...";
                    cout << " Access granted to none" << endl;
                    cout << "Next None" << endl;
                    cout << "Waiting None" << endl;

                }
                else if (ptr->H.totalItems >= 1 && ptr->tracker.Isempty())
                {
                    cout << ptr->FileID << "...";
                    cout << "Access granted to None  " << endl;

                    if (ptr->H.totalItems >= 1)
                    {
                        cout << "Next User " << ptr->H.MaxHeapVector[0].id << "," << ptr->H.MaxHeapVector[0].status << endl;
                        cout << "Waiting " << ptr->H.totalItems << " Users" << endl;
                    }
                    if (ptr->H.totalItems == 0)
                    {
                        cout << "Next None" << endl;
                        cout << "Waiting None" << endl;
                    }

                }
                else
                {
                    cout << ptr->FileID << "...";
                    cout << "Access granted to User  ";
                    for (int i = 0; i < ptr->tracker.totalItems; i++)
                        cout << ptr->tracker.MaxHeapVector[i].id << "," << ptr->tracker.MaxHeapVector[i].status << ", ";
                    cout << endl;
                    if (ptr->H.totalItems >= 1)
                    {
                        cout << "Next User " << ptr->H.MaxHeapVector[0].id << "," << ptr->H.MaxHeapVector[0].status << endl;
                        cout << "Waiting " << ptr->H.totalItems << " Users" << endl;
                    }
                    if (ptr->H.totalItems == 0)
                    {
                        cout << "Next None" << endl;
                        cout << "Waiting None" << endl;
                    }



                }




            }

            cout << endl;
        }

    }
    void load(string filename)
    {
        ifstream fin(filename);

        if (fin.good()) {
            string line;

            getline(fin, line);

            int fileID, userID, priority;
            int comma_idx;
            char mode;
            HeapItem<v> user;
            while (!fin.eof()) {

                getline(fin, line); 

                comma_idx = line.find(","); 
                fileID = stoi(line.substr(0, comma_idx));
                line = line.substr(comma_idx + 1, line.size());

                comma_idx = line.find(",");
                userID = stoi(line.substr(0, comma_idx));
                line = line.substr(comma_idx + 1, line.size());

                comma_idx = line.find(",");
                priority = stoi(line.substr(0, comma_idx)); 
                line = line.substr(comma_idx + 1, line.size());

                
                mode = line[line.size() - 1];


                if (fileID < 5000 || fileID > 100000) 
                    cout << "invalid fileID in file " << filename << endl;
                else if (userID < 0 || userID > 10000)
                    cout << "invalid userID in file " << filename << endl;
                else if (priority < 0 || priority > 100)
                    cout << "invalid priority in file " << filename << endl;
                else if (mode != 'R' && mode != 'W')
                    cout << "invalid mode for user in file " << filename << endl;
                else {
                    insert(fileID);

                    request(fileID, userID,priority, mode);
                }

            }
        }
        else
            cout << "No file exists with filename: " << filename << endl;
    }
    ~HashTable()
    {

    }

};




int main_12()
{
    HashTable<int>hash;
   
   
    int Priority, UserID;
      char status;
      int FileID;
      int c;
      char p;
      string filename;
      while (1) {
          cout << "1.Insert FileID into the table" << endl;
          cout << "2.Print Hash Table Info" << endl;
          cout << "3.Delete FileID from the table" << endl;
          cout << "4.Load Data:" << endl;
          cout << "5.Request Access for a file" << endl;
          cout << "6.Release Access for a file" << endl;
          cout << "7.Exit " << endl;
          cout << "Enter your choice: ";
          cin >> c;
          switch (c) {
          case 1:
              cout << "Enter FileID to be inserted in the range(5000-99999): ";
              cin >> FileID;

              if (FileID >= 5000 && FileID <= 99999)
                  hash.insert(FileID);
              system("pause");
              system("cls");
              break;
          case 2:
              hash.print();
              system("pause");
              system("cls");
              break;
          case 3:
              cout << "Enter FileID to be deleted in the range(5000-99999): ";
              cin >> FileID;
              if (FileID >= 5000 && FileID <= 99999)
                  hash.remove(FileID);
              system("pause");
              system("cls");
              break;
          case 4:

              cout << "Filename to insert from: ";
              cin >> filename;

              hash.load(filename);
              system("pause");
              system("cls");
              break;

          case 5:
              int choice;
              cout << "Press 1 for integer priority or press 2 for (H/L) priority:" << endl;
              cin >> choice;
              if (choice == 1)
              {
                  cout << "Enter File ID in the range(5000-99999):" << endl;
                  cin >> FileID;
                  cout << "Enter User ID in the range(0-10000):" << endl;
                  cin >> UserID;
                  cout << "Enter Priority key in the range(0-100):" << endl;
                  cin >> Priority;
                  
                  cout << "Enter Status (R for Read, W for Write):" << endl;
                  cin >> status;
                  if (FileID >= 5000 && FileID <= 99999 && Priority >= 0 && Priority <= 100 && UserID >= 0 && UserID <= 10000 && (status == 'W' || status == 'R'))
                      hash.request(FileID, UserID,Priority, status);
              }
              if (choice == 2)
              {
                  cout << "Enter File ID in the range(5000-99999):" << endl;
                  cin >> FileID;
                  cout << "Enter Priority key (H/L):" << endl;
                  cin >> p;
                  cout << "Enter User ID in the range(0-10000):" << endl;
                  cin >> UserID;
                  cout << "Enter Status (R for Read, W for Write):" << endl;
                  cin >> status;
                  if (FileID >= 5000 && FileID <= 99999 && (p=='H' ||p=='L') && UserID >= 0 && UserID <= 10000 && (status == 'W' || status == 'R'))
                      hash.request(FileID, UserID,p, status);
              }
              system("pause");
              system("cls");
              break;
          case 6:
              cout << "Enter File ID in the range(5000-99999):" << endl;
              cin >> FileID;

              cout << "Enter User ID in the range(0-10000):" << endl;
              cin >> UserID;

              if (FileID >= 5000 && FileID <= 99999 && UserID >= 0 && UserID <= 10000)
                  hash.release(FileID, UserID);
              system("pause");
              system("cls");
              break;
          case 7:
              exit(1);
          default:
              cout << "\nEnter correct option\n";
          }
      }
    system("pause");
    return 0;
}
