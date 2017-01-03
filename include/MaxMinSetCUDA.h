#include <cuda.h>

// Pull in the curand headers
#include <curand.h>
#include <curand_kernel.h>

// We'll use time as the seed
#include <ctime>

#include "Common.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// This is a CUDA implementation of the topology driven Parallel Graph Coloring Algorithm
// described in the GTC 2012 Talk by J. Cohen, P. Castonguay "Efficient Graph Matching and Coloring on the GPU"
//

/**
 * InitRandGen
 * @desc Kernel to initialize the random generator state
 * @param RandSeed Random Seed to use for the generation
 * @param RandStates curandState_t 
 * @ret none
 */
__global__ void InitRandGen (int d_NumVertices, int RandSeed, curandState_t* RandStates);

/**
 * AssignRand
 * @desc Assign random numbers to each of the vertices
 * @param d_NumVertices Number of vertices
 * @param d_NNZ Number of edges in the graph
 * @param d_ColIdx[]   : Concatenated adjacency list of each vertex
 * @param d_RowPtr[]   : Offsets of each vertex in the ColIdx list
 * @param d_RandNums[] : Random Number for each vertex
 * @param RandStates   : cuRand State struct
 * @ret none
 */
__global__ void AssignRand (int d_NumVertices, int d_NNZ, int* d_ColIdx, int* d_RowPtr, int* d_RandNums, curandState_t* RandStates);

/**
 * ColorGraph:
 * @desc  Applies a parallel MIS based algorithm to color
 * 	  the given graph (in CSR format)
 * @param d_NumVertices: Number of vertices in the graph
 * @param d_NNZ      : Number of edges in the graph
 * @param ColIdx[]   : Concatenated adjacency list of each vertex
 * @param RowPtr[]   : Offsets of each vertex in the ColIdx list
 * @param d_ColorVector : A vertex-wise color vector for the entire graph
 * @param d_ColorVal : Color value to assign in that sweep
 * @param d_RandNums : A vertex-wise vector of Random Numbers
 * @param changed   : bool flag to indicate that we operated on the graph
 * @return none
 */
__global__ void ColorGraph(int d_NumVertices, int d_NNZ, int* d_ColIdx, int* d_RowPtr, int* d_ColorVector, int d_ColorVal, int* d_RandNums, bool* d_changed);

