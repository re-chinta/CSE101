/*Reema Chintala
rechinta
PA1*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include <string.h>


int main(int argc, char* argv[]){

   int max_len = 100;    

   
    

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }


   // open files for reading and writing 
   FILE *in = fopen(argv[1], "r");
      if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }



   FILE *out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   

   int c;
   int count = 0;
    while ((c = getc(in)) != EOF) {
        if (c == '\n') {
            count ++; // Increment count if this character is newline
        }
    }


    fseek(in, 0, SEEK_SET);




char string[1000];
    char** stringArray = (char**)malloc(count * sizeof(char*));

   for(int i=0; i<count; i++ ) {
      stringArray[i] = (char*)malloc(max_len);
         
    
      if (fscanf(in, " %[^\n]", string) != 1) {
            fprintf(stderr, "error reading string\n");
            exit(1);
      }    

      strcpy (stringArray[i], string);

   }

   



    List StringList = newList();

    append(StringList, 0);
    moveBack(StringList);

    for (int i = 1; i < count; i++){
      moveBack(StringList);
      while(1){
         if (strcmp(stringArray[i], stringArray[get(StringList)]) > 0) {
            insertAfter(StringList, i);
            break;
         }  
         else if (index(StringList) == 0) {
            insertBefore(StringList, i);
            break;     
         }
         else {
            movePrev(StringList);
         }   
         
      }
    }



    moveFront(StringList);

    while ((index(StringList) < (length(StringList))) && (index(StringList) >=0) ){
      fprintf(out, "%s\n", stringArray[get(StringList)]);
      moveNext(StringList);

    }


    freeList(&StringList);


   // close files 
   fclose(in);
   fclose(out);

   for (int i = 0; i < count; i++) {
        free(stringArray[i]);
    }
    free(stringArray);


   return(0);

}