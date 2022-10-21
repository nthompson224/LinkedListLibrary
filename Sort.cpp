#ifndef SORT_CPP
#define SORT_CPP

#include "LinkedList.h"
#include "Sort.h"

//Thanks you GeeksforGeeks for having this merge sort algorithm for linked lists

template<typename T>
void splitList(ListNode<T>* src, ListNode<T>** left, ListNode<T>** right){
    ListNode<T>* fastNode;
    ListNode<T>* slowNode;
    slowNode = src;
    fastNode = src->next;

    while(fastNode){
        fastNode = fastNode->next;
        if(fastNode){
            slowNode = slowNode->next;
            fastNode = fastNode->next;
        }
    }

    *left = src;
    *right = slowNode->next;
    slowNode->next = nullptr;
}

template<typename T>
ListNode<T>* merge(ListNode<T>* left, ListNode<T>* right){
    ListNode<T>* sortedHead = nullptr;

    if(!left){
        return(right);
    }
    if(!right){
        return(left);
    }

    if(left->value <= right->value){
        sortedHead = left;
        sortedHead->next = merge(left->next, right);
    }
    if(left->value > right->value){
        sortedHead = right;
        sortedHead->next = merge(left, right->next);
    }
    return sortedHead;
}

template<typename T>
void mergeSort(ListNode<T>** refHead){
    ListNode<T>* head = *refHead;
    ListNode<T>* left;
    ListNode<T>* right;

    if(!head || !head->next){
        return;
    }

    splitList(head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *refHead = merge(left, right);
}

#endif