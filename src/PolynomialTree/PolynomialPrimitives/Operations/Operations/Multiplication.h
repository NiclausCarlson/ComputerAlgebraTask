//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_MULTIPLICATION_H
#define COMPUTERALGEBRATASK_MULTIPLICATION_H


#include "../AbstractOperations/AbstractBinaryOperation.h"

class Multiplication: virtual public AbstractBinaryOperation {
public:
    Multiplication(Node*, Node*);

    std::string get_name() override;

};


#endif //COMPUTERALGEBRATASK_MULTIPLICATION_H
