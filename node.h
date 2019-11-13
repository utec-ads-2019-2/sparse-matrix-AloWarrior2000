#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next, *down;
    unsigned posX, posY;
    T value;

public:
    Node(){
        posY = 0;
        posX = 0;
        next = nullptr;
        down = nullptr;
    }

    Node(unsigned x, unsigned y, T v){
        posY = y;
        posX = x;
        value = v;
        next = nullptr;
        down = nullptr;
    }
    friend class Matrix<T>;
};


#endif //SPARSE_MATRIX_NODE_H
