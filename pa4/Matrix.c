#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<math.h>
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
      free(pE);
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
    if( M==NULL ){
      printf("Matrix Error: calling size() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if( M==NULL ){
      printf("Matrix Error: calling NNZ() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){

    if (A == NULL || B == NULL) {
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

   if (A == B){
        return 1;
    }

    if (size(A) != size(B)){
        return 0;
    }
    
    for (int i = 1; i < size(A)+1; i++){

        List L1 = A->row[i];
        List L2 = B->row[i];

        moveFront(L1);
        moveFront(L2);


        for (int j = 0; j < length(L1); j++){

            

            if (( ((Entry)get(L1))->col !=  ((Entry)get(L2))->col )  ||   ( ((Entry)get(L1))->value !=  ((Entry)get(L2))->value ) ) {
                return 0;
            }

            moveNext(L1);
            moveNext(L2);

            

        }
        
    }

    return 1;

}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){

    if( M==NULL ){
      printf("Matrix Error: calling makeZero() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 1; i < size(M)+1; i ++){
        
        List L = M->row[i];
        while(length(L)>0){
            
            moveFront(L);
            freeEntry(get(L));
            delete(L);
        }
    }
    M->nnz = 0;
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){

    if( M==NULL ){
      printf("Matrix Error: calling changeEntry() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if (i < 1 || i > size(M) || j < 1 || j > size(M)) {
    printf("Matrix Error: calling changeEntry() with invalid row or column indices\n");
    exit(EXIT_FAILURE);
}

    List L = M->row[i];

    int insert = false;


    if (length(L)==0){
        
        if (x != 0){
            Entry E = newEntry(j, x);
            prepend(L, E);
            M-> nnz++;
            
            insert = true;
        }
    }

    else{
        Entry E1;
        moveFront(L);
        
        while (index(L) != -1){
                    
            E1 = (Entry)get(L);

            //if there is already a nnz at that column
            if (E1->col == j){
                
                if (x != 0){
                    E1->value = x;
                    
       
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
                break;

            }            
            
            moveNext(L);
            
        }
    }

    if ((insert == false) && (x != 0)){
            Entry E2 = newEntry(j, x);
            append(L, E2);
            
            M->nnz++;
    }
    

}



// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){

    if( A==NULL ){
      printf("Matrix Error: calling copy() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(size(A));
    
    for (int i = 1; i < size(A)+1; i++){

        List L = A->row[i];

        if (length(L)>0){
            
            moveFront(L);
            while(index(L) != -1){

                Entry E = newEntry(((Entry)get(L))->col, ((Entry)get(L))->value);
                append(B->row[i], E);
            
                B-> nnz++;
                moveNext(L);
                
            }
        }
    }
    return B;
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){

    if( A==NULL ){
      printf("Matrix Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    
    Matrix B = newMatrix(size(A));
    
    for (int i = 1; i < size(A)+1; i++){

        List L = A->row[i];

        if (length(L)>0){
            
            moveFront(L);
            while(index(L) != -1){

                Entry E = newEntry(i, ((Entry)get(L))->value);
                append(B->row[((Entry)get(L))->col], E);
            
                B-> nnz++;
                moveNext(L);
                
            }
        }
    }
    return B;
}




// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){

    if( A==NULL ){
      printf("Matrix Error: calling scalarMult() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(size(A));

    if (x == 0){
        return B;
    }
    
    for (int i = 1; i < size(A)+1; i++){

        List L = A->row[i];

        if (length(L)>0){
            
            moveFront(L);
            while(index(L) != -1){

                Entry E = newEntry(((Entry)get(L))->col, x*((Entry)get(L))->value);
                append(B->row[i], E);
            
                B-> nnz++;
                moveNext(L);
                
            }
        }
    }
    return B;



}

//HELPER FUNCTIONS

//USED BY multiply
double dot(List A, List B){

    if( A==NULL ||  B==NULL){
      printf("Matrix Error: calling dot() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }

    double sum = 0;

    if((length(A) == 0) || (length(B)==0)){
        return sum;  
    }

    moveFront(A);
    moveFront(B);
    
    while((index(A) >= 0) && (index(B) >= 0)){

        Entry a = (Entry)get(A);
        Entry b = (Entry)get(B);

        int col_A = a->col;
        int col_B = b->col;

        double val_A = a->value;
        double val_B = b->value;

        if (col_A == col_B){
            
            sum +=  val_A * val_B;
            moveNext(A);
            moveNext(B);
        }
         if(col_A < col_B){
            while((index(A)>=0) && (col_A < col_B)){
                moveNext(A);

                if (index(A)>=0){
                    a = (Entry)get(A);
                    col_A = a->col;
                }

            }
        }
        if(col_A > col_B){
            while((index(B)>=0) && (col_A > col_B)){
                moveNext(B);

                if (index(B)>=0){
                    b = (Entry)get(B);
                    col_B = b->col;
                }
            }   
        }
    }

    //printf("sum is: %f\n", sum);

    return sum;

}




void add(List A, List B, List Result){
    //printf("hello\n");
   

    if( A==NULL ||  B==NULL || Result == NULL){
      printf("Matrix Error: calling add() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }

    moveFront(A);
    moveFront(B);

    Entry a;
    Entry b;

    int col_A = -3;
    int col_B = -2;

    double val_A;
    double val_B;
    
    while (index(A) >= 0 && index(B) >= 0) {
        a = (Entry)get(A);
        b = (Entry)get(B);
        
        col_A = a->col;
        col_B = b->col;
        val_A = a->value;
        val_B = b->value;

        if (col_A == col_B) {
            if (val_A + val_B != 0) {
                append(Result, newEntry(col_A, val_A + val_B));
            }
            moveNext(A);
            moveNext(B);
        } else if (col_A < col_B) {
            append(Result, newEntry(col_A, val_A));
            moveNext(A);
        } else {
            append(Result, newEntry(col_B, val_B));
            moveNext(B);
        }
    }

    // Handle any remaining elements in A and B
    while (index(A) >= 0) {
        a = (Entry)get(A);
        append(Result, newEntry(a->col, a->value));
        moveNext(A);
    }

    while (index(B) >= 0) {
        b = (Entry)get(B);
        append(Result, newEntry(b->col, b->value));
        moveNext(B);
    }
}

// void sub(List A, List B, List Result){

//     moveFront(A);
//     moveFront(B);
    
//     while((index(A) >= 0) && (index(B) >= 0)){

//         Entry a = (Entry)get(A);
//         Entry b = (Entry)get(B);

//         int col_A = a->col;
//         int col_B = b->col;

//         int val_A = a->value;
//         int val_B = b->value;

//         if (col_A == col_B){
//             if ((val_A - val_B) != 0){
//                 append(Result, newEntry(col_A, val_A - val_B));
//             }
//             moveNext(A);
//             moveNext(B);
//         }
//         else if(col_A < col_B){
//             while(index(A)>=0){
//                 append(Result, newEntry(col_A, val_A));
//                 moveNext(A);
//             }
//         }
//         else{
//             while(index(B)>=0){
//                 append(Result, newEntry(col_B, -val_B));
//                 moveNext(B);
//             }   
//         }
//     }
// }


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){

    if( A==NULL || B==NULL){
      printf("Matrix Error: calling sum() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if( size(A) != size(B)){
      printf("Matrix Error: calling sum() when sizes are not equivalent\n");
      exit(EXIT_FAILURE);
    }

    if (equals(A, B)){
        return scalarMult(2, A);
    }

    Matrix C = newMatrix(size(A));

    for (int i = 1; i < size(A) + 1; i ++){

        List L = C->row[i];

        add(A->row[i], B->row[i], L);

        C->nnz += length(L);

    }

    return C;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){

    if( A==NULL || B==NULL){
      printf("Matrix Error: calling diff() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if( size(A) != size(B)){
      printf("Matrix Error: calling diff() when sizes are not equivalent\n");
      exit(EXIT_FAILURE);
    }

    Matrix T = scalarMult(-1, B);
    Matrix S = sum(A, T);

    return S;

}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){

    if( A==NULL || B==NULL){
      printf("Matrix Error: calling product() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    if( size(A) != size(B)){
      printf("Matrix Error: calling product() when sizes are not equivalent\n");
      exit(EXIT_FAILURE);
    }



    //NEW MATRIX
    Matrix C = newMatrix(size(A));
    Matrix T = transpose(B);

    for (int i = 1; i < size(C)+1; i++){

        

        if (length(A->row[i])>0){

            List L = C->row[i];

            for (int j = 1; j < size(C)+1; j++){

                if ((length(T->row[j])>0)){
                
                    double dotProduct = dot(A->row[i], T->row[j]);

                    if (dotProduct != 0){


                        Entry E = newEntry(j, dotProduct);
                        append(L, E);
                        C->nnz++;
                    
                    }
                }

            }
        }

    }

    //free transpose

    return C;
}


// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){

    if( M==NULL ){
      printf("Matrix Error: calling printMatrix() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 1; i < size(M)+1; i++){

        List L = M->row[i];

        if (length(L)>0){
            fprintf(out, "%d: ", i);
            
            moveFront(L);
            while(index(L) != -1){

                
                fprintf(out, "(%d, %.1f) ", ((Entry)get(L))->col, ((Entry)get(L))->value);
                moveNext(L);
                
            }

            fprintf(out, "\n");



        }
        
    }
}
