/*
 * Parallel Graph Coloring: 
 * Author: Kartik Mankad 
 * Email: kmankad@ncsu.edu
 * Description: GraphReader class is a basic MTX (matrixmarket) graph reader
 * 		that stores the read file in:
 * 		- Adjacency Lists
 * 		- CSR (Compressed Sparse Row) format
 */
#ifndef __GRAPHREADER
#define __GRAPHREADER

#include <iostream>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Common.h"
#include "AdjList.h"
#include "CSRGraph.h"

using namespace std;

class GraphReader{
	
	public:
		GraphReader();
		~GraphReader();
		void Reset();
		CSRGraph* ReadCSR(string FileName);
	private:
		ifstream MTXFile;
		void ReadToAdjList(string FileName);
		CSRGraph* PackAdjListToCSR();
		AdjList *MyAdjList;
		

	

};

#endif // __GRAPHREADER
