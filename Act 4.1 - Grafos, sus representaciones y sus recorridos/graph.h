/*
 *
 * Programación de estructuras de datos y algoritmos fundamentales (TC1031.2)
 * Formativa 4.1 - Grafo como matriz de Adyacencia y recorridos (DFS BFS)
 * Olivia Araceli Morales Quezada
 * A01707371
 *
*/


#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;
		//vector<Type> *vect = new vector<Type>

public:
		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjMatrix(int, int);
    void addEdgeAdjList(int, int);
		string printAdjMat();
    string printAdjList();
		bool contains(list<int>, int);

    //Metodos tarea
    void loadGraphList(string, int, int);
    string DFS(int, int);
    string BFS(int, int);

    //Auxiliares
    string DFS_help(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
    string BFS_help(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
    string print_path(vector<vector<int>>&, int, int);
    string print_visited(list<int>);
    
    
};

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjMatrix(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[v].push_back(u);
	adjList[u].push_back(v);
	edgesList++;
}

void Graph::loadGraphList(string name, int a, int b){
	adjList = new vector<int> [a];
	nodes = a;

	string line;
	ifstream lee (name);
  int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1));
				v = stoi(line.substr(4));
				addEdgeAdjList(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

string Graph::printAdjList(){
	  stringstream aux;
    for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(),adjList[i].end());
	  }
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::DFS(int start, int goal){
  stringstream aux;
  stack <int> st;
	list <int> visited;
	vector <vector<int>> path(nodes, vector<int>(1, -1));
	st.push(start);
	aux << DFS_help(start, goal, st, visited, path);
  aux << print_visited(visited) << print_path(path, start, goal);
  return aux.str();
}

string Graph::DFS_help(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths){
  stringstream aux;
  if(current == goal){
			aux << print_visited(visited);
		} else if(st.empty()){
			cout << " node not found";
		}	else {
			current = st.top();
			st.pop();
			visited.push_back(current);
			for(int  i = 0; i < adjList[current].size(); i++)
				if(!contains(visited, adjList[current][i])){
					st.push(adjList[current][i]);
					paths[adjList[current][i]][0] = current;
				}
			DFS_help(current, goal, st, visited, paths);
		}
    return aux.str();

}

string Graph::BFS(int start, int goal){
  stringstream aux;
	queue <int> qu;
	list <int> visited;
  vector <vector<int>> paths(nodes, vector<int>(0));
	qu.push(start);
  aux << BFS_help(start, goal, qu, visited, paths);
  aux << print_visited(visited) << print_path(paths, start, goal);
  return aux.str();
}

string Graph::BFS_help(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &paths){
  stringstream aux;
	if(current == goal){
			print_visited(visited);
		} else if(qu.empty()){
			cout << " node not found";
		}	else {
			current = qu.front();
			qu.pop();
			visited.push_back(current);
			for(int  i = 0; i < adjList[current].size(); i++)
				if(!contains(visited, adjList[current][i])){
					qu.push(adjList[current][i]);
					paths[adjList[current][i]].push_back(current);
				}
			BFS_help(current, goal, qu, visited, paths);
		}
  return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
  stringstream aux;
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	aux << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top();
		reverse.pop();
  }
  //aux << endl;
  return aux.str();
  
}

string Graph::print_visited(list<int> visited){
	stringstream aux;
  aux << "visited: ";
	while (!visited.empty()){
    aux << visited.front() << " ";
    visited.pop_front();
  }
  //aux << endl;
  return aux.str();
}
#endif /* Graph_H_ */