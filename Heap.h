#ifndef HEAP_H
#define HEAP_H

#include "Array.h"

template <class T>
class IHeap {
protected:
    Array<T> array;
public:
    IHeap() {}
    virtual ~IHeap() = default;
    
    // Common interface methods
    virtual void push(T item) = 0;
    virtual T pop() = 0;
    bool isEmpty() const { return array.getSize() == 0; }
    T& top () {return array[0];}

};

template <class T>
class MaxHeap : public IHeap<T> {
private:
    void reheapUp(int index) {
        if (index <= 0) return;
        int parent = (index - 1) / 2;
        if (this->array[index] > this->array[parent]) {
            std::swap(this->array[index], this->array[parent]);
            reheapUp(parent);
        }
    }

    void reheapDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int biggest = index;

        if (left < this->array.size() && this->array[left] > this->array[biggest])
            biggest = left;
        if (right < this->array.size() && this->array[right] > this->array[biggest])
            biggest = right;

        if (biggest != index) {
            std::swap(this->array[index], this->array[biggest]);
            reheapDown(biggest);
        }
    }

public:
    void push(T item) override {
        this->array.push(item); 
        reheapUp(this->array.size() - 1);
    }

    T pop() override {
        T root = this->array[0];
        this->array[0] = this->array[this->array.size() - 1];
        this->array.pop(); 
        reheapDown(0);
        return root;
    }
};

template <class T>
class MinHeap : public IHeap<T> {
private:
    void reheapUp(int index) {
        if (index <= 0) return;
        int parent = (index - 1) / 2;
        if (this->array[index] < this->array[parent]) {
            std::swap(this->array[index], this->array[parent]);
            reheapUp(parent);
        }
    }

    void reheapDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < this->array.size() && this->array[left] < this->array[smallest])
            smallest = left;
        if (right < this->array.size() && this->array[right] < this->array[smallest])
            smallest = right;

        if (smallest != index) {
            std::swap(this->array[index], this->array[smallest]);
            reheapDown(smallest);
        }
    }

public:
    void push(T item) override {
        this->array.push(item); // Assuming Array has push_back
        reheapUp(this->array.size() - 1);
    }

    T pop() override {
        T root = this->array[0];
        this->array[0] = this->array[this->array.size() - 1];
        this->array.pop(); 
        reheapDown(0);
        return root;
    }
};

#endif