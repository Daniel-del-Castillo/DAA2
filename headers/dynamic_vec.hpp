#pragma once

#define INITIAL_SIZE 10

template<class T>
class DynamicVec {
    T* content;
    unsigned size;
    
   public:
    DynamicVec();
    ~DynamicVec(); 
    T& operator[](unsigned index);
};

template<class T>
DynamicVec<T>::DynamicVec() {
    size = INITIAL_SIZE;
    content = new T[INITIAL_SIZE];
}

template<class T>
DynamicVec<T>::~DynamicVec() {
    delete content;
}

template<class T>
T& DynamicVec<T>::operator[](unsigned index) {
    if (index >= size) {
        T* new_content = new T[index + INITIAL_SIZE];
        for (unsigned i = 0; i < size; i++) {
            new_content[i] = content[i];
        }
        delete content;
        content = new_content;
        size = index + INITIAL_SIZE;
    }
    return content[index];
}