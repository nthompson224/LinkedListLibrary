#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template<typename T>
struct ListNode {
        T value;
        ListNode* next;
    };

template <typename T>
class LinkedList {
    ListNode<T>* head;
    int count;

    //frees memory and deletes any memory the list is taking up
    void freeMemory();
    //copies the content of the list and stores it in a new list
    void copyContent(const LinkedList<T>& list);

public:
    // Default Constructor; initializes this->head to nullptr
    LinkedList();
    // Parameterized Constructor; initializes this->head with value
    LinkedList(T value);
    
    //copy constructor
    LinkedList(LinkedList<T>& List);
    
    //safely deletes memory when called
    ~LinkedList();

    //Returns how many elements are in the list
    int size();

    //Returns true if list is empty and false if it is not empty
    bool isEmpty();

    // If LinkedList is not initialized, this->head is initialized with value;
    // else, append a new ListNode* initialized with value to the end of the LinkedList
    void append(T value);

    // Inserts a new ListNode* initialized with value at the given index;
    // 0 <= index <= this->size()
    void insert(int index, T value);

    // Erases ListNode at given index;
    // 0 <= index <= this->size()
    void erase(int index);

    // Uses Merge Sort to sort the linked list 
        // By default sorted lowest to greatest; if ascending is passed as false, sorted greatest to lowest
    void sort(bool ascending = true);

    //finds and returns the index of the index that val is found
        //if val is not found returns -1
    int find(T val);
    
    //Reverses the LinkedList
    void reverse();

    // operator[] overload
    ListNode<T>& operator[](int index);
    
    // operator= overload
    // Copies the contents of the list on the right into the list on the left
    LinkedList& operator=(const LinkedList& list);
    
    // operator+(LinkedList) overload
    // Concatenates the lists together and returns a new list
    LinkedList operator+(const LinkedList& list)const;

    // operator+(T value) overload
    // appends value on the end of the list
    LinkedList operator+(T value);

    //operator+=(LinkedList) overload
    // appends the lhs list onto the end of rhs list and returns rhs
    LinkedList& operator+=(const LinkedList& list);

    // operator+=(T value) overload
    // appends value on the end of the list
    LinkedList& operator+=(T value);

    //ostream operator<< overload
    //If list.head is not initialized returns an empty string;
    //else, returns all of the elements in the list
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list){
        if(list.head){
            ListNode<T>* temp = list.head;
            out << '[' << temp->value;
            temp = temp->next;
            while(temp){
                out << ", " << temp->value;
                temp = temp->next;
            }
            out << ']';
        }
        if(!list.head){
            out << "";
        }
        return out;
    }
};

#include "LinkedList.cpp"
#endif