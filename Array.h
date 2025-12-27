#ifndef ARRAY_H
#define ARRAY_H

#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

template <class T>
class Array{
private:
    int currentSize;
    int capacity;
    T* arr;
public:
    class Iterator {
    private:
        int curr;
        const Array* pointer;
    public:
        Iterator () : curr(0), pointer(nullptr) {}
        Iterator (int curr, const Array* p) : curr(curr), pointer(p) {}
        Iterator& operator++() { ++curr; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++*this; return tmp; }
        Iterator& operator--() { --curr; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --*this; return tmp; }
        bool operator==(const Iterator& iter2) const { return curr==iter2.curr && pointer==iter2.pointer; }
        bool operator!=(const Iterator& iter2) const { return !(*this==iter2); }
        Iterator operator-() const { return Iterator(-curr, pointer); }
        Iterator& operator+=(int cnt) { curr+=cnt; return *this; }
        Iterator& operator-=(int cnt) { curr-=cnt; return *this; }
        T& operator*() const { return const_cast<T&>(pointer->arr[curr]); }
        ~Iterator () = default;

        friend class Array;
    };
    friend class Iterator;
    
private:
    void ensureCapacity (int n)
    {
        if (n<=capacity) return;
        int newCap = std::max(capacity*2, n);
        if (newCap<1) newCap = 1;
        T* newArr = new T[newCap];
        for (int i=0;i<currentSize;++i) newArr[i]=arr[i];
        delete [] arr;
        arr = newArr;
        capacity = newCap;
    }
    inline void createArray (int cap, int currSize) 
    {
        this->capacity=cap;
        this->currentSize=currSize;
        this->arr=new T [cap];
    }
public:
    void clear ()
    {
        delete[] this->arr;
        this->capacity=this->currentSize=0;
        this->arr = nullptr;
    }
    Array (int n=10) 
    {
        n=n<=0?10:n;
        createArray(n, 0);
    }
    Array (Iterator begin, Iterator end)
    {
        if (begin.pointer==end.pointer && begin.pointer!=nullptr) {
            int cap = this->distance (begin, end);
            if (cap>0) {
                createArray (cap, cap);
                for (int i=0;i<cap;++i) this->arr[i]=begin.pointer->arr[begin.curr+i];
            } else createArray(10,0);
        }
        else createArray(10, 0);
    }
    Array (std::initializer_list<T> list)
    {
        int cap = (int)list.size();
        this->capacity=this->currentSize=cap<=0?10:cap;
        this->arr= new T [this->capacity];
        int i=0;
        for(const T& item : list) this->arr[i++]=item;
    }
    T& operator[](int index)
    {
        if (index<0 || index>=currentSize) 
        {
            throw std::out_of_range("Array index is out of bounds!");
        }
        return this->arr[index];
    }
    const T& operator[](int index) const
    {
        if (index<0 || index>=currentSize) 
        {
            throw std::out_of_range("Array index is out of bounds!");
        }
        return this->arr[index];
    }
    Array& operator=(std::initializer_list<T> list)
    {
        delete[] arr;

        int cap = (int)list.size();
        this->capacity = this->currentSize = (cap <= 0) ? 10 : cap;

        this->arr = new T[this->capacity];
        
        int i = 0;
        for (const T& item : list) this->arr[i++] = item;
        
        return *this;
    }
    Array& operator=(const Array& other)
    {
        if (this==&other) return *this;
        delete[] arr;
        this->capacity=other.capacity;
        this->currentSize=other.currentSize;
        this->arr = new T[this->capacity];
        for (int i=0;i<other.currentSize;++i) this->arr[i]=other.arr[i];
        return *this;
    }
    Array& operator=(Array& other)
    {
        return operator=((const Array&)other);
    }
    bool operator==(const Array& other) const
    {
        if (this==&other) return true;
        if (this->currentSize!=other.currentSize) return false;
        for (int i=0; i<this->currentSize;++i) 
            if (this->arr[i]!=other.arr[i]) return false;

        return true;
    }
    bool operator==(Array& other) const
    {
        return operator==((const Array&)other);
    }
    Array operator+(const Array& other)
    {
        Array res(this->currentSize + other.currentSize);
        for (int i=0;i<this->currentSize;++i) res.arr[res.currentSize++]=this->arr[i];
        for (int j=0;j<other.currentSize;++j) res.arr[res.currentSize++]=other.arr[j];
        return res;
    }
    Array operator+(Array& other)
    {
        return operator+((const Array&)other);
    }
    bool operator!=(const Array& other) const
    {
        return !this->operator==(other);
    }
    bool operator!=(Array& other) const
    {
        return !this->operator==((const Array&)other);
    }
    ~Array () 
    {
        delete[] arr;
    }
    void push (T val)
    {
        ensureCapacity(this->currentSize+1);
        this->arr[currentSize]=val;
        this->currentSize++;
    }
    void pop ()
    {
        if (this->currentSize<=0) throw std::out_of_range("Array is empty now!");
        this->currentSize--;
    }
    void insert (T val, int index)
    {
        if (index >= this->currentSize) 
        {
            this->push (val);
        }
        else 
        {
            if (index<0) throw std::out_of_range("Index out of range");
            ensureCapacity (this->currentSize+1);
            for (int i = this->currentSize; i>index; --i)
            {
                this->arr[i]=this->arr[i-1];
            }
            this->arr[index]=val;
            this->currentSize++;
        }
    }
    bool remove (int index){
        if (index<0 || index>=currentSize) return false;
        for (int i=index;i+1<currentSize;++i) arr[i]=arr[i+1];
        --currentSize;
        return true;
    }
    void replace (T val, int index){
        if (index<0 || index>=currentSize) throw std::out_of_range("Index out of range");
        arr[index]=val;
    }
    void reverse (){
        for (int i=0,j=currentSize-1;i<j;++i,--j) std::swap(arr[i],arr[j]);
    }
    
    int size() const
    {
        return this->currentSize;
    }
    int distance (Iterator iter){
        return iter.curr;
    }
    int distance (Iterator iter1, Iterator iter2){
        if (iter1.pointer!=iter2.pointer) throw std::invalid_argument("Iterators from different containers");
        return iter2.curr - iter1.curr;
    }
    
    bool empty () const{
        return this->currentSize==0;
    }
    Iterator find (T val){ //not find -> return arr.begin()
        for (int i=0;i<currentSize;++i) if (arr[i]==val) return Iterator(i,this);
        return begin();
    }
    Iterator begin() const{
        return Iterator(0,this);
    }
    Iterator end() const{
        return Iterator(currentSize,this);
    }

};

#endif