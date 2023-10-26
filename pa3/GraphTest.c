/*Reema Chintala
rechinta
PA2*/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
    
    int n = 5;

    Graph G = newGraph(n);

    

    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 1, 5);
    addArc(G, 3, 1);
    addArc(G, 4, 3);
    addArc(G, 5, 5);
    addArc(G, 1, 5);
    addArc(G, 2, 1);

    printGraph(stdout, G);

    printf("\nOrder: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));

    List S = newList();
    
    for(int i=1; i<=n; i++) append(S, i);


    

    DFS(G, S);


    printf("\nCalled DFS \n");

    printf("\nDiscover times are: \n");

    for(int i = 1; i < getOrder(G)+1; i++){

      printf("%d ", getDiscover(G, i));

    }

    printf("\n\nFinish times are: \n");

    for(int i = 1; i < getOrder(G)+1; i++){

      printf("%d ", getFinish(G, i));

    }

    printf("\n\nParents are: \n");

    for(int i = 1; i < getOrder(G)+1; i++){

      printf("%d ", getParent(G, i));

    }


     printf("\n\nStack after DFS is: \n");

    

    printList(stdout, S);

    Graph T = transpose(G);

    printf("\n\nTranspose is: \n");

    printGraph(stdout, T);


    Graph C = copyGraph(T);
    printf("\nCopy is: \n");
    printGraph(stdout, C);


    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    freeList(&S);
   

    freeGraph(&G);

    return 0;
}