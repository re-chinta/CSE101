#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char *argv[]){
    
    if( argc != 3 ){
      printf("Usage: %s input output\n", argv[0]);
      exit(1);
    }

    std::string in = argv[1];

    std::string out = argv[2];

    std::ifstream inputFile(in);
    std::ofstream outputFile(out);

    std::string s1;
    std::string s2;

    if (inputFile.is_open()) {
        
        std::getline(inputFile, s1);

        // Skip the newline character
        inputFile.ignore();

        // Read the second line and store it in another string variable
        
        std::getline(inputFile, s2);

        // Close the file when done
        inputFile.close();

        
    } else {
        std::cerr << "Unable to open the file: " << in << std::endl;
    }

    
    
    
    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s2);


    if (outputFile.is_open()) {

        outputFile << A << endl;
        outputFile << endl;
        outputFile << B << endl;
        outputFile << endl;
        outputFile << A+B << endl;
        outputFile << endl;
        outputFile << A-B << endl;
        outputFile << endl;
        outputFile << A-A << endl;
        outputFile << endl;

        outputFile << (BigInteger(3)*A)-(BigInteger(2)*B) << endl;
        outputFile << endl;

        outputFile << A*B << endl;
        outputFile << endl;

        outputFile << A*A << endl;
        outputFile << endl;

        outputFile << B*B << endl;
        outputFile << endl;

        outputFile << (BigInteger(9)*A*A*A*A)+(BigInteger(16)*B*B*B*B*B) << endl;
        outputFile << endl;
        
        outputFile.close();
    
    } else {
        std::cerr << "Unable to open the file: " << out << std::endl;
    }


   


    


    

    





   
    

}