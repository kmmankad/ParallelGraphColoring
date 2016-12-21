#ifndef __FIRSTFIT
#define __FIRSTFIT
/*
# * Parallel Graph Coloring: 
# * Author: Kartik Mankad 
# * Email: kmankad@ncsu.edu
# * Description: A simple serial implementation of the FirstFit algorithm
# */
#include <iostream>
#include <vector>

using namespace std;

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
		vector<int> &ColorVector);

#endif // __FIRSTFIT
