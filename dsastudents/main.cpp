#include <memory.h>
template<class T>
class Heap{
public:
    class Iterator; //forward declaration
    
protected:
    T *elements;    //a dynamic array to contain user's data
    int capacity;   //size of the dynamic array
    int count;      //current count of elements stored in this heap
    int (*comparator)(T& lhs, T& rhs);      //see above
    void (*deleteUserData)(Heap<T>* pHeap); //see above
    
public:
    
    Heap(int (*comparator)(T& , T&)=0, void (*deleteUserData)(Heap<T>*)=0 ){ 
        //YOUR CODE HERE
        capacity = 10;
        count = 0 ;
        elements = new T[capacity];
        this->comparator = comparator;
        this->deleteUserData = deleteUserData;
    }
    
   // Heap(const Heap<T>& heap); //copy constructor 
    //Heap<T>& operator=(const Heap<T>& heap); //assignment operator
    
    ~Heap();
    
    //Inherit from IHeap: BEGIN
    void push(T item);
    T pop();
    const T peek();
    void remove(T item);
    int size();
    bool contains(T item);
    void heapify(T array[], int size);
    void clear();
    bool empty();
    //Inherit from IHeap: END
    
    Iterator begin(){
        return Iterator(this, true);
    }
    Iterator end(){
        return Iterator(this, false);
    }
    
public:
    
public:
    bool aLTb(T& a, T& b){
        return compare(a, b) < 0;
    }
    int compare(T& a, T& b){
        if(comparator != 0) return comparator(a, b);
        else{
            if (a < b) return -1;
            else if(a > b) return 1;
            else return 0;
        }
    }
    void ensureCapacity(int minCapacity); 
    void swap(int a, int b);
    void reheapUp(int position);
    void reheapDown(int position);
    int getItem(T item);
    
    
    
    
    
//////////////////////////////////////////////////////////////////////
////////////////////////  INNER CLASSES DEFNITION ////////////////////
//////////////////////////////////////////////////////////////////////
    
public:
    
    //Iterator: BEGIN
    class Iterator{
    private:
        Heap<T>* heap;
        int cursor;
    public:
        Iterator(Heap<T>* heap=0, bool begin=0){
            this->heap = heap;
            if(begin && (heap !=0)) cursor = 0;
            if(!begin && (heap !=0)) cursor = heap->size();
        }
        Iterator& operator=(const Iterator& iterator){
            this->heap = iterator.heap;
            this->cursor = iterator.cursor;
            return *this;
        }
        
        T& operator*(){
            return this->heap->elements[cursor];
        }
        bool operator!=(const Iterator& iterator){
            return this->cursor != iterator.cursor;
        }
        // Prefix ++ overload 
        Iterator& operator++(){
            cursor++;
            return *this; 
        }
        // Postfix ++ overload 
        Iterator operator++(int){
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        }
        void remove(void (*removeItemData)(T)=0){
            this->heap->remove(this->heap->elements[cursor], removeItemData);
        }
    };
    //Iterator: END
};


//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
Heap<T>::~Heap(){
    
}

template<class T>
void Heap<T>::push(T item){ //item  = 25
    //YOUR CODE HERE
    ensureCapacity(count+1);
    elements[count] = item;
    count+=1;
    reheapUp(count-1);
}

template<class T>
T Heap<T>::pop(){
    //YOUR CODE HERE
    T toRet = elements[0];
    elements[0] = elements[count-1];
    count -= 1;
    reheapDown(0);
    return toRet;
}


template<class T>
const T Heap<T>::peek(){
    //YOUR CODE HERE
    if(count == 0)
        throw std::underflow_error("The heap is empty");
    return elements[0];
}

template<class T>
void Heap<T>::remove(T item){
    //YOUR CODE HERE
    int foundIdx = this->getItem(item);
    if(foundIdx == -1) return;
    
    T item1 = elements[foundIdx];
    elements[foundIdx] = elements[this->count -1];
    elements[this->count -1] = item1;
    count--;
    reheapDown(foundIdx);
}

template<class T>
bool Heap<T>::contains(T item){
    //YOUR CODE HERE
    bool found = false;
    for(int idx = 0; idx < count; idx++){
        if(compare(elements[idx],item)==0){
            found = true;
            break;
        }
    }
    return found;
}

template<class T>
int Heap<T>::size(){
    //YOUR CODE HERE
    return count;
}

template<class T>
void Heap<T>::heapify(T array[], int size){
    //YOUR CODE HERE
    for(int i = 0; i < size ;i++) push(array[i]);
}

template<class T>
void Heap<T>::clear(){
    
    capacity = 10;
    count = 0;
    elements= new T[capacity];
    //YOUR CODE HERE
}

template<class T>
bool Heap<T>::empty(){
    //YOUR CODE HERE
    return count == 0 ;
}



