/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShellSort.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 16:45
 */

#ifndef SHELLSORT_H
#define SHELLSORT_H
#include "ISort.h"

template<class T>
class ShellSort: public ISort<T>{
private:
    int *num_segment_list;
    int num_phases;
    
public:
    ShellSort(int *num_segment, int num_phases){
        this->num_phases = num_phases;
        this->num_segment_list = new int[num_phases];
        for(int idx=0; idx < num_phases; idx++) 
            this->num_segment_list[idx] = num_segment[idx];
    }
    ~ShellSort(){
        delete []num_segment_list;
    }
    
    
    void sortSegment(T array[], int size, 
            int segment_idx, int cur_segment_total,
            int (*comparator)(T&, T&), int stride = 1){
        //YOUR CODE HERE
        int current, walker;
        T temp;
        current = segment_idx*stride + cur_segment_total*stride;
        while (current < size)
        {
            temp = array[current];
            walker = current - cur_segment_total*stride;
            while(walker >=0 && comparator(temp, array[walker])<0){
                array[walker + cur_segment_total*stride] = array[walker];
                walker-= (cur_segment_total*stride);
            }
            array[walker + cur_segment_total*stride] = temp;
            current += (cur_segment_total*stride);
        }
        
    }
    /*
    shell_sort
    -----------
    num_segments: 
         + The first must be 1, for examples: [1,3,7]
    */
    void sort(T array[], int size, int (*comparator)(T&,T&), int stride=1){
        //YOUR CODE HERE
        for(int k = this->num_phases-1; k >=0 ; k --){
            int segment = num_segment_list[k];
            for(int segment_i = 0; segment_i < segment; segment_i++){
                sortSegment(array,size, segment_i, segment, comparator, stride);
            }
        }
    }
};

#endif /* SHELLSORT_H */

