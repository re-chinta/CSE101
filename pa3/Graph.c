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

    int *discover;
    int *finish;


    

    int order; //vertices
    int size; //edges
    
   
} GraphObj;



/*** Constructors-Destructors ***/
Graph newGraph(int n){

    Graph G = malloc(sizeof(GraphObj));
    
    assert( G!=NULL );
    G -> size = 0;
    G -> order = n;

    G -> neighbors = (List*)calloc(n+1, sizeof(List));


    for (int i = 0; i < n+1; i++){
        G->neighbors[i] = newList();
    }


    G -> color = (char*)calloc(n+1, sizeof(char));
    G -> parent = (int*)calloc(n+1, sizeof(int));

    G -> discover = (int*)calloc(n+1, sizeof(int));
    G -> finish = (int*)calloc(n+1, sizeof(int));

    for (int i = 0; i < n+1; i++){
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }



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
        free((*pG)->discover);
        free((*pG)->finish);

        
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




int getParent(Graph G, int u){

    if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() when 1 ≤ u ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }


    return G->parent[u];


}






int getDiscover(Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDiscover() when 1 ≤ u ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }

    return G->discover[u];

} /* Pre: 1<=u<=n=getOrder(G) */


int getFinish(Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getFinish() when 1 ≤ u ≤ getOrder(𝐺) not met\n");
      exit(EXIT_FAILURE);
    }

    return G->finish[u];
} /* Pre: 1<=u<=n=getOrder(G) */




/*** Manipulation procedures ***/





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
        G->size ++;
        
    }
    else{

        int check = 1;
        moveFront(G->neighbors[u]);
        
        while (index(G->neighbors[u]) != -1){
            if (get(G->neighbors[u]) == v){
                check = 0;
            }
            moveNext(G->neighbors[u]);
        }

        if (check == 1){

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
            
            G->size ++;
        }      
    }

    
}



void Visit(Graph G, int x, int* time, List S){
    
    G->discover[x] = ++(*time);        // discover x
    G->color[x] = 'g';
    List adj = G->neighbors[x];
    moveFront(adj);
    for (int i = 0; i <length(adj); i++){
        if (G->color[get(adj)] == 'w'){
            G->parent[get(adj)] = x;
            Visit(G, get(adj), time, S);
        }
        moveNext((G->neighbors[x]));
    }
    G->color[x] = 'b';
    G->finish[x] = ++(*time);        // finish x
    insertAfter(S, x);

}

void DFS(Graph G, List S){

    for (int i = 1; i < getOrder(G) + 1; i ++){
        G->color[i] = 'w';
        G->parent[i] = NIL;
    } 
    
    int time = 0;

    moveBack(S);

    while (time < getOrder(G)*2){

        if (G->color[front(S)] == 'w'){

            Visit(G, front(S), &time, S);
        }
        deleteFront(S);
        
    }

    while (length(S) > getOrder(G)){
        deleteFront(S);
    }

    
}
/*** Other operations ***/

Graph copyGraph(Graph G){

    Graph N = newGraph(getOrder(G));

    for (int i = 1; i < getOrder(G)+1; i++){
        moveFront(G->neighbors[i]);
        while (index(G->neighbors[i]) != -1){
            addArc(N, i, get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
    }

    return N;

    

}


Graph transpose(Graph G){

    Graph T = newGraph(getOrder(G));

    for (int i = 1; i < getOrder(G)+1; i++){
        moveFront(G->neighbors[i]);
        while (index(G->neighbors[i]) != -1){

            addArc(T, get(G->neighbors[i]), i);
            moveNext(G->neighbors[i]);
        }
    }
    return T;
}



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