# Serial Graph coloring implementation in C++

This is the simple (and greedy) first fit algorithm.

Till all the vertices are not colored:
	For each vertex v in the set of vertices V:
		Iterate over v's neighbors and marks their colors disallowed
		Find the first available color that is not disallowed and assign it to the vertex
