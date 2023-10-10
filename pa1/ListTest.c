/*Reema Chintala
rechinta
PA1*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"



int main(int argc, char* argv[]){

    List l1 = newList();
    List l2 = newList();

    printf("%s\n", equals(l1,l2)?"true":"false"); //true
    append(l1, 10);
    printf("%s\n", equals(l1,l2)?"true":"false"); //false

    printList(stdout, l1);
    printf("\n");
    printList(stdout, l2);
    printf("\n");

    append(l1, 20);

    List l3 = copyList(l1);
    printList(stdout, l3);
    printf("\n");

    printf("length: %d\n", length(l1)); //2


    moveFront(l1);
    printf("cursor: %d\n", get(l1)); 
    set(l1, 99);
    printf("cursor after setting: %d\n", get(l1)); 

    for(int i=1; i<=20; i++){
      
      append(l2,i);
      
   }
   moveFront(l2);
    printf("cursor: %d\n", get(l2)); 
    insertBefore(l2, 0);

    moveBack(l2);
    printf("cursor: %d\n", get(l2)); 
    insertAfter(l2, 21);

    printList(stdout, l2);
    printf("\n");

    //deleteBack(l2);
    deleteFront(l2);
    printList(stdout, l2);














    
    

    return 0; 
}



