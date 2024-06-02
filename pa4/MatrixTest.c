#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
#include"List.h"
     
int main(int argc, char* argv[]){


    Matrix freeCheck = newMatrix(1);


    changeEntry(freeCheck, 1, 1, 4);

    

   

    freeMatrix(&freeCheck);





   
    Matrix A = newMatrix(3);

    changeEntry(A, 1,1,0);
    changeEntry(A, 1,2,1);
    changeEntry(A, 1,3,1);
    
    changeEntry(A, 2,1,1);
    changeEntry(A, 2,2,1);
    changeEntry(A, 2,3,1);
  
    changeEntry(A, 3,1,1);
    changeEntry(A, 3,2,1);
    changeEntry(A, 3,3,1);
    printMatrix(stdout, A);

    printf("\n");

    changeEntry(A, 1,3,0);
    
    printMatrix(stdout, A);

    printf("\n");


    changeEntry(A, 1,3,0);
    
    printMatrix(stdout, A);

    printf("\n");


    changeEntry(A, 1,2,3);
    printMatrix(stdout, A);

    printf("\ncopy matrix \n");
    printMatrix(stdout, copy(A));

    printf("\nA is: \n");

    printMatrix(stdout, A);



    printf("\nmake zero A \n");
    makeZero(A);
    printMatrix(stdout, A);




    Matrix B = newMatrix(3);
    changeEntry(B, 1,2,3);
    changeEntry(B, 3,2,3);

    

    printf("\nB matrix \n");

    printMatrix(stdout, B);

    printf("\ntranspose matrix of B\n");
    printMatrix(stdout, transpose(B));

    printf("\nscalar matrix of B by 2\n");
    printMatrix(stdout, scalarMult(2, B));




   
    

    //freeMatrix(&A);

    return EXIT_SUCCESS;

}