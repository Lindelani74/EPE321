#ifndef NODE_H
#define NODE_H

template<class T>
class Node
{
public:
    Node(T data){
        element = data;
        next = nullptr;
    }

    T element;
    Node<T> *next;
};

#endif // NODE_H
