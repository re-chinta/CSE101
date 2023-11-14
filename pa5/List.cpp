/*Reema Chintala  
rechinta  
PA5*/  

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;
// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


List::List(){

   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   frontDummy -> next = backDummy;
   backDummy -> prev = frontDummy;

}


// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   frontDummy -> next = backDummy;
   backDummy -> prev = frontDummy;

   // load elements of L into this List
   Node* N = (L.frontDummy) ->next;
   while( (N->next)!=nullptr ){
      this->insertBefore(N->data);
      N = N->next;
   }

   
}

// Destructor

List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}




// length()
// Returns the length of this List.
int List::length() const{

    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    return frontDummy -> next -> data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    return backDummy -> prev -> data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    return afterCursor -> data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    return beforeCursor -> data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear()
{

    moveFront();
    while (length() > 0){
        eraseAfter();
    }
    
    


}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = beforeCursor -> next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy -> prev;

    afterCursor = backDummy;

}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){


    ListElement D = afterCursor -> data;
    pos_cursor ++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor -> next;
    return D;

}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){

    




    

    ListElement D = beforeCursor -> data;
    
    pos_cursor--;

    afterCursor = beforeCursor;
    beforeCursor = beforeCursor -> prev;

    return D;
        

    

    

}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    
    Node* N = new Node(x);

    N -> next = afterCursor;
    N -> prev = beforeCursor;
    
    afterCursor -> prev = N;

    beforeCursor -> next = N;

    afterCursor = N;

    num_elements++;
    
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){

    Node* N = new Node(x);

    N -> next = afterCursor;
    N -> prev = beforeCursor;

    
    beforeCursor -> next = N;


    afterCursor -> prev = N;

    beforeCursor = N;

    pos_cursor++;

    num_elements++;

}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    afterCursor -> next -> data = x;

}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    beforeCursor -> prev -> data = x;
    
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){

    // beforeCursor -> next = afterCursor -> next;
    // afterCursor = afterCursor -> next;
    // afterCursor -> prev = beforeCursor;

    Node* N = afterCursor;

    afterCursor = beforeCursor -> next -> next;
    beforeCursor -> next = afterCursor;
    afterCursor -> prev = beforeCursor;

    delete N;

    num_elements --;



}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){

    Node* N = beforeCursor;




    beforeCursor = afterCursor -> prev -> prev;
    afterCursor -> prev = beforeCursor;
    beforeCursor -> next = afterCursor;

    delete N;

    

    pos_cursor --;

    num_elements --;

}


// Other Functions ---------------------------------------------------------

// Next()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){

    while (pos_cursor < num_elements){

        beforeCursor = beforeCursor -> next;
        afterCursor = afterCursor -> next;

        pos_cursor ++;
    

        if (beforeCursor -> data == x){
            

            return pos_cursor;
        }


    }

    return -1;

}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){

    while (pos_cursor > 0){

        beforeCursor = beforeCursor -> prev;
        afterCursor = afterCursor -> prev;
        pos_cursor--;

        if ((afterCursor -> data) == x){
            return pos_cursor ;
        }

    }

    return -1;


}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){

    List elements;



    Node* temp = frontDummy -> next;

    int index = 0;

    while (temp != backDummy){
        elements.moveFront();

        if (elements.findNext(temp->data) > -1){

            if (temp == beforeCursor){
                temp = temp -> next;
                
                eraseBefore();
                
            }
            else if (temp == afterCursor){
                temp = temp -> next;
                
                eraseAfter();
                
            }
            
            else{

                if (index-1 <= position()){
                    pos_cursor--;
                }

                Node* N = temp;



                temp -> prev -> next = temp -> next;
                temp -> next -> prev = temp -> prev;

                
                
                num_elements--;
                temp = temp -> next;
                delete N;

            }


        }
        else{
            elements.insertAfter(temp->data);
            temp = temp -> next;
            
        }

        

        index++;


    }





}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{

    
    List J;

    Node* N = this -> frontDummy -> next;
    Node* M = L.frontDummy -> next;


    
    
    while( (N->next) != nullptr ){
        J.insertAfter(N->data);
        N = N->next;
        J.moveNext();
    }
    while( (M->next)!=nullptr ){
        J.insertAfter(M->data);
        M = M->next;
        J.moveNext();
    }

    J.moveFront();
    return J;


}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    
    Node* N = nullptr;
    std::string s = "(";
    
    for(N=frontDummy->next; N->next!=nullptr; N=N->next){

        if (N->next == backDummy){
            s += std::to_string(N->data);

        }
        else{
            s += std::to_string(N->data)+", ";

        }
        
    }

    s += ")";
    
    return s;

}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( length() == R.length() );
    N = this->frontDummy -> next;
    M = R.frontDummy -> next;
    while( eq && (N->next)!=nullptr){
       eq = (N->data==M->data);
       N = N->next;
       M = M->next;
    }
    return eq;
}


   // Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
// operator<<()
// Inserts string representation of Q, as defined by member function 
// to_string(), into stream.
std::ostream& operator<<( std::ostream& stream,  const List& L ) {
    return stream << L.to_string();

}

// operator==()
// Returns true if and only if Queue A equals Queue B, as defined by member
// member function equals().
bool operator==(const List& A, const List& B){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Queue with state of Q, then returns a reference
// to this Queue.
List& List::operator=( const List& L ) {


    if( this != &L ){ // not self assignment 
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return

  
}
