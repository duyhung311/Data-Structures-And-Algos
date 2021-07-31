/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BubbleSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 17:16
 */

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sorting/ISort.h"

template<class T>
class BubbleSort: public ISort<T>{
public:
    void sort(T array[], int size, int (*comparator)(T&,T&), int stride=1){
        //YOUR CODE HERE
        for(int i = 0 ; i < size ; i+=stride){
            bool haveswap = false;
            for(int j = 0 ; j < (size - i - stride) ;j+=stride){
                if(comparator==0){
                    if(array[j] > array[j+stride]){
                        swap(array[j], array[j+stride]);
                        haveswap = true;
                    }
                }
                else{
                    if(comparator(array[j] , array[j+stride]) > 0){
                        swap(array[j], array[j+stride]);
                        haveswap = true;
                    }
                }
            }
            if(haveswap == false)  break;
        }
        
    }
};


#endif /* BUBBLESORT_H */

