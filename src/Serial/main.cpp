#/*
# * Parallel Graph Coloring: 
# * Author: Kartik Mankad 
# * Email: kmankad@ncsu.edu
# * Description: A simple serial implementation of the FirstFit algorithm
# */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "FirstFit.h"
#include "GraphReader.h"


using namespace std;

// Declare the GraphReader Object
GraphReader *GReader;
// Declare the CSR Graph Object
CSRGraph *InputGraph;
// String vars to hold the filenames
string InputMTXFile;
string OutputTxtFile;

// Simple function to print usage
void PrintUsage(int argc, char* argv[]){
	cout << "Usage: " << argv[0] << " <input-mtx-file> <output-txt-file> " << endl;
	exit(2);
}

void Initialize(int argc, char* argv[]){
	//TODO: Add a more robust commandline option parsing mechanism
	if (argc != 3){
		PrintUsage(argc,argv);
	}
	// Construct the GraphReader
	GReader = new GraphReader();
	// Read the input file into a CSRGraph object
	InputGraph = GReader->ReadCSR(argv[1]);
}

int main (int argc, char* argv[]){

	// Initialize the program
	Initialize(argc, argv);

	// Call the ColorGraph routine
	ColorGraph(InputGraph->GetNumVertices(), InputGraph->GetNumEdges(), InputGraph->ColIdx, InputGraph->RowPtr, InputGraph->ColorVector);

	// Print the coloring to a file
	InputGraph->PrintColoring();
	InputGraph->DumpColoringToFile(OutputTxtFile);


}
