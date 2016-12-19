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

void GraphBase::Print(){
		cout << " ==== Graph Info ==== " << endl;

		cout << " Number of Vertices(m) : " << dec << NumVertices << endl;
		cout << " Number of Edges(nnz)  : " << dec << NumEdges << endl;

		/* TODO */
		cout << " ==================== " << endl;
}

bool GraphBase::VerifyColoring(){
	/* TODO */
	return true;
}

void GraphBase::DumpColoringToFile(string OutFile){
	/* TODO */
}

void GraphBase::PrintColoring(){
	int NodeNum = 0;
	LogInfo("NumColors: %0d",(int)ColorVector.size());
	vector<int>::iterator it;
	for (it = ColorVector.begin(); it != ColorVector.end(); it++){
		 LogInfo("Node[%0d]:%0d", NodeNum++, *it);
	}
}
