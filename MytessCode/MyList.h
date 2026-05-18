/*** 
 * @Author: shengli.liu
 * @Date: 2024-07-04 15:52:03
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-07-18 14:41:27
 */

#ifndef MYLIST_H
#define MYLIST_H
#include <cstdint>
#include "MyDependency.h"
#define defaultSize 1
template <typename E> class List { // List ADT
private:
    void operator =(const List&) {} // Protect assignment
    List(const List&) {} // Protect copy constructor
public:
    List() {

    } // Default constructor
    ~List() {

    } // Base destructor
    // Clear contents from the list, to make it empty.
    virtual void clear() = 0;
    // Insert an element at the current location.
    // item: The element to be inserted
    virtual void insert(const E& item) = 0;
    // Append an element at the end of the list.
    // item: The element to be appended.
    virtual void append(const E& item) = 0;
    // Remove and return the current element.
    // Return: the element that was removed.
    virtual E remove() = 0;
    // Set the current position to the start of the list
    virtual void moveToStart() = 0;
    // Set the current position to the end of the list
    virtual void moveToEnd() = 0;
    // Move the current position one step left. No change
    // if already at beginning.
    virtual void prev() = 0;
    // Move the current position one step right. No change
    // if already at end.
    virtual void next() = 0;
    // Return: The number of elements in the list.
    virtual std::int32_t length() const = 0;
    // Return: The position of the current element.
    virtual std::int32_t currPos() const = 0;
    // Set current position.
    // pos: The position to make current.
    virtual void moveToPos(int pos) = 0;
    // Return: The current element.
    virtual const E& getValue() const = 0;
};

template <typename E> // Array-based list implementation
class AList : public List<E>{
private:
    std::int32_t pos;
    std::int32_t maxSize; // Maximum size of list
    std::int32_t listSize; // Number of list items now
    std::int32_t curr; // Position of current element
    E* listArray; // Array holding list elements
    //std::int32_t defaultSize = 1; // Default size of
public:
     // Constructor
    AList(std::int32_t size = defaultSize){    
        maxSize = size;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    // Destructor
    ~AList(){
        delete [] listArray; 
    } 

    // Reinitialize the list
    void clear(){   
        delete [] listArray; // Remove the array
        listSize = curr = 0; // Reset the size
        listArray = new E[maxSize]; // Recreate array
    }

    // Insert "it" at current position
    void insert(const E& it){
        Assert(listSize < maxSize, "List capacity exceeded");
        // Shift elements up
        for(std::int32_t i = listSize; i > curr; i--) {
            listArray[i] = listArray[i-1]; // to make room
        }
        listArray[curr] = it;
        listSize++; // Increment list size
    }

    // Append "it"
    void append(const E& it){   
        Assert(listSize < maxSize, "List capacity exceeded");
        listArray[listSize++] = it;
    }

    // Remove and return the current element.
    E remove(){
        Assert((curr>=0) && (curr < listSize), "No element");
        E it = listArray[curr]; // Copy the element
        for(std::int32_t i = curr; i < listSize-1; i++){
            listArray[i] = listArray[i+1];
        } // Shift them down
        listSize--; // Decrement size
        return it;
    }
    // Reset position
    void moveToStart(){ 
        curr = 0; 
    } 
    // Set at end
    void moveToEnd(){
        curr = listSize; 
    } 
    void prev(){
        if(curr != 0){
            curr--;
        }  
    } 
    void next(){ 
        if(curr < listSize){
            curr++;
        }  
    } // Next

    // Return list size
    std::int32_t length() const{
         return listSize; 
    }
    // Return current position
    std::int32_t currPos() const{
         return curr; 
    }
    // Set current list position to "pos"
    void moveToPos(int pos){
        Assert ((pos >= 0)&&(pos <= listSize), "Pos out of range");
        curr = pos;
    }
    const E& getValue() const { // Return current element
        Assert((curr >= 0)&&(curr < listSize),"No current element");
        return listArray[curr];
    }
};

// Singly linked list node
template <typename E> 
class Link {
public:
    E element; // Value for this node
    Link *next; // Pointer to next node in list
// Constructors
    Link(const E& elemval, Link* nextval = nullptr){ 
        element = elemval;
        next = nextval; 
    }
    Link(Link* nextval = nullptr){
        next = nextval;
    }
};

// Linked list implementation
template <typename E> class LList: public List<E> {
private:
    Link<E>* head; // Pointer to list header
    Link<E>* tail; // Pointer to last element
    Link<E>* curr; // Access to current element
    std::int32_t cnt; // Size of list
    void init(){ 
        // Intialization helper method
        curr = tail = head = new Link<E>;
        cnt = 0;
    }
    void removeall(){ 
        // Return link nodes to free store
        while(head != nullptr){
            curr = head;
            head = head->next;
            delete curr;
        }
    }
public:
    LList(int size = defaultSize){
        init();
    } // Constructor

    ~LList(){
        removeall();
    } // Destructor
    void print() const; // Print list contents
    void clear(){
        removeall();
        init();
    } // Clear list
    // Insert "it" at current position
    void insert(const E& it){
        curr->next = new Link<E>(it,curr->next);
        if (tail == curr){
            tail = curr->next;
        }; // New tail
        cnt++;
    }
    void append(const E& it){ 
        // Append "it" to list
        tail = tail->next = new Link<E>(it,nullptr);
        cnt++;
    }
    // Remove and return current element
    E remove(){
        Assert(curr->next != nullptr, "No element");
        E it = curr->next->element; // Remember value
        Link<E>* ltemp = curr->next; // Remember link node
        if (tail == curr->next){
            tail = curr;
        }; // Reset tail
        curr->next = curr->next->next; // Remove from list
        delete ltemp; // Reclaim space
        cnt--; // Decrement the count
        return it;
    }
    // Place curr at list start
    void moveToStart(){
        curr = head; 
    }
    // Place curr at list end
    void moveToEnd(){
        curr = tail;
    }
// Move curr one step left; no change if already at front
    void prev(){
        // No previous element
        if (curr == head){
            return;
        }
        Link<E>* temp = head;
        // March down list until we find the previous element
        // algorithm time complex could optimize
        while (temp->next != curr){
            temp = temp->next;
        }
        curr = temp;
    }
    // Move curr one step right; no change if already at end
    void next(){
        if (curr != tail) {
            curr = curr->next;
        }
    }
    // Return length
    int length() const{
        return cnt;
    } 

    // Return the position of the current element
    int currPos() const {
        Link<E>* temp = head;
        int i;
        for (i = 0; curr != temp; i++){
            temp = temp->next;
        }
        return i;
    };
    // Move down list to "pos" position
    void moveToPos(int pos) {
        Assert ((pos >= 0)&&(pos <= cnt), "Position out of range");
        curr = head;
        for(int i = 0; i < pos; i++){
            curr = curr->next;
        };
    }
    // Return current element
    const E& getValue() const{ 
        Assert(curr->next != nullptr, "No value");
        return curr->next->element;
    }
};




#endif // MYLIST_H