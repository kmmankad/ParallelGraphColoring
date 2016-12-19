#/*
# * Parallel Graph Coloring: 
# * Author: Kartik Mankad 
# * Email: kmankad@ncsu.edu
# * Description: A simple serial implementation of the FirstFit algorithm
# */
#include "FirstFit.h"

/**
 * ColorGraph:
 * @desc  Applies a greedy first-fit serial algorithm to color
 * 	  the given graph (in CSR format)
 * @param NumVertices: Number of vertices in the graph
 * @param NNZ        : Number of non-zero elements in the CSR matrix
 * @param ColIdx[]   : Concatenated adjacency list of each vertex
 * @param RowPtr[]   : Offsets of each vertex in the ColIdx list
 * @param NumColors  : Number of colors used
 * @param ColorVector : A vertex-wise color vector for the entire graph
 * @return none
 */
void ColorGraph(int NumVertices, int NNZ, 
		vector<int> &ColIdx, vector<int> &RowPtr, 
		vector<int> &ColorVector){

	// For all vertices...
	for (int i=0; i<NumVertices; i++){
		// Temp storage for unavailable colors
		// that belong to the vertex's neighbors
		vector <int> NeighborColors;

		// Iterate over its neighbors
		for (int CurrNodeOffset=RowPtr[i]; CurrNodeOffset<RowPtr[i+1] ; CurrNodeOffset++){
			// Mark the neighbor's colors unavailable by
			// pushing them into the NeighborColors vector
			int NodeColor = ColorVector[ColIdx[CurrNodeOffset]];
			NeighborColors.push_back(NodeColor);
		}

		// Now that we know what colors _cant_ be used, 
		// lets find the first color that fits
		bool VertexColored = false;
		int VertexColor = 1; // We init all vertices to color=1

		while(VertexColored != true){
			bool IsNeighborColor = false;
			// Check if the color we're attempting to assign
			// is available
			vector<int>::iterator it;
			for (it = NeighborColors.begin() ; it != NeighborColors.end(); it++){
				if (*it == VertexColor){
					IsNeighborColor = true;
					break;
				}
			}
		
			// If the color we're attempting is not already
			// assigned to one of the neighbors...
			if (IsNeighborColor == false){
				// This is a valid color to assign
				ColorVector[i] = VertexColor;
				VertexColored = true;
				break;
			} else {
				// Try with the next color
				VertexColor++;
			}
		} // end of while(VertexColored !=true)
		// At the end of this while loop, this vertex would be colored.
	}
}
