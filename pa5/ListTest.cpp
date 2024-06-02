//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
  
  
  List A, B, C;
  
  
  for(int i=1; i<=10; i++){
    A.insertAfter(i);
    B.insertAfter(11-i);
    C.insertBefore(i);
  }

  cout << "A = " << A << endl;
  cout << "B = " << B << endl;
  cout << "C = " << C << endl;

  if (B.equals(C)){
    cout << "B and C are equal" << endl;
  }

  if (!A.equals(C)){
    cout << "A and C are not equal" << endl;
  }

  A.moveFront();
  cout << "peekNext A is " << A.peekNext() << endl;
  A.moveNext();
  A.moveNext();
  cout << "peekPrev A is " << A.peekPrev() << endl;

  cout << "length A is " << A.length() << endl;
  cout << "position A is " << A.position() << endl;

  A.eraseBefore();
  A.eraseAfter();

  A.insertBefore(1);
  A.insertAfter(2);
  A.cleanup();

  cout << "A = " << A << endl;

  cout << "6 is at index " << A.findNext(6) << endl;

  List D = A.concat(B);
  cout << "D = " << D << endl;







  







}