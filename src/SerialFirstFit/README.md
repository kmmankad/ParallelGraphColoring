# Serial Graph coloring implementation in C++

##### Algorithm
This is a C++ implementation of the popular greedy first fit graph coloring algorithm.
* Till all the vertices are not colored:
* For each vertex v in the set of vertices V:
* Iterate over v's neighbors and mark their colors disallowed
* Find the first available color that is not disallowed and assign it to the vertex v

Repeat this snippet till the entire graph is colored.

##### Usage
1. Build the GraphReader library. This is a library written to read in MTX (Matrix Market) graph ASCII files. It'll be dynamically linked to our executable. See the `README.md` in `src/GraphReader` for details.
```
cd ../src/GraphReader && make
```
2. Build this program: All built components will be in a new folder `build/`
```
make 
```
3. Run the program: The coloring info for the given graph will be written to STDOUT and an output text file.
```
./build/SerialFirstFit <input-mtx-file> <Output-txt-file>
```

##### Performance
TODO

##### References
* https://en.wikipedia.org/wiki/Greedy_coloring
