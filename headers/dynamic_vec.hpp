#pragma once

#define INITIAL_SIZE 10

template<class T>
class DynamicVec {
    T* content;
    unsigned content_size;
    
   public:
    DynamicVec();
    ~DynamicVec(); 
    T& operator[](unsigned index);
    unsigned size() const;
};

template<class T>
DynamicVec<T>::DynamicVec() {
    content_size = INITIAL_SIZE;
    content = new T[INITIAL_SIZE];
}

template<class T>
DynamicVec<T>::~DynamicVec() {
    delete content;
}

template<class T>
T& DynamicVec<T>::operator[](unsigned index) {
    if (index >= content_size) {
        unsigned new_size = index + 1;
        T* new_content = new T[new_size];
        for (unsigned i = 0; i < content_size; i++) {
            new_content[i] = content[i];
        }
        delete content;
        content = new_content;
        content_size = new_size;
    }
    return content[index];
}

template<class T>
unsigned DynamicVec<T>::size() const {
    return content_size;
}