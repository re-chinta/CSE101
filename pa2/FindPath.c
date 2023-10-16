/*Reema Chintala
rechinta
PA2*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"
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

   return 0;

}