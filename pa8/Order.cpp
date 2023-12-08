/*Reema Chintala  
rechinta  
PA7*/ 

//-----------------------------------------------------------------------------
// Order.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"Dictionary.h"

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

    std::string line;


    Dictionary A;

    if (inputFile.is_open()) {
        
        int line_num = 1;
        while (std::getline(inputFile, line)) {
            A.setValue(line, line_num);
            line_num++;
        }


        // Close the file when done
        inputFile.close();

        
    } else {
        std::cerr << "Unable to open the file: " << in << std::endl;
    }


    if (outputFile.is_open()) {

        outputFile << A << endl;
        outputFile << A.pre_string();
        outputFile.close();
    
    } else {
        std::cerr << "Unable to open the file: " << out << std::endl;
    }



    



}