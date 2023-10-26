/*Reema Chintala
rechinta
PA3*/

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){


    Graph A = newGraph(100);
    List L = newList();


    if (getSize(A) != 0)
      return 1;
    addArc(A, 54, 1); ///
    addArc(A, 54, 2); ///
    addArc(A, 54, 2);
    addArc(A, 54, 3); ///
    addArc(A, 1, 54); ///
    addArc(A, 1, 54);
    addArc(A, 1, 55); ///
    addArc(A, 1, 55);

    for (uint8_t i = 1; i <= 100; i++) {
      append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 5)
      return 3;
    addArc(A, 55, 1);
    if (getSize(A) != 6)
      return 4;
    return 0;

    
    
    

    return 0;
}