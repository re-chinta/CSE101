#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct MatrixObj{
    List* row;
    int size;
    int nnz;
} MatrixObj;

typedef struct EntryObj{
   int col;
   double value;
} EntryObj;




// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){

    Matrix M = malloc(sizeof(MatrixObj));
    assert(M != NULL );

    M->size = n;

    M->nnz = 0;

    M -> row = (List*)calloc(n+1, sizeof(List));
    
    for (int i = 1; i < n+1; i++){
        M->row[i] = newList();
    }

    return M;


}


Entry newEntry(int col, double value){

    Entry E = malloc(sizeof(EntryObj));
    assert(E != NULL);

    E->col = col;
    E->value = value;

    return E;
}

void freeEntry(Entry* pE){
    if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
   }
}





// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    
    if(pM!=NULL && *pM!=NULL ){

        makeZero(*pM);
        
        for (int i = 1; i < size(*pM)+1; i++){
            if ((*pM)->row[i] != NULL){
                freeList(&((*pM)->row[i]));
            }
        }

        free((*pM)->row);

        free(*pM);
        *pM = NULL;

    }
    
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){

    for (int i = 1; i < size(M); i ++){
        
        List L = M->row[i];
        while(length(L)>0){
            
            moveFront(L);
            freeEntry(get(L));
            delete(L);
        }
    }
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){

    List L = M->row[i];

    //int insertn;

    if (length(L)==0){
        //if (x != 0){
            Entry E = newEntry(j, x);
            prepend(L, &E);
            //printf("Col: %d\n", E->col);
            //printf("Val: %lf\n",  E->value);
            M-> nnz++;
            //insert = true;
        //}
    }

    /*


    else{

        

        Entry E1;

        
        
        while (index(L) < length(L)){
            E1 = *(Entry*)get(L);
            if (E1->col == j){
                if (x != 0){
                    E1->value = x;
                    M->nnz++;
                }
                else{
                    freeEntry(&E1);
                    delete(L);
                    M->nnz--;
                }
                insert = true;
                break;
            }
            if (E1->col > j){
                if (x != 0){
                    Entry Insert = newEntry(j, x);
                    insertBefore(L, Insert);
                    M->nnz++;
                }
                insert = true;

            }            
            moveNext(L);
        }
    }

    

    if (insert == false){
            Entry E2 = newEntry(j, x);
            prepend(L, E2);
            M->nnz++;
    }

    */

    //moveFront(M->row[i]);
    //printf("(%d, %f) ", (*(Entry*)get(M->row[i]))->col, (*(Entry*)get(M->row[i]))->value);



}



// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    moveFront(A->row[1]);
    printf("(%d, %f) ", (*(Entry*)get(A->row[1]))->col, (*(Entry*)get(A->row[1]))->value);

    return A;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);


// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){

   //moveFront(M->row[2]);
  // fprintf(out, "(%d, %f) ", (*(Entry*)get(M->row[2]))->col, (*(Entry*)get(M->row[2]))->value);



    /*

    
    

    for (int i = 1; i < size(M)+1; i++){

        List L = M->row[i];

        if (length(L)>0){
            fprintf(out, "%d: ", i);
            
            moveFront(L);

        
            while(index(L) != -1){

                
                fprintf(out, "(%d, %f) ", (*(Entry*)get(L))->col, (*(Entry*)get(L))->value);
                moveNext(L);
                
            }

            fprintf(out, "\n");



        }
        
    }

*/
    
}