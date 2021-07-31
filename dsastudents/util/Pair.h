/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pair.h
 * Author: LDHUNG
 *
 * Created on 10 July 2021, 1:24
 */

#ifndef Pair_H
#define Pair_H

#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>
using namespace std;

#define EPSILON (1E-8)

template <class T, class V>
class Pair{
private:
    T x;
    V y;
    friend ostream &operator<<( ostream &os, const Pair& Pair);
    
public:
    Pair(T x=0, V y=0){
        this->x = x;
        this->y = y;
    }
    Pair(const Pair& Pair){
        this->x = Pair.x;
        this->y = Pair.y;
    }
    
    void setY(V y) {
        this->y = y;
    }

    V getY() const {
        return y;
    }

    void setX(T x) {
        this->x = x;
    }

    T getX() const {
        return x;
    }
    

    //with Pair object
    bool operator==(Pair rhs){
        return  (abs(this->x - rhs.x) < EPSILON) &&
                (abs(this->y - rhs.y) < EPSILON);
    }
    
    //with POINTER to Pair
    static bool PairEQ(Pair& lhs, Pair& rhs){
        return  lhs == rhs;
    }
    //with POINTER to Pair
    static bool PairEQ(Pair*& lhs, Pair*& rhs){
        return  *lhs == *rhs;
    }
    
    static string Pair2str(Pair& Pair){
        stringstream os;
        os  << Pair;
        return os.str();
    }
    static string Pair2str(Pair*& Pair){
        return Pair2str(*Pair);
    }

    static Pair* genPairs(int size, float minValue=0, float maxValue=1, 
                            bool manualSeed=false, int seedValue=0){
        Pair* head = new Pair[size];
        std::default_random_engine* engine;
        if(manualSeed)
            engine = new std::default_random_engine(static_cast<long unsigned int>(seedValue));
        else
            engine = new std::default_random_engine(static_cast<long unsigned int>(time(0)));
        uniform_real_distribution<T> dist1(minValue, maxValue);
        uniform_real_distribution<V> dist2(minValue, maxValue);
        
        for(int idx=0; idx < size; idx++){
            T x = dist1(*engine);
            V y = dist2(*engine);
            head[idx] = Pair(x,y);
        }
        delete engine;
        return head;
    }
    static void println(Pair* head, int size){
        stringstream os;
        os << "[";
        for(int idx=0; idx < size-1; idx++)
            os << head[idx] << ", ";
        if(size > 0) os << head[size-1] << "]";
        else os << "]";
        cout << os.str() << endl;
        return;
    }
   
};
ostream &operator<<( ostream &os, const Pair& Pair){
    os << "P(" << fixed 
            << setw(6) << setprecision(2) << Pair.x << "," 
            << setw(6) << setprecision(2) << Pair.y << ")";
    return os;
}



#endif /* Pair_H */

