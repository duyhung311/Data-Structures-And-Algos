/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightSelectionSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 17:10
 */

#ifndef STRAIGHTSELECTIONSORT_H
#define STRAIGHTSELECTIONSORT_H

#include "sorting/ISort.h"


template<class T>
class StraightSelectionSort: public ISort<T>{
public:   

    void sort(T array[], int size, int (*comparator)(T&,T&), int stride=1){
        //YOUR CODE HERE
        for(int i = 0 ; i < size -1 ; i+=stride){
            T temp = array[i];
            int minIdx = findMin(array,i,size,comparator,stride);
            array[i] = array[minIdx];
            array[minIdx] = temp;
        }
    }
protected:
    int findMin(T array[], int start, int size, int (*comparator)(T&,T&), int stride=1){
        T min = array[start];
        int ind = start;
        for(int i = start; i< size; i+=stride){
            if(comparator!=nullptr){
                if(comparator(array[i], min)<0){
                    ind = i;
                    min = array[ind];
                }
            }
            else 
                if(array[i] < min){
                    ind = i;
                    min = array[ind];
                }
            
               
        }
        return ind;
    }
    
};



#endif /* STRAIGHTSELECTIONSORT_H */

