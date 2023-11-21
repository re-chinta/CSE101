/*Reema Chintala  
rechinta  
PA6*/  

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

#include <cmath>

using namespace std;


//CHANGE BEFORE SUBMITTING


const int power = 9;
const int base = std::pow(10, power);

// Exported type  -------------------------------------------------------------




// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){

    signum=0;
    digits = List();

}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){

   digits = List();

   if (x > 0){
      signum=1;
   }
   else if (x < 0){
      signum=-1;
   }
   else{
      signum=0;
   }

   x = abs(x);


   while (x > base){

      digits.insertBefore(x % base);
      digits.movePrev();
      x = x / base;
      
   }

}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){


   digits = List();

   if (s.size() == 0){
      throw std::invalid_argument("Value must not be an empty string");
   }

   string::size_type ch = s.find_first_not_of("+-0123456789"); 
   
   if (ch != std::string::npos) {
      throw std::invalid_argument("Value is invalid");
   } 

   string::size_type plus_minus = s.substr(1, s.size()-1).find_first_not_of("0123456789"); 

   
   if (plus_minus != std::string::npos) {
      throw std::invalid_argument("plus/minus must be in front");
   } 

   if (s[0] == '-'){
      signum=-1;
      
   }
   else if (s[0] == '+'){
      signum=1;
   }
   else{

      string::size_type zero = s.find_first_not_of("0"); 
      if (zero == std::string::npos) {
         signum=0;
         
      }
      else{
         signum=1;
      }
   }


   
   while (s.length() > 0){
      
      if (s.length()>=power){

         digits.insertAfter(std::abs(stol(s.substr(s.length() - power, power))));
         s.erase(s.length() - power, power);

      }
      else{

         string::size_type checksign = s.find_first_not_of("+-"); 
   
         if (checksign != std::string::npos) {
            digits.insertAfter(std::abs(stol(s)));
         } 
         
         // << stol(s) << endl;
         s.erase();
      }
   }

   digits.moveFront();


   while ((digits.length() > 1) && (digits.peekNext() == 0)){

      
      digits.eraseAfter();
      
   }






   

   

}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
   
   signum=N.sign();
   digits = N.digits;

}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{

   return signum;

}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{

   if (signum != N.signum){
      
      if (signum > N.signum){
         return 1;
         
      }
      else{
         return -1;
         
      }

   }


   if ((digits == N.digits) || (signum == 0 && N.signum == 0) ){


      return 0;

   }

   
   

   

   List A = digits;
   List B = N.digits;

   if (A.length() > B.length()){

      return 1;
      
   }
   else if (A.length() < B.length()){
      return -1;

   }
   else{

      

      A.moveFront();
      B.moveFront();

      while (A.position() != A.length()){
         if (A.peekNext() > B.peekNext()){
            
            return 1;
            
         }
         else if (A.peekNext() < B.peekNext()){
            
            return -1;
         }

         A.moveNext();
         B.moveNext();

      }

   }

   return 999;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){

   signum = 0;
   digits.clear();

}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){

   signum = -signum;

}


// BigInteger Arithmetic operations ----------------------------------------

void negateList(List& digits){

   digits.moveFront();

   for (int i = 0; i < digits.length() ; i++){
      digits.setAfter(-(digits.peekNext()));
      digits.moveNext();
   }
   
}



int normalize(List& digits){


   if (digits.length() == 0){
      return 0;
   }

   digits.moveFront();


   while ((digits.length() >= 1) && (digits.peekNext() == 0) ){
      digits.eraseAfter();
   }


   if (digits.length() == 0){
      return 0;
   }

   int sign = 0;

   if (digits.front() < 0){

      negateList(digits);
      sign =  -1;
   }
   else if (digits.front() > 0){

      sign =  1;
   }

   int len = digits.length();


   digits.moveBack();

   ListElement carry = 0;

   for (int x = 0; x < len; x ++){

      ListElement data = digits.movePrev();

      data += carry;
      carry = 0;
   
      
      if (data < 0){
         
         
         carry = -1;
         data += base;


      }

      if (data >= base){
         carry = data / base;
         data -= carry * base;
      }

      digits.setAfter(data);

   }


   digits.moveFront();


   if (carry != 0){
      digits.insertBefore(carry);
   }

   return sign;

}

