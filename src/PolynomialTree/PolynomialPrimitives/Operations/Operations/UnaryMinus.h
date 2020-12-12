//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_UNARYMINUS_H
#define COMPUTERALGEBRATASK_UNARYMINUS_H


#include "../AbstractOperations/AbstractUnaryOperation.h"

class UnaryMinus : protected AbstractUnaryOperation {
public:
    explicit UnaryMinus(Node *);
};


#endif //COMPUTERALGEBRATASK_UNARYMINUS_H
