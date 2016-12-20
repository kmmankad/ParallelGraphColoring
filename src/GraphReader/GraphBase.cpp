#include "GraphBase.h"

GraphBase::GraphBase(int _NumVertices, int _NumEdges){
	// TODO: Add check for number of vertices not
	// exceeding max graph size
	NumVertices = _NumVertices;
	NumEdges = _NumEdges;

	// Per-vertex initialization
	for (int i=0; i<NumVertices; i++){
		// Init the color to -1
		ColorVector.push_back(NO_COLOR);
	}
}

GraphBase::~GraphBase(){
}

int GraphBase::GetNumVertices(){
	return NumVertices;
}

int GraphBase::GetNumEdges(){
	return NumEdges;
}

// Print Graph Info to an arbitary ostream
void GraphBase::Print(ostream& OutStream){
		OutStream << "==== Graph Info ==== " << endl;
		OutStream << "Number of Vertices(m) : " << dec << NumVertices << endl;
		OutStream << "Number of Edges(nnz)  : " << dec << NumEdges << endl;
		OutStream << "==================== " << endl;
}

// Print Graph Info to STDOUT
void GraphBase::Print(){
	Print(cout);
}

// This function will verify that the nodes are indeed colored properly
bool GraphBase::VerifyColoring(){
	LogError("Extend and implement this check for each graph representation!");
	return false;
}

// This function outputs the coloring to a file
// TODO: Override the cout stream on the Print functions to a filestream
// 	 to avoid duplicating the print strings
void GraphBase::DumpColoringToFile(string OutFile){
	ofstream OutFileStream(OutFile.c_str(), ios::out | ios::trunc);
	// TODO: Add check for file open
	Print(OutFileStream);
	PrintColoring(OutFileStream);
}

// Print the colors of the vertices to an arbitary ostream
void GraphBase::PrintColoring(ostream& OutStream){
	int NodeNum = 0;
	OutStream << "NumColors: " << (int)ColorVector.size() << endl;
	vector<int>::iterator it;
	for (it = ColorVector.begin(); it != ColorVector.end(); it++){
		 OutStream << "Node[" << NodeNum++ << "]:" << *it << endl;
	}
}

// Print the colors of the vertices to STDOUT
void GraphBase::PrintColoring(){
	PrintColoring(cout);
}
