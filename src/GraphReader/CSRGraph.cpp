/*
 * Parallel Graph Coloring: 
 * Author: Kartik Mankad 
 * Email: kmankad@ncsu.edu
 * Description: CSRGraph class is a container to hold graph data
 * 		in the CSR (Compressed Sparse Row) format. This class
 * 		derives from GraphBase.
 */
#include "CSRGraph.h"

// Constructor
CSRGraph::CSRGraph(int _NumVertices, int _NumEdges):GraphBase(_NumVertices, _NumEdges){
		// According to https://en.wikipedia.org/wiki/Sparse_matrix
		// the first element of the RowPtr vector is fixed at 0.
		// There will be NNZ more entries
		CurrRowPtr = 0;

}

void CSRGraph::AddAdjList(vector<int>* Neighbors){
	// Add the offset to RowPtr
	RowPtr.push_back(CurrRowPtr);
	CurrRowPtr += Neighbors->size();

	// Add this adjacencylist to ColIdx
	vector<int>::iterator it;
	for (it = Neighbors->begin(); it != Neighbors->end(); it++){
		ColIdx.push_back(*it);
	}	
}

void CSRGraph::DoneAdjList(){
	//TODO: Verify that we have the right number of entries
	
	// The last entry has to be NNZ
	RowPtr.push_back(NumEdges);
}

// Print the graph with info
void CSRGraph::Print(){
	GraphBase::Print();
}

