//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_DIVIDE_H
#define COMPUTERALGEBRATASK_DIVIDE_H


#include "../AbstractOperations/AbstractBinaryOperation.h"

class Divide: virtual public AbstractBinaryOperation {
public:
    Divide(Node*, Node*);

    std::string get_name() override;

};


#endif //COMPUTERALGEBRATASK_DIVIDE_H
