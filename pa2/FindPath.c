/*Reema Chintala
rechinta
PA2*/

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
      addEdge(G, v1, v2);
    }
    else{
      break;
    }

   }

   List Path = newList();

   printGraph(out, G);

   int n = 0;

   List NoPath = newList();
   append(NoPath, -2);

   

   while (1){
     
    if (fscanf(in, "%d %d\n", &v1, &v2) != 2) {
        fprintf(stderr, "Find Path: error reading path\n");
        exit(1);
    }

    if (v1 != 0 && v2 != 0){
      BFS(G, v1);
      if (n>0){
         fprintf(out, "\n");
      }

      if (getDist(G, v2) >=0){
         fprintf(out, "\nThe distance from %d to %d is %d\n", v1, v2, getDist(G, v2));
      }
      else{
         fprintf(out, "\nThe distance from %d to %d is infinity\n", v1, v2);
      }

      getPath(Path, G, v2);

      if (equals(Path, NoPath)){
         fprintf(out, "No %d-%d path exists", v1, v2);

      }
      else{
         fprintf(out, "A shortest %d-%d path is: ", v1, v2);
         printList(out, Path);

      }
      
   
      
      clear(Path);
      
   
    }
    else{
      break;
    }
    n++;
   }

   freeList(&NoPath);

   freeGraph(&G);
   freeList(&Path);


   fclose(in);
   fclose(out);



   return 0;



}