#include<iostream>
#include<vector>
#include<fstream>
#include<list>
using namespace std;
class Graph
{
    list<int>* adj;
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
            int vertix, edge;
            MyFile >> V;

            adj = new list<int>[V];
            while (!MyFile.eof())
            {
                MyFile >> vertix >> edge;
                adj[vertix-1].push_back(edge);
                adj[edge-1].push_back(vertix);
            }
            MyFile.close();
        }
    }
    void Print()
    {
        list<int>::iterator j;
        for (int i = 0; i < V; i++)
        {
            cout << i + 1 << ". ";
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
        for (int i = 0; i < V; i++)
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
        for (j = adj[key - 1].begin(); j != adj[key - 1].end(); j++)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
   /* ~Graph()
    {
        delete adj;
    }*/
    void DFS(int v)
    {

        bool* visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        DFSHelp(v-1, visited);
    }
    void DFSHelp(int v, bool visited[])
    {
        // Mark the current node as visited and
        // print it
        visited[v] = true;
        cout << v+1 << " ";
        // Recur for all adjacent vertices
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i) {

            if (!visited[*i])
                DFSHelp(*i, visited);

        }
    }
    void DFS()
    {

        bool* visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                DFSHelpRec(i, visited);

        delete[]visited;
    }
    void DFSHelpRec(int v, bool visited[])
    {
        // Mark the current node as visited and
        // print it
        visited[v] = true;
        cout << v+1 << " ";
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
    G.DFS();


    return 0;
}