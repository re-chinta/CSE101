
//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
    cout << "D = " << D << endl;
    int len = D.length();

    D.moveFront();
    D.moveNext();

    List A, B;

    int count = len/2;


    for(int i=0; i<count; i++){
        A.insertBefore(D.peekPrev());
        D.moveNext();

    }
    cout << "A = " << A << endl;

    for(int j=0; j<(len-count); j++){
        B.insertBefore(D.peekPrev());
        D.moveNext();
    }
    cout << "B = " << B << endl;

    A.moveFront();
    B.moveFront();
    A.moveNext();
    B.moveNext();

    D.clear();


    while (1){
        
        if (B.position() <= B.length()){
            D.insertBefore(B.peekPrev());
            B.moveNext();
            
        }
        else{
            break;
        }
        if (A.position() <= A.length()){
            D.insertBefore(A.peekPrev());
            A.moveNext();

        }
        
    }

    cout << "D = " << D << endl;




    
    

}

int main(int argc, char* argv[]){

    if( argc != 2 ){
      printf("Usage: %s [num]\n", argv[0]);
      exit(1);
   }
    
    
    int n = stoi(argv[1]);

    List A;

    for(int i=0; i<n; i++){
        A.insertAfter(n-(i+1));
    }

    int num_shuffles = 0;

    List B = A;

    

    do{

        num_shuffles++;

        shuffle(A);
        cout << "A = " << A << endl;
        cout << "B = " << B << endl;


        
    } while(!(A==B));

    

    
    // cout << "A = " << A << endl;
    // shuffle(A);
    // shuffle(A);
    // shuffle(A);

    cout << "num: " << num_shuffles << endl;











    








}