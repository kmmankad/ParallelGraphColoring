/*
 * Parallel Graph Coloring: 
 * Author: Kartik Mankad 
 * Email: kmankad@ncsu.edu
 * Description: CSRGraph class is a container to hold graph data
 * 		in the CSR (Compressed Sparse Row) format. This class
 * 		derives from GraphBase.
 */
#ifndef __CSRGRAPH
#define __CSRGRAPH

#include "GraphBase.h"
#include <iostream>
#include <vector>

using namespace std;

class CSRGraph: public GraphBase{

	public:
		CSRGraph(int _NumVertices/*m*/, int _NumEdges/*NNZ*/);
		~CSRGraph();
		vector<int> ColIdx;
		vector<int> RowPtr;
		void AddAdjList(vector<int>* Neighbors);
		void DoneAdjList();
		void Print();
	private:
		int CurrRowPtr;
};

#endif // __CSRGRAPH
