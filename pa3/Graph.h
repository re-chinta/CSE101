/*Reema Chintala
rechinta
PA3*/

#include "List.h"

#define NIL 0
#define UNDEF -10

typedef struct GraphObj* Graph;




/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */



/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/

Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
