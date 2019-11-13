#include <iostream>

#include "tester/tester.h"
#include "matrix.h"

/*
void trials(){
    Matrix<int> M(2, 2);
    M.set(1,1,4);
    M.set(1,0,3);
    M.set(0,1,2);
    M.set(0,0,1);
    //M.set(2,0,5);
    //M.set(2,1,6);
    M.print();

    Matrix<int> N(2,2);
    N.set(1, 1, 2);
    N.set(1, 0, 3);
    N.set(0, 1, 5);
    N.set(0, 0, 5);
    N.set(0, 0, 6);
    //N.set(1, 2, 1);
    //N.set(0, 2, 4);
    N.print();
    auto X = N+M;
    X.print();
}

*/
int main() {
    //trials();
    Tester::execute();
    return EXIT_SUCCESS;
}

