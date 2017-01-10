/*
 * Parallel Graph Coloring: 
 * Author: Kartik Mankad 
 * Email: kmankad@ncsu.edu
 * Description: AdjList class is a container to hold graph data
 * 		in the form of Adjacency lists per vertex
 */
#ifndef __ADJLIST
#define __ADJLIST

#include "GraphBase.h"
#include <iostream>
#include <set>
#include <cassert>

using namespace std;

// FIXME: Set a more realistic value
// Currently unused.
#define MAX_GRAPH_SIZE 100

class AdjList : public GraphBase{
	public:
		AdjList(int _NumVertices, int _NumEdges);
		~AdjList();
		void AddEdge(int Src, int Dest);
		set<int>* GetNeighbors(int NodeNum);
		void Print();
		void Print(ostream& OutStream);
	private:
		vector< set<int>* > Adj;
};

#endif // __ADJLIST
