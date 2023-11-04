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
int equals(Matrix A, Matrix B){

    bool equal = true;

    if (size(A) != size(B)){
        return false;
    }


    
    
    for (int i = 1; i < size(A)+1; i++){

        List AL = A->row[i];
        List BL = B->row[i];

        if (length(AL) != length(BL)){
            equal = false;
            break;

        }
        else if(length(AL) != 0 &&  length(BL) != 0){
            
            moveFront(AL);
            moveFront(BL);
            while(index(AL) != -1){

                if ( ((((Entry)get(AL))->col) != (((Entry)get(BL))->col))  ||  ((((Entry)get(AL))->value) != (((Entry)get(BL))->value))){
                    equal = false;
                    break;
                }            
                
                moveNext(AL);
                moveNext(BL);
                
            }
        }
        if (equal == false){
            break;
        }
    }


    return equal;


}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){

    for (int i = 1; i < size(M)+1; i ++){
        
        List L = M->row[i];
        while(length(L)>0){
            
            moveFront(L);
            //freeEntry(get(L));
            delete(L);
        }
    }
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){

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



            //if there is already a nnx at that column
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

    double sum = 0;

    if((length(A) == 0) || (length(B)==0)){
        return sum;  
    }

    moveFront(A);
    moveFront(B);

    while(index(A) != -1 && index(B) != -1){

        if ((((Entry)get(A))->col) > (((Entry)get(B))->col)){
            moveNext(B);
        }
        else if ((((Entry)get(A))->col) < (((Entry)get(B))->col)){
            moveNext(A);
        }

        if ((index(A) != -1) && (index(B) != -1)) {
            if ((index(A) != -1) == (index(B) != -1)){



                double product = (((Entry)get(A))->value) * (((Entry)get(B))->value);
                sum += product;

                printf("sum is: %f\n", sum);


            }
        }

        moveNext(A);
        moveNext(B);

    }

    return sum;

    

}






void add(List A, List B, List C){

    

    

    // double sum = 0;

    // if(length(A) != length(B)){
    //     printf("Matrix Error for dot helper function: len of two lists are not equal\n");
    //     freeList(&A);
    //     freeList(&B);
    //     exit(EXIT_FAILURE);
    // }

    // moveFront(A);
    // moveFront(B);

    // while(index(A) != -1 && index(B) != -1){



    //         while (((((Entry)get(A))->col) != (((Entry)get(B))->value))){
    //             if ((((Entry)get(A))->col) > (((Entry)get(B))->col)){
    //                 moveNext(B);
    //             }
    //             else{
    //                 moveNext(A);
    //             }
    //         }

    //         if ((index(A) != -1) && (index(B) != -1)) {
    //             double product = (((Entry)get(A))->value) * (((Entry)get(B))->value);
    //             sum += product;
    //         }

    //         moveNext(A);
    //         moveNext(B);

    //     }


}

List sub(List A, List B){

    List C = newList();

    double diff = 0;

    if(length(A) != length(B)){
        printf("Matrix Error for dot helper function: len of two lists are not equal\n");
        freeList(&A);
        freeList(&B);
        exit(EXIT_FAILURE);
    }

    moveFront(A);
    moveFront(B);

    while(index(A) != -1){

        diff = (((Entry)get(A))->value) - (((Entry)get(B))->value);

        if (diff != 0){

            Entry E = newEntry(index(A), diff);
            append(C, E);

        }


        moveNext(A);
        moveNext(B);

    }

    return C;

}

    



// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (equals(A, B)){
        return scalarMult(2, A);
    }

    return A;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){

    //check if both sizes are the same error handling


    //NEW MATRIX
    Matrix C = newMatrix(size(A));

    Matrix T = transpose(B);

    for (int i = 1; i < size(C)+1; i++){
        List L = C->row[i];

        for (int j = 1; j < size(C)+1; j++){
            
            double dotProduct = dot(A->row[i], T->row[j]);

            printf("dot is: %f\n", dotProduct);

            if (dotProduct != 0){

                Entry E = newEntry(j, dotProduct);
                append(L, E);
            
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



// double dot(List A, List B){
    
//         double sum = 0;

//         if((length(A) == 0) || (length(B)==0)){
//             return sum;  
//         }

//         moveFront(A);
//         moveFront(B);

//         while(index(A) != -1 || index(B) != -1){

//             while ((((((Entry)get(A))->col) != (((Entry)get(B))->value)))   && ( index(A) != -1 || index(B) != -1  ) ){
//                 if ((((Entry)get(A))->col) > (((Entry)get(B))->col)){
//                     moveNext(B);
//                 }
//                 else{
//                     moveNext(A);
//                 }
//             }

//             if ((index(A) != -1) && (index(B) != -1)) {
//                 double product = (((Entry)get(A))->value) * (((Entry)get(B))->value);
//                 sum += product;
//             }

//             moveNext(A);
//             moveNext(B);

//         }

//         return sum;

// }
    
