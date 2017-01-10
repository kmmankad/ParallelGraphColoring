/*
 * Parallel Graph Coloring: 
 * Author: Kartik Mankad 
 * Email: kmankad@ncsu.edu
 * Description: GraphReader class is a basic MTX (matrixmarket) graph reader
 * 		that stores the read file in:
 * 		- Adjacency Lists
 * 		- CSR (Compressed Sparse Row) format
 * TODO:
 * 	- Add support for non-space delimiters
 * 	- Make File-IO more robust
 */
#include "GraphReader.h"

// Constructor
GraphReader::GraphReader(){
	MyAdjList = (AdjList*)NULL;
}

GraphReader::~GraphReader(){
}

// Set the file seek pointer back to the start
void GraphReader::Reset(){
	MTXFile.clear();
	MTXFile.seekg(0, ios::beg);
}

CSRGraph* GraphReader::ReadCSR(string FileName){
	// Read the MTX file into adjacency lists
	ReadToAdjList(FileName);
	// Print the AdjList
	//MyAdjList->Print();	
	// Pack the adjacency lists into CSRGraph
	return(PackAdjListToCSR());
}

void GraphReader::ReadToAdjList(string FileName){
	int m,n,nnz;
	// Open the MTX file
	MTXFile.open(FileName.c_str(), ifstream::in);
	// TODO: Add an error check for failed open

	string Line;
	// File Reader loop
	while(getline(MTXFile, Line)){ 
		char FirstChar;
		sscanf(Line.c_str(), "%c", &FirstChar);
		if (FirstChar == '%'){
			continue;
		}else{
			// After the comments, we expect a triplet 
			// of integers, <M> <N> <NNZ>
			// where M is the number of rows 
			//       N is the number of columns
			//       NNZ is the number of non-zero entries
			// See Full specification here: http://math.nist.gov/MatrixMarket/reports/MMformat.ps.gz
			// Also see http://networkrepository.com/mtx-matrix-market-format.html
			sscanf(Line.c_str(), "%d %d %d", &m, &n, &nnz);
			LogInfo("m:%0d n:%0d nnz:%0d", (int)m, (int)n, (int)nnz);
			if (m!=n){
				LogError("Adjacency Matrix should be square! Aborting.");
				exit(0);
			}
			break;
		}
	}

	MyAdjList = new AdjList(m, nnz);
	//TODO: Add a null check

	// After this info-header line, we'll have nnz number
	// of node information lines
	for (int i=0; i<nnz; i++){
		int SourceNode, DestNode;
		getline(MTXFile, Line);
		//TODO: Add an error check here for getline status
		//
		sscanf(Line.c_str(), "%d %d", &SourceNode, &DestNode);
		MyAdjList->AddEdge(SourceNode, DestNode);
	}

	// Close the file
	MTXFile.close();
}

CSRGraph* GraphReader::PackAdjListToCSR(){
	// Return NULL if the AdjacencyList is bad
	if (MyAdjList == NULL) return NULL;

	CSRGraph* Graph = new CSRGraph(MyAdjList->GetNumVertices(), MyAdjList->GetNumEdges());

	// Go over the vertices and em in
	for (int i=0; i<MyAdjList->GetNumVertices(); i++){
		Graph->AddAdjList(MyAdjList->GetNeighbors(i));	
	}

	//Signal the completion
	Graph->DoneAdjList();

	return Graph;
}