void sumList(List& LA, List& LB, List& digits, int signA, int signB){

   

   LA.moveFront();
   LB.moveFront();

  
   while (LA.length() > LB.length()){

      LB.insertBefore(0);

   }
   while (LA.length() < LB.length()){

      LA.insertBefore(0);
      
   }
   

   LA.moveBack();
   LB.moveBack();

   
   long sum;

   if (digits.length() > 0){
      digits.clear();
   }


   for (int i = 0; i < LA.length(); i ++){
      
      sum = (signA * LA.movePrev()) + (signB * LB.movePrev());
      
      digits.insertAfter(sum);

   }

}




// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{


   BigInteger A = *this;
   BigInteger B = N;

   BigInteger C = BigInteger();

   

   List LA = A.digits;
   List LB = B.digits;

   sumList(LA, LB, C.digits, A.sign(), B.sign());




   //NORMALIZE



   C.signum = normalize(C.digits);

   if (C.digits.length() == 0){
      C.digits.insertBefore(0);
   }

   return C;

}


// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{

   BigInteger A = *this;
   BigInteger B = N;

   B.negate();

   BigInteger subVal = A.add(B);


   return subVal;

}


void shift(List& digits, int p){
   digits.moveBack();
   for (int i = 0; i < p; i ++){
      digits.insertAfter(0);
   }
}

List scalar(List L, long s){

   //cout << L <<endl;
   //cout << s <<endl;
   List digits = L;
   digits.moveFront();
   for (int i = 0; i < digits.length(); i ++){
      digits.setAfter(s * digits.peekNext());
      digits.moveNext();
   }
   return digits;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{

   BigInteger total = BigInteger();

   BigInteger A = *this;
   BigInteger B = N;

   if (sign() == 0 || N.sign() == 0){
      return total;
   }
   if (sign() != N.sign()){
      total.signum = -1;
   } 
   else{
      total.signum = 1;
   }


   B.digits.moveBack();
   List running_sum = List();


   for (int i = 0; i < B.digits.length(); i++){

      //cout << "N.digits: " << N.digits << endl;

      List scale = scalar(A.digits, B.digits.movePrev());

      //cout << "scalar: " << scale << endl;

      shift(scale, i);

      List sum_copy = running_sum;

      sumList(scale, sum_copy, running_sum, 1, 1);

      //cout << "before normalize: " << running_sum << endl;

      normalize(running_sum);

      //cout << "running sum: " << running_sum << endl;

   }

   total.digits = running_sum;

   return total;

}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {

   


   digits.moveFront();

   std::string s = "";

   if (sign() == -1){
      s += '-';
   }

   
    
   while (digits.position() < digits.length()){

      int count = 0;

      if (std::to_string(digits.peekNext()).size() < power){

         if (digits.position() > 0){

            
   
            count = power - std::to_string(digits.peekNext()).size();

            for (int i = 0; i < count; i++){
               s += std::to_string(0);

            }
            
         }
      }
      
      s += std::to_string(digits.peekNext());
      //s += ".....";
      digits.moveNext();
 
   } 
   return s;
   
}
 

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
   
   return stream << N.to_string();
 
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){


   if (A.compare(B) == 0){
      return true;
   }

   return false;

}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){

   if (A.compare(B) == -1){
      return true;
   }

   return false;

   

}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){

   if (A.compare(B) <= 0){
      return true;
   }

   return false;

}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){

   if (A.compare(B) == 1){
      return true;
   }

   return false;

}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){

   if (A.compare(B) >= 0){
      return true;
   }

   return false;

}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){

   return A.add(B);

}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){

   A = A.add(B);
   return A;

}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){

   
   return A.sub(B);

}



// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
   A = A.sub(B);
   return A;

}



// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){

   return A.mult(B);

}



// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){

   A = A.mult(B);
   return A;

}

