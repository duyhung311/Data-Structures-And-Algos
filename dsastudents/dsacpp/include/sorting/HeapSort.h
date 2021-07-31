/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeapSort.h
 * Author: LTSACH
 *
 * Created on 14 September 2020, 18:10
 */

#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "ISort.h"
#include "heap/Heap.h"

template<class T>
class HeapSort: private Heap<T>, public ISort<T>{
public:
    HeapSort(   int (*comparator)(T& , T&)=0, 
                void (*deleteUserData)(Heap<T>*)=0 ):
                Heap<T>(comparator, deleteUserData){
    }
    void sort(T array[], int size, int (*comparator)(T&,T&)=0, int stride=1){  
        //YOUR CODE HERE
        if(comparator == nullptr){
            Heap<T>  minHeap;
            int i = 0 , j = 0;
            if(stride > 1){
                int capa = size/stride;
                T *temp = new T[capa];
                for(j = 0 ; j < stride ;j++){
                  temp[j] = array[i];
                  i+=stride;
                }
                minHeap.heapify(temp, capa);
                delete []temp;
            }else minHeap.heapify(array,size);
            i = 0;
            while(!minHeap.empty()){
                T min = minHeap.pop();
                array[i] = min;
                i+=stride;
            }
        }
        else{
            Heap<T> heap(comparator);
            int i = 0 , j = 0;
            if(stride > 1){
                int capa = size/stride;
                T *temp = new T[capa];
                for(j = 0 ; j < stride ;j++){
                  temp[j] = array[i];
                  i+=stride;
                }
                heap.heapify(temp, capa);
                delete []temp;
            }else heap.heapify(array,size);
            i = 0;
            while(!heap.empty()){
                T head = heap.pop();
                array[i] = head;
                i+=stride;
            }
        }
    }         
                
};


#endif /* HEAPSORT_H */