//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    if(minCapacity >= capacity){
        //re-allocate 
        int old_capacity = capacity;
        capacity = old_capacity + (old_capacity >> 2);
        try{
            T* new_data = new T[capacity];
            memcpy(new_data, elements, capacity*sizeof(T));
            delete []elements;
            elements = new_data;
        }
        catch(std::bad_alloc e){
            e.what();
        }
    }
}

template<class T>
void Heap<T>::swap(int a, int b){
    T temp = this->elements[a];
    this->elements[a] = this->elements[b];
    this->elements[b] = temp;
}

template<class T>
void Heap<T>::reheapUp(int position){
    //YOUR CODE HERE
    // if(position && compare(elements[(position-1)/2], elements[position]) > 0){
    //     swap(position, (position-1)/2);
    //     reheapUp((position-1)/2);
    // }
    if(position <= 0 || position > count -1) return;
    int parent = (position-1)/2;
    if(aLTb(this->elements[position], this->elements[parent])){
        swap(position, parent);
        reheapUp(parent);
    }
    //reheapUp(parent);
}

template<class T>
void Heap<T>::reheapDown(int position){
    //YOUR CODE HERE
    // int left = position*2+1;
    // int right=  position*2+2;
    // int largest = position;
    // if(left < size() 
    //     && compare(elements[largest], elements[left]) > 0){
    //     largest = left;
    // }
    // if(right < size() 
    //     && compare(elements[largest], elements[right]) > 0){
    //     largest = right;
    // }
    // if(largest!=position){
    //     swap(position, largest);
    //     reheapDown(largest);
    // }
    //if(position < 0 || position > count -1) return;
    int leftChildIndex = 2*position +1;
    int rightChildIndex = 2*position +2;
    int lastPosition = this->count - 1;
    if(leftChildIndex <= lastPosition){
        int smallChildIndex = leftChildIndex;
        if(rightChildIndex <= lastPosition){ 
            if(aLTb(this->elements[leftChildIndex], this->elements[rightChildIndex]))
                smallChildIndex = leftChildIndex;
            else 
                smallChildIndex = rightChildIndex;
        }
        if(aLTb(this->elements[smallChildIndex], this->elements[position])){
            this->swap(smallChildIndex, position);
            reheapDown(smallChildIndex);
        }
    }
}

template<class T>
int Heap<T>::getItem(T item){
    int foundIdx = -1;
    for(int idx=0; idx < this->count; idx++){
        if(compare(elements[idx], item) == 0){
            foundIdx = idx;
            break;
        }
    }
    return foundIdx;
}


int compare(pair<int, int> &a, pair<int, int> &b){
    if(a.first - b.first < 0) return -1;
    else if(a.first - b.first >0) return 1;
    else return 0;
}

int minWaitingTime(int n, int arrvalTime[], int completeTime[]){
   
    Heap<pair<int, int>> h(&compare); 
    for(int i = 0 ; i < n ; i++){
        h.push({arrvalTime[i], completeTime[i]});
    }
    for(auto i = h.begin() ; i!=h.end() ; i++){
        cout << (*i).first << " ";
    }
    cout << endl;
    int minTime   = 0;
    int timeStamp = 0;
    int clock = 0;
    int ite = 0;
    while(ite < n){
        auto temp = h.begin();
        auto next = temp++;
        //cout << "{" <<(*temp).first<<", "<< (*temp).second<<"}  -  "<<"{" <<(*next).first <<", "<< (*next).second <<"}"<< endl;
        if( (*next).second > (*temp).second){ // collision
            cout << "before {" <<(*temp).first<<", "<< (*temp).second<<"}  -  "<<"{" <<(*next).first <<", "<< (*next).second <<"}"<< endl;
            int aI = h.getItem( (*next));
            int bI = h.getItem( (*temp));
            swap(aI, bI);
            cout <<aI << " "<< bI<< "after swap {" <<(*temp).first<<", "<< (*temp).second<<"}  -  "<<"{" <<(*next).first <<", "<< (*next).second <<"}"<< endl;
        }
        int arriveTime;
        if(clock == timeStamp){
            temp = h.begin();
            arriveTime = (*temp).first;
            timeStamp += (*temp).second ;
            h.remove((*h.begin()));
        }
        else {
            clock++;
            continue;
        }
        cout << "[";
        for(auto i = h.begin() ; i!=h.end() ; i++){
            cout << (*i).first << " ";
        }
        cout<< "]"<<endl;
        cout << timeStamp << "  "<<arriveTime<<endl;
        int dur = timeStamp - arriveTime;
        minTime += dur;
        clock++;
        ite++;
        
    }
    return minTime;
    
}

int main(){
int n = 3;
int arrvalTime[] = { 0, 1, 2 };
int completeTime[] = { 3, 9, 6 };

cout << minWaitingTime(n, arrvalTime, completeTime);
system("pause");
}