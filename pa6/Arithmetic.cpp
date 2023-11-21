#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

    string s1 = "-0000000000041085449";
    string s2 = "6402779357";
    
    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s2);

    cout << A << endl;
    cout << endl;
    cout << B << endl;
    cout << endl;
    cout << A+B << endl;
    cout << endl;
    cout << A-B << endl;
    cout << endl;
    cout << A-A << endl;
    cout << endl;

    cout << (BigInteger(3)*A)-(BigInteger(2)*B) << endl;
    cout << endl;

    cout << A*B << endl;
    cout << endl;

    cout << A*A << endl;
    cout << endl;

    cout << B*B << endl;
    cout << endl;

    

    





   
    

}