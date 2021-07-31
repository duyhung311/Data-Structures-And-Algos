/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    void sort(int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
        if(this->count > 0){
            typename DLinkedList<T>::Node* first = this->head->next; //first user's data
            first->prev = 0;
            this->tail->prev->next = 0; //to tail => to 0
            this->tail->prev = 0;
            mergeSort(first, comparator);
            
            //find the last user's data
            typename DLinkedList<T>::Node* last = first;
            while(last->next != 0) last = last->next;
            
            //attach to head&tail of the list
            last->next = this->tail;
            this->tail->prev = last;
            this->head->next = first;
            first->prev = this->head;
        }
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
    void mergeSort(typename DLinkedList<T>::Node*& head, int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
        if(head != 0 && head->next != 0){
            typename DLinkedList<T>::Node* second;
            devide(head, second);
            mergeSort(head, comparator);
            mergeSort(second, comparator);
            merge(head, second, comparator);
        }
    };
    void devide(typename DLinkedList<T>::Node*& first, typename DLinkedList<T>::Node*& second){
        //YOUR CODE HERE
        typename DLinkedList<T>::Node* midpoint = first;
        typename DLinkedList<T>::Node* last = first->next;
        while (last != 0)
        {
            last = last->next;
            if(last!=0){
                last = last->next;
                midpoint = midpoint->next;
            }
        }
        second = midpoint->next;
        midpoint->next = 0;
        second->prev = 0;
    }

    void merge(typename DLinkedList<T>::Node*& first, typename DLinkedList<T>::Node*& second, int (*comparator)(T&,T&)=0){
        //YOUR CODE HERE
        typename DLinkedList<T>::Node combined;
        typename DLinkedList<T>::Node* lastSorted = &combined;
        while(first != 0 && second!=0){
            if(compare(first->data , second->data, comparator) <= 0){
                lastSorted->next = first;
                lastSorted = first;
                first = first->next;
            }
            else {
                lastSorted->next = second;
                lastSorted = second;
                second = second->next;
            }
        }
        while(first != 0){
            lastSorted->next = first;
            lastSorted = first;
            first = first->next;
        }
        while(second != 0){
            lastSorted->next = second;
            lastSorted = second;
            second = second->next;
        }
        typename DLinkedList<T>::Node *ptr2 = &combined;
        while (ptr2->next != NULL){
            ptr2->next->prev = ptr2;
            ptr2 = ptr2->next;
        }
        first = combined.next;
    }
};

#endif /* DLINKEDLISTSE_H */

