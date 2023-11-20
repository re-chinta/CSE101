/*Reema Chintala  
rechinta  
PA6*/  

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

using namespace std;


//CHANGE BEFORE SUBMITTING

const int base = 1000;
const int power = 3;

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

   // int firstDigits;
   // int num_dig = 0;
   // int index = 0;

   // if (s[0] == '+' || s[0] == '-' ){
   //    firstDigits = (s.size()-1)%power;
   //    digits.insertBefore(stol(s.substr(1, firstDigits)));
   //    digits.movePrev();
   //    num_dig = s.size()-1-firstDigits;
   //    index = 1;

   // }
   // else{
   //    firstDigits = s.size()%power;
   //    digits.insertBefore(stol(s.substr(0, firstDigits)));
   //    digits.movePrev();
   //    num_dig = s.size()-firstDigits;
   //    index = 0;

   // }

   //int iterations = num_dig/power;

   
   
   while (s.length() > 0){
      if (s.length()>=power){
         digits.insertAfter(stol(s.substr(s.length() - 3, power)));
         //cout << stol(s.substr(s.length() - 3, power)) << endl;
         s.erase(s.length() - 3, power);

      }
      else{
         digits.insertAfter(stol(s));
         // << stol(s) << endl;
         s.erase();
      }
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


   if ((digits == N.digits) || (signum == 0 && N.signum == 0) ){

      return 0;

   }
   

   if (signum != N.signum){
      if (signum > N.signum){
         return 1;
         
      }
      else{
         return -1;
         
      }

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





// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{



   BigInteger A = *this;
   BigInteger B = N;

   cout << A << endl;
   cout << B << endl;

   List LA = A.digits;
   List LB = B.digits;

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

   BigInteger C = BigInteger();

   long sum;

   for (int i = 0; i < LA.length(); i ++){

      sum = (A.sign() * LA.peekPrev()) + (B.sign() * LB.peekPrev());
      C.digits.insertAfter(sum);
      LA.movePrev();
      LB.movePrev();


   }


   cout << LA << endl;
   cout << LB << endl;
   cout << C.digits << endl;
   





   //NORMALIZE

   if (C.digits.length() == 0){
      C.signum = 0;
      return C;
   }

   C.digits.moveFront();

   while (C.digits.peekNext() == 0){

      C.digits.eraseAfter();
   }

   if (C.digits.length() == 0){
      C.signum = 0;
      return C;
   }

   if (C.digits.front() < 0){
      C.signum = -1;
   }
   else if (C.digits.front() > 0){
      //cout << "positive" << endl;

      C.signum = 1;
   }

   int len = C.digits.length();


   C.digits.moveBack();

   ListElement carry = 0;

   for (int x = 0; x < len; x ++){

      ListElement data = C.digits.peekPrev() + carry;
      C.digits.setBefore(data);
      C.digits.movePrev();
      carry = 0;
      
      
      // if (data < 0){
      //    carry = data/base - 1;
      //    data -= carry + base;
      //    if (x == length - 1){
      //       setAfter()
      //    }
      // }

      if (data >= base){
         
         carry = data / base;
         data -= base;
         C.digits.setAfter(data);
        
         if (x == len - 1 ){

            C.digits.insertAfter(carry);
            C.digits.moveFront();

            //cout << C.digits << endl;

            return C;
         }
      }

      

   }

   cout << C << endl;




   return N;



}



// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{

   return N;

}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{

   return N;

   

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

   //cout << "hi" << endl;

   if (A.compare(B) == 0){
      //cout << "hhi" << endl;
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
   return A;

}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
   return A;

}



// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
   return A;

}



// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){

   return A;

}



// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){

   return A;

}

