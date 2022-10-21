#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "LinkedList.h"
#include "Sort.h"

template <typename T>
LinkedList<T>::LinkedList() { //default constructor
    head = nullptr;
    count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(T value) {//parameterized constructor
    head = new ListNode<T>; //create a new node in memory for head
    head->value = value;
    head->next = nullptr;
    count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>& list){ //copy constructor
    copyContent(list);
}

template <typename T>
LinkedList<T>::~LinkedList() {
    freeMemory();
}

template <typename T>
void LinkedList<T>::freeMemory(){
    if (head) {
        ListNode<T>* nodePtr = head;
        ListNode<T>* nextNode;
        while (nodePtr) {
            nextNode = nodePtr->next;
            delete nodePtr;
            nodePtr = nextNode;
        }
    }
    count = 0;
}

template <typename T>
void LinkedList<T>::copyContent(const LinkedList& list){
    if(list.head){
        ListNode<T>* newNode = new ListNode<T>; //this node with be used to initalize the new list
        ListNode<T>* nodePtr = list.head; //node to loop through list

        newNode->value = nodePtr->value; //initialize newNode with the value of the list.head
        this->head = newNode; //assign newNode to the head of the newList
        while(nodePtr->next){ //loop through list and assign newNode the values of the nodes in list
            nodePtr = nodePtr->next;
            newNode->next = new ListNode<T>;//create a new node in memory for each node being copied
            newNode = newNode->next;
            newNode->value = nodePtr->value;
        }
        newNode->next = nullptr; //finally assign the nullptr after the last node
        this->count = list.count; //copy over the count of nodes
    }
}

template <typename T>
int LinkedList<T>::size(){
    return count;
}

template <typename T>
bool LinkedList<T>::isEmpty(){
    return head == nullptr;
}

template <typename T>
void LinkedList<T>::append(T value) {
    if(head){ //make sure head is initialized
        ListNode<T>* nodePtr = head; //node to loop through the list 
        ListNode<T>* newNode = new ListNode<T>; //create memory for the new node
        newNode->value = value; //initialize the new node
        newNode->next = nullptr;

        while (nodePtr->next) //loop through list
            nodePtr = nodePtr->next;
        nodePtr->next = newNode; //the last node in list now points at the new node
    }
    if (!head) { //if head isn't initialized
        head = new ListNode<T>;
        head->value = value;
        head->next = nullptr;
    }
    count++;
}

template<typename T>
void LinkedList<T>::insert(int index, T value){
    //make sure the index given is within the subscript range
    //technically not needed but used so the user knows where the element is if index >= count + 1; makes the [] operator make sense
    if(index < 0 || index >= count + 1){
        throw(std::out_of_range("this->insert(index, value): Subscript out of range"));
    }

    ListNode<T>* nodePtr = head;
    ListNode<T>* prevNode = nullptr;
    ListNode<T>* newNode = new ListNode<T>;
    newNode->value = value;

    int i = 0;
    while(i != index && nodePtr){ //loop to given index or until end of list
        prevNode = nodePtr;
        nodePtr = nodePtr->next;
        i++;
    }
    prevNode->next = newNode; //node at index - 1 now points to new node
    newNode->next = nodePtr; // new node now points to index + 1
    count++;
}

template<typename T>
void LinkedList<T>::erase(int index){
    //make sure the index given is within the subscript range
    //technically not needed but used so the user knows what node they are deleting
    if(index < 0 || index >= count){
        throw(std::out_of_range("this->erase(index): Subscript out of range"));
    }
    if(head && !head->next){ //if only head is initialized delete head
        delete head;
        head = nullptr;
    }
    if(head->next){ //make sure head->next is a valid node
        ListNode<T>* nodePtr = head;
        if(index == 0){ //if the deleted node is the head of the list makes sure the head is reinitialized to head->next
            nodePtr = nodePtr->next;
            delete head;
            head = nodePtr;
        }
        if(index > 0){
            ListNode<T>* deleteNode;
            int i = 0;

            while(nodePtr && i < index - 1){ // loop to index - 1 or until end of list
                nodePtr = nodePtr->next;
                i++;
            }
            deleteNode = nodePtr->next; // store the node at index int the node to be deleted
            nodePtr->next = deleteNode->next; //the node at index - 1 now points to the node after the node to be deleted
            delete deleteNode;
            deleteNode = nullptr;
        }
    }
    count--;
}

template<typename T>
void LinkedList<T>::sort(bool ascending){
    mergeSort(&head); //entrance point for the sort algo
    if(!ascending){ //if user passes false in parameter, reverse the sorted list so it is sorted greates->least
        this->reverse();
    }
}

template <typename T>
int LinkedList<T>::find(T val){
    ListNode<T>* nodePtr = head;
    int index = -1; //default return value
    int i = 0;
    bool found = false;

    while(nodePtr && !found){ //loop until val is found in list or end of list
        if(nodePtr->value == val){
            found = true;
            index = i; //index of the node holding the found value
        }
        nodePtr = nodePtr->next;
        i++;
    }
    return index;
}

template<typename T>
void LinkedList<T>::reverse(){
    if(head && head->next){ //make sure head and head->next are valid nodes
        ListNode<T>* nodePtr = head->next; 
        ListNode<T>* prevNode = head;
        ListNode<T>* nextNode;
        
        prevNode->next = nullptr; // prevNode hold the head of the list so make it point to null
        while(nodePtr){
            nextNode = nodePtr->next; //nextNode initalized to the next node in the list so we can reassign nodePtr->next to prevNode
            nodePtr->next = prevNode;
            prevNode = nodePtr;
            nodePtr = nextNode; //nodePtr is now at the next element in the list to reverse
        }
        head = prevNode; //prevNode hold the last valid node in the list (before reversing) so assign head to it
    }
}

template<typename T>
ListNode<T>& LinkedList<T>::operator[](int index){
    //make sure the index given is within the subscript range
    //technically not needed but can't pull a node at list[size + 1] when there isn't a node at the index
    if(index < 0 || index >= count){
        throw(std::out_of_range("this[index]: Subscript out of range"));
    }
    int i = 0;
    ListNode<T>* nodePtr = head;
    while(nodePtr && i < index){ //loop until index or end of list
        nodePtr = nodePtr->next;
        i++;
    }
    return *nodePtr; //return that node
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list){
    if(this == &list){ //if the list is being assigned to itself return itself
        return *this;
    }

    freeMemory(); //free memory for new list
    copyContent(list); //copy the contents over
    return *this;
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& list)const{
    LinkedList<T> newList; //new list
    newList.copyContent(*this); //copy the contents from the lhs list to newList

    if(list.head){
        ListNode<T>* newListPtr = newList.head;
        ListNode<T>* listPtr = list.head; //holds the first node in the list to append
        ListNode<T>* newNode = new ListNode<T>;
        while(newListPtr->next){//loop until the end of the newList so we can append the contents of list
            newListPtr = newListPtr->next;
        }
        newNode->value = listPtr->value; 
        newListPtr->next = newNode;
        while(listPtr->next){ //loop through the rhs list and create a new node and assign its value each node in list
            //create new memory for a new node to copy the contents of list to the end of newList
            listPtr = listPtr->next;
            newNode->next = new ListNode<T>;
            newNode = newNode->next;
            newNode->value = listPtr->value;
        }
        newNode->next = nullptr; // assign nullptr at the end of the newList
        newList.count = this->count + list.count; //uypdate the size of list
    }
    return newList;
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(T value){
    LinkedList<T> newList = *this; //assign newList to the list being operated on
    newList.append(value); //append the new value onto the end of the new list

    return newList;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& list){
    if(!list.head){ //if rhs list is not initialized then return the original list
        return *this;
    }
    if(!this->head){ //if the rhs list is not initialized then copy the contents of the lhs list to the rhs list and return it
        this->freeMemory();
        this->copyContent(list);
        return *this;
    }
    //if the conditions above don't execute then append the rhs list to the end of the lhs list
    ListNode<T>* nodePtr = this->head; //nodePtr points to lhs list
    ListNode<T>* listPtr = list.head; //listPtr points to rhs list
    ListNode<T>* newNode = new ListNode<T>;
    while(nodePtr->next){ //loop to end of lhs list
        nodePtr = nodePtr->next;
    }

    newNode->value = listPtr->value; // initialize the new node with a copy of the head of rhs list so it can be assigned to the end of lhs list
    newNode->value = listPtr->value;
    nodePtr->next = newNode; //the end of lhs list now points to the copy first element of rhs list
    while(listPtr->next){ //loop until the last valid node of rhs list
        //create new memory for a new node to copy the contents of rhs list to lhs list
        listPtr = listPtr->next; 
        newNode->next = new ListNode<T>;
        newNode = newNode->next;
        newNode->value = listPtr->value;
    }
    newNode->next = nullptr; //the last node of the lhs list now points to null
    this->count = this->count + list.count; //update lhs list size
    
    return *this; //return lhs list now that the rhs list is not appended onto the end
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator+=(T value){ //append the value onto the end of the list (same as + operator but returns the same list)
    this->append(value);
    return *this;
}

#endif
