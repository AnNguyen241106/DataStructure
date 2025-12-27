#ifndef STACK_h
#define STACK_H
template <class T>
class Stack {
private:
    int currentSize;
    int capacity;
    T* data;
private:
    void ensureCapacity (int size)
    {
        if (size >= this->capacity) 
        {
            this->capacity+=10;
        }
    }
public:
    Stack (int n=10) 
    {
        this->currentSize=0;
        this->capacity=n;
        this->data=new T[n];
    }
    ~Stack ()
    {
        delete []data;
    }
    void clear ()
    {
        delete []data;
        this->capacity=this->currentSize=0;
    }
    void push (T value)
    {
        ensureCapacity(this->currentSize+1);
        this->data[currentSize]=value;
        this->currentSize+=1;
    }
    T& top()
    {
        if (!currentSize) throw std::out_of_range("empty ");
        return this->data[this->currentSize-1];
    }
    bool pop ()
    {
        if (this->currentSize<=0) return false;
        this->currentSize-=1;
        return true;
    }
};
#endif