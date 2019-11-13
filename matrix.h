#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <iomanip>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned Xs, Ys;

public:
    Matrix(unsigned rows, unsigned columns){
        root = new Node<T>;
        Xs = rows;
        Ys = columns;
        auto aux = root;
        for (unsigned i = 0; i < rows; ++i) {
            auto down = new Node<T>;
            down->posX = i;
            aux->down = down;
            aux = down;
        }
        aux = root;
        for (unsigned i = 0; i < columns; ++i) {
            auto next = new Node<T>;
            next->posY = i;
            aux->next = next;
            aux = next;
        }
    }

    Node<T>* getNode(unsigned X, unsigned Y) const{
        auto aux = root->next;
        while (aux->posY != Y){
            aux = aux->next;
        }
        while(aux->down and aux->down->posX < X){
            aux = aux->down;
        }
        if(aux->down) {
            if (aux->down->posX == X) return aux->down;
            else return nullptr;
        }else return nullptr;
    }


    void set(unsigned X, unsigned Y, T val){
        auto aux = root->next;
        while (aux->posY != Y){
            aux = aux->next;
        }
        while(aux->down and aux->down->posX < X){
            aux = aux->down;
        }
        Node<T> *temp = nullptr;
        if (aux->down) {
            if(aux->down->posX == X){
                if(val == 0){
                    temp = aux->down;
                    aux->down = aux->down->down;
                    aux = root->down;
                    while (aux->posX != X){
                        aux = aux->down;
                    }
                    while (aux->next != temp){
                        aux = aux->next;
                    }
                    aux->next = aux->next->next;
                    delete temp;
                } else aux->down->value = val;
                return;
            } else temp = aux->down;
        }
        if(val == 0) return;
        aux->down = new Node<T>(X,Y, val);
        if (temp) aux->down->down = temp;
        temp = aux->down;
        aux = root->down;
        while (aux->posX != X) {
            aux = aux->down;
        }
        while (aux->next and aux->next->posY < Y) {
            aux = aux->next;
        }
        Node<T> *temp2 = nullptr;
        if (aux->next) temp2 = aux->next;
        aux->next = temp;
        if (temp2) aux->next->next = temp2;
    }

    T operator()(unsigned X, unsigned Y) const{
        auto ans = getNode(X,Y);
        if(ans) return ans->value;
        else return 0;
    }

    Matrix<T> operator*(T scalar) {
        Matrix<T> AnsMatrix(Xs, Ys);
        auto auxMain = root;
        for (unsigned i = 0; i < Xs; ++i) {
            auxMain = auxMain->down;
            auto aux2 = auxMain;
            while (aux2->next){
                aux2 = aux2->next;
                AnsMatrix.set(aux2->posX, aux2->posY, aux2->value*scalar);

            }
        }
        return AnsMatrix;
    }

    Matrix<T> operator*(Matrix<T> other) const{
        Matrix<T> AnsMatrix(Xs, other.Ys);
        for (int x = 0; x < Xs; ++x) {
            for (int y = 0; y < other.Ys; ++y) {
                T newval = 0;
                for (int i = 0; i < Ys; ++i) {
                    if((*this)(x,i) != 0 && other(i,y)!=0){
                        newval += (*this)(x,i)*other(i,y);
                    }
                }
                AnsMatrix.set(x,y,newval);
            }
        }

        return AnsMatrix;
    }

    Matrix<T> operator+(Matrix<T> other) const{
        Matrix<T> AnsMatrix(Xs,Ys);
        for (int i = 0; i < Xs; ++i) {
            for (int j = 0; j < Ys; ++j) {
                T newval = (*this)(i,j) + other(i,j);
                AnsMatrix.set(i,j,newval);
            }
        }
        return AnsMatrix;
    }

    Matrix<T> operator-(Matrix<T> other) const{
        Matrix<T> AnsMatrix(Xs,Ys);
        for (int i = 0; i < Xs; ++i) {
            for (int j = 0; j < Ys; ++j) {
                T newval = (*this)(i,j) - other(i,j);
                AnsMatrix.set(i,j,newval);
            }
        }
        return AnsMatrix;
    }

    Matrix<T> transpose() const{
        Matrix<T> AnsMatrix(Xs,Ys);
        for (int i = 0; i < Xs; ++i) {
            for (int j = 0; j < Ys; ++j) {
                T newval = this->getNode(j,i)->value;
                AnsMatrix.set(i,j,newval);
            }
        }
        return AnsMatrix;

    }

    void print_row(unsigned i) const{
        auto aux = root->down;
        for (unsigned j = 0; j < i; ++j) {
            aux = aux->down;
        }
        bool printed = true;
        for (unsigned k = 0; k < Ys; ++k) {
            if (aux->next && printed){
                aux = aux->next;
                printed = false;
            }
            if (aux->posY == k){
                cout << setw(4) << aux->value;
                printed = true;
            } else {
                cout << setw(4) << "0";
            }
        }

    }
    void print() const {
        for (unsigned i = 0; i < Xs; ++i) {
            print_row(i);
            cout << endl;
        }
        cout << endl;
    }

    void deleteHeader(Node<T>* node, bool X){
        if(X){
            if (node->down) deleteHeader(node->down, true);
        } else {
            if (node->next) deleteHeader(node->next, false);
        }
        delete node;
    }
/*

 PROFESOR EL DESTRUCTOR NO FUNCIONA PERO ESTE AVANCE ES LA LOGICA QUE QUISE IMPLEMENTAR
    ~Matrix(){
        for (int i = 0; i < Xs; ++i) {
            for (int j = 0; j < Ys; ++j) {
                set(i,j,0);
            }
        }
        deleteHeader(root->down,true);
        deleteHeader(root->next,false);
        delete root;

    }
*/
 };

#endif //SPARSE_MATRIX_MATRIX_H