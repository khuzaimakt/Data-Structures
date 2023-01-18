#include<iostream>
#include<vector>
#include<fstream>
#include<list>
using namespace std;
class Graph
{
    vector<list<int>> adj;
    int V;
public:
    void Read_File(string F)
    {
        ifstream MyFile;
        MyFile.open(F, ios::in);
        if (!MyFile)
        {
            cout << "File not Found " << endl;
        }
        else
        {
            int temp, vertix, edge;
            MyFile >> V;

            V += 1;
            temp = V + 1;
           adj.resize(temp);
            while (!MyFile.eof())
            {
                MyFile >> vertix >> edge;
                adj[vertix].push_back(edge);
                adj[edge].push_back(vertix);
            }
            MyFile.close();
        }
    }
    void Print()
    {
        list<int>::iterator j;
        for (int i = 0; i < adj.size(); i++)
        {
            cout << i << ". ";
            for (j = adj[i].begin(); j != adj[i].end(); j++)
            {
                cout << *j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    void Degree()
    {
        list<int>::iterator j;
        for (int i = 0; i < adj.size(); i++)
        {
            cout << i << ". ";
            int temp = 0;
            for (j = adj[i].begin(); j != adj[i].end(); j++)
            {
                temp++;
            }
            cout << temp << endl;
        }
    }
    void Print_neighbours(const int key)
    {
        list<int>::iterator j;
        cout << "Neighbours of " << key << ": ";
        for (j = adj[key].begin(); j != adj[key].end(); j++)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
    ~Graph()
    {
        adj.clear();
    }
    void DFS(int v)
    {
        bool* visited = new bool[this->V];
        for (int i = 1; i < this->V; i++)
            visited[i] = false;
        DFSHelp(v, visited);
        
    }
    void DFSHelp(int v, bool visited[])
    {
        visited[v] = true;
        cout << v << " ";
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); i++)
            if (!visited[*i])
                DFSHelp(*i, visited);
    }
    void DFS()
    {

        bool* visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        for (int i = 1; i < V; i++)
            if (visited[i] == false)
                DFSHelpRec(i, visited);

        delete[]visited;
    }
    void DFSHelpRec(int v, bool visited[])
    {
        // Mark the current node as visited and
        // print it
        visited[v] = true;
        cout << v << " ";
        // Recur for all the vertices adjacent
        // to this vertex
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i) {

            if (!visited[*i])
                DFSHelpRec(*i, visited);

        }
    }

   


};
int main()
{
    string file = "graph.txt";
    Graph G;
    G.Read_File(file);
    cout << "Graph:" << endl << endl;
    G.Print();
    cout << "Degrees of graph: " << endl << endl;
    G.Degree();
    cout << "Neighbour:" << endl << endl;
    G.Print_neighbours(2);
    cout << "Depth First Search" << endl << endl;
    G.DFS(2);
   

    return 0;
}

