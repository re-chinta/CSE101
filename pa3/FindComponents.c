/*Reema Chintala
rechinta
PA3*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"
#include <string.h>


int main(int argc, char* argv[]){

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   FILE *in = fopen(argv[1], "r");
      if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

   FILE *out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   int num_vertices;

   if (fscanf(in, "%d\n", &num_vertices) != 1) {
      fprintf(stderr, "Find Path: error reading number of vertices\n");
      exit(1);
   }

   Graph G = newGraph(num_vertices);

   int v1 = 1;
   int v2 = 1;

   while (1) {

    if (fscanf(in, "%d %d\n", &v1, &v2) != 2) {
        fprintf(stderr, "Find Path: error reading edge\n");
        exit(1);
    }


    if (v1 != 0 && v2 != 0){
      addArc(G, v1, v2);
    }
    else{
      break;
    }

   }

   fprintf(out, "Adjacency list representation of G:\n");

   printGraph(out, G);
   

   List S = newList();

   for(int i=1; i<=num_vertices; i++) append(S, i);

   
   DFS(G, S);

   
   Graph T = transpose(G);

   DFS(T, S);

   int components = 0;

   for (int i = 1; i < getOrder(G)+1; i ++){
      if (getParent(T, i) == NIL){
         components++;
      }
   }

   fprintf(out, "\nG contains %d strongly connected components:", components);
   
   int c = 1;
   while (c < components+1){
      moveBack(S);
      while (getParent(T, get(S)) != NIL){
         movePrev(S);
      }
      fprintf(out, "\nComponent %d: %d", c, get(S));
      c++;
      int k = 1;
      while(index(S) != length(S)-1){
         moveNext(S);
         k++;
         fprintf(out, " %d", get(S));
      }
      for (int i = 0; i < k; i ++){
         deleteBack(S);
      }
   }
   freeGraph(&G);
   freeGraph(&T);
   freeList(&S);
   fclose(in);
   fclose(out);
   return 0;
}