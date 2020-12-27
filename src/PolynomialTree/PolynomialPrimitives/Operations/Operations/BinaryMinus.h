//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_BINARYMINUS_H
#define COMPUTERALGEBRATASK_BINARYMINUS_H


#include "../AbstractOperations/AbstractBinaryOperation.h"

class BinaryMinus : virtual public AbstractBinaryOperation {
public:
    BinaryMinus(Node *, Node *);

    std::string get_name() override;

};


#endif //COMPUTERALGEBRATASK_BINARYMINUS_H
