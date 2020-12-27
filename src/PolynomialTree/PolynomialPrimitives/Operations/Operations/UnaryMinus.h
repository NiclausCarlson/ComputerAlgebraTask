//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_UNARYMINUS_H
#define COMPUTERALGEBRATASK_UNARYMINUS_H


#include "../AbstractOperations/AbstractUnaryOperation.h"

class UnaryMinus : virtual public AbstractUnaryOperation {
public:
     UnaryMinus(Node *);

    std::string get_name() override;

};


#endif //COMPUTERALGEBRATASK_UNARYMINUS_H
