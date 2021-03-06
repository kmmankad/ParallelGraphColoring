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
		Adj.push_back(new set<int>);
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
	// STL Set automatically prevents the addition of duplicates
	// so we dont need to explicity worry about that
	Adj[Src]->insert(Dest);
	Adj[Dest]->insert(Src);
}

set<int>* AdjList::GetNeighbors(int NodeNum){
	//TODO: Add check for NodeNum 
	return (Adj[NodeNum]);
}

void AdjList::Print(ostream& OutStream){
	// Print the info
	GraphBase::Print(OutStream);

	// Print the adjacency lists
	for (int i=0; i<NumVertices; i++){
		OutStream << "[" << i << "] -> {";
		set<int>* NeighborSet = GetNeighbors(i);
		set<int>::iterator sit;
		for (sit = (*NeighborSet).begin() ; sit != (*NeighborSet).end(); sit++){
			OutStream << *sit << " , ";
		}
		OutStream << "}" << endl;
	}
}

void AdjList::Print(){
	Print(cout);
}
