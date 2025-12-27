#ifndef QUEUE_H
#define QUEUE_H
template <class T>
class Queue {
private:    
    struct Node {
        Node* next;
        T value;
        Node (T val) : value (val) {}
        friend class Queue;
    };
    friend struct Node;
private:
    int currentSize;
    Node* root;
    Node* rear;
public:
    Queue () 
    {
        this->currentSize=0;
        this->root=this->rear=nullptr;
    }
    ~Queue() 
    {
        clear();
    }
    void clear ()
    {
        Node* curr=root;
        while (curr)
        {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    void push (T val)
    {
        Node* newNode = new Node (val);
        if (!root) this->root=this->rear=newNode;
        else 
        {
            rear->next=newNode;
            rear=newNode;
        }
        this->currentSize+=1;
    }
    bool pop ()
    {
        if (root)
        {
            Node* next = this->root->next;
            delete this->root;
            this->root = next;
            this->currentSize-=1;
            return true;
        }
        return false;
    }
    T& top ()
    {
        if (!root) throw std::out_of_range ("empty");
        return this->root->value;
    }
};
#endif