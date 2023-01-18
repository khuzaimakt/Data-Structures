

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

class Graph {
	vector<list<int>> GraphAdjacency;	  
	int v;								

	void list_Print(list<int> const& list) {
		for (auto it = list.cbegin(); it != list.cend(); it++)
			cout << *it << " ";
	}

	void DFSHelp(int v, bool visited[]) {
		visited[v] = true;
		cout << v << " ";
		list<int>::iterator i;
		for (i = GraphAdjacency[v].begin(); i != GraphAdjacency[v].end(); i++)
			if (!visited[*i])
				DFSHelp(*i, visited);
	}
public:

	Graph(int s = 10) {
		while (s < 1) {
			cout << "Size cannot be smaller than 1.\nEnter te size: " << endl;
			cin >> s;
		}
		v = s + 1;
		GraphAdjacency.resize(v);
	}
	//Function to add an edge into the graph.
	void addEdge(int vertex, int edge) {
		GraphAdjacency[vertex].push_back(edge);
		GraphAdjacency[edge].push_back(vertex);
	}

	void readFile(string path) {
		int a = 0; // element1
		int b = 0; // element2
		ifstream fin(path);
		fin >> v;				//first line has number of vertices.
		v += 1;
		while (!fin.eof()) {
			fin >> a;
			fin >> b;
			addEdge(a, b);
		}


		fin.close();
	}
	void print() {
		int i = 1;
		while (i < v) {
			cout << i << "-> ";
			list_Print(GraphAdjacency[i]);
			cout << endl;
			i++;
		}
	}
	int inDegree(int vertex) { return GraphAdjacency[vertex].size(); } 	//undirected graph
	int outDegree(int vertex) { return GraphAdjacency[vertex].size(); }       //undirected graph
	//Function to print the neighbour of a given vertex.
	void printNeighbours(int vertex) {
		cout << vertex << "'s neighbour is ";
		list_Print(GraphAdjacency[vertex]);
		cout << endl;
	}

	void DFS(int v) {
		bool* visited = new bool[this->v];
		for (int i = 1; i < this->v; i++)
			visited[i] = false;
		DFSHelp(v, visited);
	}
	//destructor.
	~Graph() {
		int i = 0;
		while (i < v) {
			GraphAdjacency[i].clear();		//delete the lists
			i++;
		}
		GraphAdjacency.clear();			   //delete the vector
	}
};

int main_4() {
	Graph g;
	g.readFile("graph.txt");
	g.print();
	
	return 0;
}