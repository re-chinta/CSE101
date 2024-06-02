/*Reema Chintala  
rechinta  
PA6*/ 

//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "4389570045938";
   string s2 = "-40325978037";
   string s3 = "0";

   //BigInteger N;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);
   BigInteger C = BigInteger(s3);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;



   BigInteger D = A+B;
   BigInteger E = B+A;
   BigInteger F = A-B;
   BigInteger G = 0*A + 0*B + 928374*C;
   BigInteger H = A*B;
   BigInteger I = B*A;
   BigInteger J = B*C;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "I = " << I << endl;
   cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
   cout << "J = " << J << endl << endl;

   cout << endl;

   A += B;
   B -= C;
   C *= J;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*E*G*H*I*J << endl << endl;

   BigInteger X = BigInteger(0);
   BigInteger Y = BigInteger(10);
   BigInteger Z = BigInteger(99999999);

   cout << "X: " <<  X << endl;
   cout << "Y: " << Y << endl;
   cout << "Z: " << Z << endl;

   cout << "X+Y: " <<  X+Y << endl;
   cout << "X+Z: " <<  X+Z << endl;
   cout << "X*Z: " <<  X*Z << endl;
   cout << "Y*Z: " <<  Y*Z << endl;





   cout << endl;

   
}

