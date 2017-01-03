/*
# * Parallel Graph Coloring: 
# * Author: Kartik Mankad 
# * Email: kmankad@ncsu.edu
# * Description: A parallel implementation of
#	         an MIS based graph coloring algorithm
# */
#include "MaxMinSetCUDA.h"

// Random Number generator init
__global__ void InitRandGen (int d_NumVertices, int RandSeed, curandState_t* RandStates){
	int threadID = blockIdx.x * blockDim.x + threadIdx.x;
	if (thread_num < d_NumVertices) {
		// Initialization is much faster if sequence number and offset
		// are kept at zero, and instead a different seed is used.
		// See - https://devtalk.nvidia.com/default/topic/480586/curand-initialization-time/?offset=4
		curand_init(RandSeed+thread_num, /* sequence number */ 0, /* sequence offset */ 0, &RandStates[thread_num]);
	}

}

// Assign Random Numbers to each vertex.
// TODO: Check if merging the two RNG kernel calls helps perf
__global__ void AssignRand (int d_NumVertices, int d_NNZ, int* d_ColIdx, int* d_RowPtr, int* d_RandNums, curandState_t* RandStates){
	int threadID = blockIdx.x * blockDim.x + threadIdx.x;
	if (threadID < d_NumVertices){
		d_RandNums[threadID] = curand(&RandStates[thread_num]) % d_NumVertices;
	}
}

// Actual Graph Coloring kernel
__global__ void ColorGraph(int d_NumVertices, int d_NNZ, int* d_ColIdx, int* d_RowPtr, int* d_ColorVector, int d_ColorVal, int* d_RandNums, bool* d_changed){
	int threadID = blockIdx.x * blockDim.x + threadIdx.x;
	// Set the default value of changed to false
	*d_changed = false;
	// So that we dont walk over the edge of the d_RowPtr array
	if (threadID <= d_NNZ) { 
		// if the vertex is not colored
		if (d_ColorVector[threadID] == NO_COLOR){
			// Iterate over its neighbors
			// and color it d_ColorVal if its the max
			bool VertexIsMax = true; 
			for (int CurrNodeOffset=d_RowPtr[threadID]; CurrNodeOffset<d_RowPtr[threadID+1] ; CurrNodeOffset++){
				// Ignore neighbors that are already colored 
				int NeighborColor = d_ColorVector[d_ColIdx[CurrNodeOffset]];
				if (NeighborColor == NO_COLOR){
					// Check if the vertex is the maximum of its neighbors
					if (d_RandNums[threadID] < d_RandNums[d_ColIdx[CurrNodeOffset]]){
						VertexIsMax = false;	
					}
				}
			}
			// If this vertex is the max, assign it d_ColorVal
			if (VertexIsMax == true){
				d_ColorVector[threadID] = d_ColorVal;
				*d_changed = true;
			}
		} // end if d_ColorVector[threadID] == NO_COLOR
	} // end if (threadID < d_NNZ)
}
