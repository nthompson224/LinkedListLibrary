#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "LinkedList.h"
#include "Sort.h"

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(T value) {
    head = new ListNode<T>;
    head->value = value;
    head->next = nullptr;
    count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>& list){
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
        ListNode<T>* newNode = new ListNode<T>;
        ListNode<T>* nodePtr = list.head;

        newNode->value = nodePtr->value;
        this->head = newNode;
        while(nodePtr->next){
            nodePtr = nodePtr->next;
            newNode->next = new ListNode<T>;
            newNode = newNode->next;
            newNode->value = nodePtr->value;
        }
        newNode->next = nullptr;
        this->count = list.count;
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
    if(head){
        ListNode<T>* nodePtr = head;
        ListNode<T>* newNode = new ListNode<T>;
        newNode->value = value;
        newNode->next = nullptr;

        while (nodePtr->next)
            nodePtr = nodePtr->next;
        nodePtr->next = newNode;
    }
    if (!head) {
        head = new ListNode<T>;
        head->value = value;
        head->next = nullptr;
    }
    count++;
}

template<typename T>
void LinkedList<T>::insert(int index, T value){
    if(index < 0 || index >= count + 1){
        throw(std::out_of_range("this->insert(index, value): Subscript out of range"));
    }

    ListNode<T>* nodePtr = head;
    ListNode<T>* prevNode = nullptr;
    ListNode<T>* newNode = new ListNode<T>;
    newNode->value = value;

    int i = 0;
    while(i != index && nodePtr){
        prevNode = nodePtr;
        nodePtr = nodePtr->next;
        i++;
    }
    prevNode->next = newNode;
    newNode->next = nodePtr;
    count++;
}

template<typename T>
void LinkedList<T>::erase(int index){
    if(index < 0 || index >= count){
        throw(std::out_of_range("this->erase(index): Subscript out of range"));
    }
    if(head && !head->next){
        delete head;
        head = nullptr;
    }
    if(head->next){
        ListNode<T>* nodePtr = head;
        if(index == 0){
            nodePtr = nodePtr->next;
            delete head;
            head = nodePtr;
        }
        if(index > 0){
            ListNode<T>* deleteNode;
            int i = 0;

            while(nodePtr && i < index - 1){
                nodePtr = nodePtr->next;
                i++;
            }
            deleteNode = nodePtr->next;
            nodePtr->next = deleteNode->next;
            delete deleteNode;
            deleteNode = nullptr;
        }
    }
    count--;
}

template<typename T>
void LinkedList<T>::sort(bool ascending){
    mergeSort(&head);
    if(!ascending){
        this->reverse();
    }
}

template <typename T>
int LinkedList<T>::find(T val){
    ListNode<T>* nodePtr = head;
    int index = -1;
    int i = 0;
    bool found = false;

    while(nodePtr && !found){
        if(nodePtr->value == val){
            found = true;
            index = i;
        }
        nodePtr = nodePtr->next;
        i++;
    }
    return index;
}

template<typename T>
void LinkedList<T>::reverse(){
    if(head && head->next){
        ListNode<T>* nodePtr = head->next;
        ListNode<T>* prevNode = head;
        ListNode<T>* nextNode;
        
        prevNode->next = nullptr;
        while(nodePtr){
            nextNode = nodePtr->next;
            nodePtr->next = prevNode;
            prevNode = nodePtr;
            nodePtr = nextNode;
        }
        head = prevNode;
    }
}

template<typename T>
ListNode<T>& LinkedList<T>::operator[](int index){
    if(index < 0 || index >= count){
        throw(std::out_of_range("this[index]: Subscript out of range"));
    }
    int i = 0;
    ListNode<T>* nodePtr = head;
    while(nodePtr && i < index){
        nodePtr = nodePtr->next;
        i++;
    }
    return *nodePtr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list){
    if(this == &list){
        return *this;
    }

    freeMemory();
    copyContent(list);
    return *this;
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& list)const{
    LinkedList<T> newList;
    newList.freeMemory();
    newList.copyContent(*this);

    if(list.head){
        ListNode<T>* newListPtr = newList.head;
        ListNode<T>* listPtr = list.head;
        ListNode<T>* newNode = new ListNode<T>;
        while(newListPtr->next){
            newListPtr = newListPtr->next;
        }
        newNode->value = listPtr->value;
        newListPtr->next = newNode;
        while(listPtr->next){
            listPtr = listPtr->next;
            newNode->next = new ListNode<T>;
            newNode = newNode->next;
            newNode->value = listPtr->value;
        }
        newNode->next = nullptr;
        newList.count = this->count + list.count;
    }
    return newList;
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(T value){
    LinkedList<T> newList = *this;
    newList.append(value);

    return newList;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& list){
    if(!list.head){
        return *this;
    }
    if(!this->head){
        this->freeMemory();
        this->copyContent(list);
        return *this;
    }
    ListNode<T>* nodePtr = this->head;
    ListNode<T>* listPtr = list.head;
    ListNode<T>* newNode = new ListNode<T>;
    while(nodePtr->next){
        nodePtr = nodePtr->next;
    }

    newNode->value = listPtr->value;
    newNode->value = listPtr->value;
    nodePtr->next = newNode;
    while(listPtr->next){
        listPtr = listPtr->next;
        newNode->next = new ListNode<T>;
        newNode = newNode->next;
        newNode->value = listPtr->value;
    }
    newNode->next = nullptr;
    this->count = this->count + list.count;
    
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator+=(T value){
    this->append(value);
    return *this;
}

#endif