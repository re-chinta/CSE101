/*Reema Chintala
rechinta
PA4*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Matrix.h"
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

   

   int size;
   int entries_A;
   int entries_B;


   if (fscanf(in, "%d %d %d\n", &size, &entries_A, &entries_B) != 3) {
      fprintf(stderr, "Sparse: error reading size and num of entries\n");
      exit(1);
   }


   //printf("%d %d %d\n",  size, entries_A, entries_B);

   Matrix A = newMatrix(size);
   Matrix B = newMatrix(size);

   int col;
   int row;
   double val;

   for (int i = 0; i < entries_A; i++){


    if (fscanf(in, "%d %d %lf\n", &row, &col, &val) != 3) {
        fprintf(stderr, "Sparse: error reading entry for Matrix A\n");
        exit(1);
    }

    changeEntry(A, row, col, val);


   }


   for (int i = 0; i < entries_B; i++){


    if (fscanf(in, "%d %d %lf\n", &row, &col, &val) != 3) {
        fprintf(stderr, "Sparse: error reading entry for Matrix A\n");
        exit(1);
    }

    changeEntry(B, row, col, val);
   }







   fprintf(out, "A has 9 non-zero entries:\n");
   printMatrix(out, A);
   fprintf(out, "\n");

   fprintf(out, "B has 5 non-zero entries:\n");
   printMatrix(out, B);
   fprintf(out, "\n");

   fprintf(out, "(1.5)*A =\n");
   Matrix Scalar = scalarMult(1.5, A);
   printMatrix(out, Scalar);
   fprintf(out, "\n");

   fprintf(out, "A+B =\n");
   Matrix Sum = sum(A, B);
   printMatrix(out, Sum);
   fprintf(out, "\n");


   fprintf(out, "A+A =\n");
   Matrix Sum2 = sum(A, A);
   printMatrix(out, Sum2);
   fprintf(out, "\n");

   fprintf(out, "B-A =\n");
   Matrix Diff = diff(B, A);
   printMatrix(out, Diff);
   fprintf(out, "\n");

   fprintf(out, "A-A =\n");
   Matrix Diff2 = diff(A, A);
   printMatrix(out, Diff2);
   fprintf(out, "\n");

   fprintf(out, "Transpose(A) =\n");
   Matrix T = transpose(A);
   printMatrix(out, T);
   fprintf(out, "\n");


   fprintf(out, "A*B =\n");
   Matrix Mult = product(A, B);
   printMatrix(out, Mult);
   fprintf(out, "\n");



   fprintf(out, "B*B =\n");
   Matrix Mult2 = product(B, B);
   printMatrix(out, Mult2);
   fprintf(out, "\n");







   return 0;
}