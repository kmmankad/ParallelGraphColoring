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
	
	// The last entry will be the duplicate of the penultimate entry
	
	RowPtr.push_back(CurrRowPtr);
	
}

bool CSRGraph::VerifyColoring(){
	bool GoodColoring=true;
	// For all the vertices
	for (int i=0; i<NumVertices; i++){
		int VertexColor = ColorVector[i];
		// Iterate over the neighbor vertices
		for (int CurrNodeOffset=RowPtr[i]; CurrNodeOffset<RowPtr[i+1]; CurrNodeOffset++){
			// Get the neighbor's color
			int NeighborColor = ColorVector[ColIdx[CurrNodeOffset]];
			// If the vertices' colors match, error out.
			if ((NeighborColor == VertexColor) && (ColIdx[CurrNodeOffset] != i)){
				GoodColoring=false;
				LogError("Color for Vertex#%0d and neighbor Vertex#%0d match!",i, ColIdx[CurrNodeOffset]);
				goto DoneCheck;
			}
		}
	}
DoneCheck:
	return GoodColoring;


}

void CSRGraph::Print(ostream& OutStream){
	// Print the Graph Info
	GraphBase::Print(OutStream);

	// Print the ColIdx
	vector<int>::iterator it;
	OutStream << "Printing ColIdx : ";
	for (it=ColIdx.begin(); it!=ColIdx.end(); it++){
		OutStream << *it << " , ";
	}
	OutStream << endl;
	
	// Print the RowPtr
	OutStream << "Printing RowPtr : ";
	for (it=RowPtr.begin(); it!=RowPtr.end(); it++){
		OutStream << *it << " , ";
	}
	OutStream << endl;
}

void CSRGraph::Print(){
	Print(cout);
}
