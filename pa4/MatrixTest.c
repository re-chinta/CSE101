#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
#include"List.h"
     
int main(int argc, char* argv[]){

    Matrix M = newMatrix(10);

    printMatrix(stdout, M);

    freeMatrix(&M);

    return EXIT_SUCCESS;

}