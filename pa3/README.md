/*Reema Chintala  
rechinta  
PA3*/  

- List.h: Header file for the List module.
- List.c: This contains all the functions for the List ADT
- Graph.h: Header file for the Graph module.
- Graph.c: Contains all the functions for the Graph ADT, such as DFS(), copyGraph(), and Transpose(). Creates a new graph which the client can add edges to.
- GraphTest.c: Tests for Graph module's functionality.
- FindComponents.c: Client that uses the Graph and List ADT modules to determine the strongly connected components in a graph. Does this by callling DFS on the graph and then the transpose of the graph. The resulting stack contains the strongly connected components. Input is a file containing vertices and edges to a graph. Outputs adjacency list for the graph and all of its strongly connected components.
- Makefile: makefile builds the executables 
- README.md