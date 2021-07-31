/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightInsertionSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 16:24
 */

#ifndef STRAIGHTINSERTIONSORT_H
#define STRAIGHTINSERTIONSORT_H
#include "sorting/ISort.h"

template<class T>
class StraightInsertionSort: public ISort<T>{
public:
    void sort(T array[], int size, int (*comparator)(T&,T&), int stride=1){
        //YOUR CODE HERE
        T temp;
        int index;
        for(int i = stride ; i< size;i+=stride){
            temp = array[i];
            index = i-stride;
            while(index >= 0){
                if(comparator != 0) {
                    if(comparator(array[index], temp) > 0){
                        array[index+stride] = array[index];
                        index-=stride;
                    }
                    else break;
                }
                else {
                    if(array[index] > temp){
                        array[index+stride] = array[index];
                        index-=stride;
                    }
                    else break;
                }   
            }
            array[index+stride] = temp;
        }
    }
};

#endif /* STRAIGHTINSERTIONSORT_H */

