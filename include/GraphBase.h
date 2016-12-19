#ifndef __GRAPHBASE
#define __GRAPHBASE

#include <iostream>
#include <vector>
#include "Common.h"

#define NO_COLOR 0

using namespace std;

class GraphBase{
	public:
		GraphBase(int _NumVertices, int _NumEdges);
		~GraphBase();
		virtual	void Print();
		virtual bool VerifyColoring();
		virtual void DumpColoringToFile(string OutFile);
		virtual void PrintColoring();
		vector<int> ColorVector;
		int GetNumVertices();
		int GetNumEdges();
	protected:
		int NumVertices;
		int NumEdges;
};

#endif // __GRAPHBASE
