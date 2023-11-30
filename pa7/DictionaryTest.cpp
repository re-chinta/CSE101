/*Reema Chintala  
rechinta  
PA7*/  

//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

    Dictionary A;

    std::string ideal = "a\nb\ne\nh\nf\ni\n";
    A.setValue("a", 1);
    A.setValue("b", 5);
    A.setValue("e", 10);
    A.setValue("h", 15);
    A.setValue("f", 20);
    A.setValue("i", 100);
    std::string val = A.pre_string();

    cout << ideal << endl;
    cout << val << endl;


    return 0;


}