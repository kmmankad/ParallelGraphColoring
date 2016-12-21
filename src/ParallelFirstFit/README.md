# Parallel Graph coloring implementation in C++

## Algorithm
This is a CUDA implementation of the topology driven Parallel Graph Coloring Algorithm described in **Pingfan Li et al., High Performance Parallel Graph Coloring on GPGPUs, IPDPSW, 2016**

* We're going with a topology based approach here (rather than worklist based). It should be noted that the worklist based approach will definitely give better performance. With this topology based apporach, we expect the kernel to suffer from a lot of warp divergence and load imbalance and perform poorly as a result.

* To store the various CSR vectors, we'll be using Thrust's device-vectors. We could also have used raw integer pointers.
  * An inherent issue I see with the CSR storage is the unaligned and uncoalesced memory access pattern. Need to look into this further.

* Main algorithm:
* We'll assign each thread one vertex to deal with as described below.
  * Each Thread:
    * Figure out which vertex you're to process
    * Examine its neighbors and find the first available color thats not disallowed

## Usage
TODO: Add Instructions
