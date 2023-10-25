/*Reema Chintala
rechinta
PA2*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "Graph.h"





typedef struct GraphObj{
    List *neighbors;
    char *color;
    int *parent;
    int *distance;
    

    int order; //vertices
    int size; //edges
    int source;
   
} GraphObj;



/*** Constructors-Destructors ***/
Graph newGraph(int n){

    Graph G = malloc(sizeof(GraphObj));
    
    assert( G!=NULL );
    G -> size = 0;
    G -> order = n;
    G -> source = NIL;


    G -> neighbors = (List*)calloc(n+1, sizeof(List));


    for (int i = 0; i < n+1; i++){
        G->neighbors[i] = newList();
    }
    


    G -> color = (char*)calloc(n+1, sizeof(char));
    G -> parent = (int*)calloc(n+1, sizeof(int));
    G -> distance = (int*)calloc(n+1, sizeof(int));
    

    return(G);

}
void freeGraph(Graph* pG){
    if( pG!=NULL && *pG!=NULL ){

        

        

        for (int i = 0; i < ((*pG)->order) +1; i++){
            if ((*pG)->neighbors[i] != NULL){
                freeList(&((*pG)->neighbors[i]));
            }
            
        }
        
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);

        
        free(*pG);
        *pG = NULL;
        
    }
    

    
   
}

/*** Access functions ***/
int getOrder(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    return G->size;

}

int getSource(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    return G->source;
    
}


int getParent(Graph G, int u){

    if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() when 1 ≤ u ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }


    if (getSource(G) == NIL){
        return NIL;
    }
    return G->parent[u];


}


int getDist(Graph G, int u){

    if( G==NULL ){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDist() when 1 ≤ u ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }

    if (getSource(G) == NIL){
        return INF;
    }

    return G->distance[u];
}

void getPath(List L, Graph G, int u){

    if( G==NULL ){
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getPath() when 1 ≤ u ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }

    
    if(getSource(G)== NIL){
        printf("Graph Error: calling getPath() without calling BFS() before\n");
        exit(EXIT_FAILURE);
    }


    if (u == getSource(G)){
        append(L, getSource(G));
    }
        
    else if (G->parent[u] == NIL){
        append(L, NIL);
    }
    else{
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}


/*** Manipulation procedures ***/


void makeNull(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G)+1; i++){
        if (G->neighbors[i] != NULL){
            clear(G->neighbors[i]);
        }
    }

    G->size = 0;

}


void addEdge(Graph G, int u, int v){

    if( G==NULL ){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addEdge() when 1 ≤ u/v ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }


    if (length(G->neighbors[v]) == 0){
        append(G->neighbors[v], u);
    }
    else{

        moveBack(G->neighbors[v]);
        while(1){
            if (u > get(G->neighbors[v])){
                insertAfter(G->neighbors[v], u);
                break;
            }  
            else if (index(G->neighbors[v]) == 0) {
                insertBefore(G->neighbors[v], u);
                break;     
            }
            else {
                movePrev(G->neighbors[v]);
            }   
        }      
    }


    if (length(G->neighbors[u]) == 0){
        append(G->neighbors[u], v);
    }
    else{

        moveBack(G->neighbors[u]);
        while(1){
            if (v > get(G->neighbors[u])){
                insertAfter(G->neighbors[u], v);
                break;
            }  
            else if (index(G->neighbors[u]) == 0) {
                insertBefore(G->neighbors[u], v);
                break;     
            }
            else {
                movePrev(G->neighbors[u]);
            }   
        }      
    }

    G->size ++;

}




void addArc(Graph G, int u, int v){
    if( G==NULL ){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addArc() when 1 ≤ u/v ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }

    if (length(G->neighbors[u]) == 0){
        append(G->neighbors[u], v);
    }
    else{

        moveBack(G->neighbors[u]);
        while(1){
            if (v > get(G->neighbors[u])){
                insertAfter(G->neighbors[u], v);
                break;
            }  
            else if (index(G->neighbors[u]) == 0) {
                insertBefore(G->neighbors[u], v);
                break;     
            }
            else {
                movePrev(G->neighbors[u]);
            }   
        }      
    }

    G->size ++;
}


void BFS(Graph G, int s){
    if( G==NULL ){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    G->source = s;

    for (int i = 1; i < getOrder(G) + 1; i ++){

        if (i != s){
            G->color[i] = 'w';
            G->distance[i] = INF;
            G->parent[i] = NIL;
        }
    } 

    G->color[s] = 'g';       // discover the source s
    G->distance[s] = 0;
    G->parent[s] = NIL; 

    List Q = newList();              // construct a new empty queue
    append(Q,s);


    while (length(Q) != 0){

        int x = front(Q);
        deleteFront(Q);

        moveFront(G->neighbors[x]);

        for (int i = 0; i < length((G->neighbors)[x]); i++){

            
            int y = get(G->neighbors[x]);

            if (G->color[y] == 'w' ){        // y is undiscovered
                G->color[y] = 'g';         // discover y
                G->distance[y] = getDist(G, x) + 1; 
                G->parent[y] = x;
                append(Q,y);
            } 

            moveNext(G->neighbors[x]);
        }
        G->color[x] = 'b';                  // finish x

        
    }
    freeList(&Q);

    
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G)+1; i ++ ){ 
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}