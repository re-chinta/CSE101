/*Reema Chintala
rechinta
PA2*/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
    
    int n = 5;

    Graph G = newGraph(n);

    

    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 1, 5);
    addArc(G, 3, 1);

    printGraph(stdout, G);

    printf("\nOrder: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));
    printf("Source: %d\n", getSource(G));


    BFS(G, 3);

    List Path = newList();
    getPath(Path, G, 5);
    printf("Path from 3 to 5: ");
    printList(stdout, Path);
    printf("\n");
    clear(Path);

    getPath(Path, G, 2);
    printf("Path from 3 to 2: ");
    printList(stdout, Path);


    printf("\nParent of 5 is: %d\n", getParent(G, 5));

    

    printf("\nGraph after making NULL: \n");


    makeNull(G);



    printGraph(stdout, G);













    
   

    freeGraph(&G);

    return 0;
}