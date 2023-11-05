#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
#include"List.h"
     
int main(int argc, char* argv[]){


    Matrix A = newMatrix(1);


    changeEntry(A, 1, 1, 4);

    

   

    freeMatrix(&A);






    // changeEntry(A, 1, 3, 0);
    // changeEntry(A, 3, 1, 0);
    // changeEntry(A, 3, 3, 0);


    // Matrix A = newMatrix(2);

    
    // changeEntry(A, 1,2,1);
    // changeEntry(A, 1,1,-1);

    // changeEntry(A, 2,1,1);
    // changeEntry(A, 2,2,1);

    // printf("Matrix A:\n");
    
    // printMatrix(stdout, A);

    // printf("\n");



    // Matrix A2 = newMatrix(2);

    // changeEntry(A2, 1,1,1);
    // changeEntry(A2, 1,2,1);

    // changeEntry(A2, 2,1,1);
    // changeEntry(A2, 2,2,1);

    // printf("Matrix A2:\n");
    
    // printMatrix(stdout, A2);

    // printf("\n");




    // printf("Matrix B:\n");


    // Matrix B = sum(A, A2);
    // printMatrix(stdout, B);






   
    // Matrix A = newMatrix(3);

    // changeEntry(A, 1,1,0);
    // changeEntry(A, 1,2,1);
    // changeEntry(A, 1,3,1);
    
    // changeEntry(A, 2,1,1);
    // changeEntry(A, 2,2,1);
    // changeEntry(A, 2,3,1);
  
    // changeEntry(A, 3,1,1);
    // changeEntry(A, 3,2,1);
    // changeEntry(A, 3,3,1);
    // printMatrix(stdout, A);

    // printf("\n");

    // changeEntry(A, 1,3,0);
    
    // printMatrix(stdout, A);

    // printf("\n");


    // changeEntry(A, 1,3,0);
    
    // printMatrix(stdout, A);

    // printf("\n");


    // changeEntry(A, 1,2,3);
    // printMatrix(stdout, A);

    // printf("\ncopy matrix \n");
    // printMatrix(stdout, copy(A));

    // printf("\nA is: \n");

    // printMatrix(stdout, A);



    // printf("\nmake zero A \n");
    // makeZero(A);
    // printMatrix(stdout, A);




    // Matrix B = newMatrix(3);
    // changeEntry(B, 1,2,3);
    // changeEntry(B, 3,2,3);

    

    // printf("\nB matrix \n");

    // printMatrix(stdout, B);

    // printf("\ntranspose matrix of B\n");
    // printMatrix(stdout, transpose(B));

    // printf("\nscalar matrix of B by 2\n");
    // printMatrix(stdout, scalarMult(2, B));



    //freeMatrix(&A);
    
    

    
    /*
    

    changeEntry(A, 2,1,1);
    changeEntry(A, 2,2,1);
    changeEntry(A, 2,3,1);

    changeEntry(A, 3,1,1);
    changeEntry(A, 3,2,1);
    changeEntry(A, 3,3,1);
*/

   
    

    //freeMatrix(&A);

    return EXIT_SUCCESS;

}