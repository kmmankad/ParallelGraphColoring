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
// For the timer...
#include <time.h>
#include <sys/time.h>


using namespace std;

// Max number of iterations to run
#define NUM_ITERATIONS 10 // Arbit

// Declare the GraphReader Object
GraphReader *GReader;
// Declare the CSR Graph Object
CSRGraph *InputGraph;
// String vars to hold the filenames
string InputMTXFile;
string OutputTxtFile;
// Execution Timer
double ExecTime;

// Simple timer function
double get_wall_time(){
	struct timeval time;
	if (gettimeofday(&time,NULL)){
		//  Handle error
		return 0;
	}
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

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
	OutputTxtFile = argv[2];
	// Init the timer to zero
	ExecTime = 0.0;
}

int main (int argc, char* argv[]){

	// Initialize the program
	Initialize(argc, argv);

	// FIXME: Replace with a while(changed..) type of control loop
	for (int i=0; i<NUM_ITERATIONS; i++){
		double StartTime = get_wall_time();	
		// Call the ColorGraph routine
		ColorGraph(InputGraph->GetNumVertices(), InputGraph->GetNumEdges(), InputGraph->ColIdx, InputGraph->RowPtr, InputGraph->ColorVector);
		double EndTime = get_wall_time();	
		ExecTime += (EndTime - StartTime);
	}

	// Verify the coloring
	if (InputGraph->VerifyColoring() == false){
		LogError("Incorrect Coloring!");

	}
	
	// Print the coloring
	LogInfo("Execution Time: %0.2fms", ExecTime);
	
	// Print the coloring to a file
	//InputGraph->PrintColoring();
	InputGraph->DumpColoringToFile(OutputTxtFile);


}
