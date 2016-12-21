#include <cuda.h>
#include "Common.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// This is a CUDA implementation of the topology driven Parallel Graph Coloring Algorithm
// described in Pingfan Li et al., High Performance Parallel Graph Coloring on GPGPUs, IPDPSW, 2016


/**
 * InitializeColorVector:
 * @desc Initialize the vertices' colors on the device
 * @param NumVertices: Number of vertices in the graph
 * @param ColorVector : A vertex-wise color vector for the entire graph
 * @param ColorValid : A vertex-wise vector to store if the coloring is indeed legal
 * 	This is needed because when we attempt to color the graph in parallel, 
 * 	there are chances that we color incorrectly. So, we need to go resolve the coloring for those vertices.
 * @return none
 */
__global__ void InitializeColorVector(int d_NumVertices, bool* d_ColorValid);

/**
 * ColorGraph:
 * @desc  Applies a parallel first-fit serial algorithm to color
 * 	  the given graph (in CSR format)
 * @param NumVertices: Number of vertices in the graph
 * @param ColIdx[]   : Concatenated adjacency list of each vertex
 * @param RowPtr[]   : Offsets of each vertex in the ColIdx list
 * @param ColorVector : A vertex-wise color vector for the entire graph
 * @return none
 */
__global__ void ColorGraph(int d_NumVertices, int d_NNZ, int* ColIdx_d, int* d_RowPtr, int* d_ColorVector, bool* d_changed);

/**
 * ResolveBadColoring:
 * @desc  Goes over the vertices and marks them uncolored if the coloring 
 * 	  is not valid (i.e. neighbors have the same color). This situation
 * 	  arises as we attempt to color vertices in parallel.
 * @param NumVertices: Number of vertices in the graph
 * @param ColIdx[]   : Concatenated adjacency list of each vertex
 * @param RowPtr[]   : Offsets of each vertex in the ColIdx list
 * @param ColorVector : A vertex-wise color vector for the entire graph
 * @param ColorValid : A vertex-wise vector to store if the coloring is indeed valid
 * @return none
 */
__global__ void ResolveBadColoring(int d_NumVertices, int* d_ColIdx, int* d_RowPtr, int* d_ColorVector, bool* d_ColorValid); 
