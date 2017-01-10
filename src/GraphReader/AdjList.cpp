/*
 * Parallel Graph Coloring: 
 * Author: Kartik Mankad 
 * Email: kmankad@ncsu.edu
 * Description: AdjList class is a container to hold graph data
 * 		in the form of Adjacency lists per vertex
 */
#include "AdjList.h"

// Constructor
AdjList::AdjList(int _NumVertices, int _NumEdges):GraphBase(_NumVertices, _NumEdges){
	// Init the Adj container
	for (int i=0; i<NumVertices; i++){
		Adj.push_back(new vector<int>);
	}
}

// Destructor
AdjList::~AdjList(){
}

// Function to add edges
void AdjList::AddEdge(int Src, int Dest){
	// TODO: Add check for number of vertices not
	// exceeeding max graph size
	
	// We need to subtract Src and Dest Node numbers as MatrixMarket is 1-indexed
	Src--;
	Dest--;

	// Add the links from Src->Dest
	// and Dest->Src
	Adj[Src]->push_back(Dest);
	Adj[Dest]->push_back(Src);
}

vector<int>* AdjList::GetNeighbors(int NodeNum){
	//TODO: Add check for NodeNum 
	return (Adj[NodeNum]);
}

void AdjList::Print(){
	// Print the info
	GraphBase::Print();

	// Print the adjacency lists
	for (int i=0; i<NumVertices; i++){
		cout << "[" << i << "] -> {";
		vector<int>* NeighborVec = GetNeighbors(i);
		for (int j=0; j< (*NeighborVec).size(); j++){
			cout << (*NeighborVec)[j] << " , ";
		}
		cout << "}" << endl;
	}
}
