#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
#include"List.h"
     
int main(int argc, char* argv[]){

    Matrix A = newMatrix(1);

    changeEntry(A, 1,1,999);
    printMatrix(stdout, A);
    

    
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