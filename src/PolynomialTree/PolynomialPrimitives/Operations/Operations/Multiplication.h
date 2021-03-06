//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_MULTIPLICATION_H
#define COMPUTERALGEBRATASK_MULTIPLICATION_H


#include "../AbstractOperations/AbstractBinaryOperation.h"

class Multiplication : virtual public AbstractBinaryOperation {
public:
    Multiplication(Node *, Node *);

    Multiplication *clone() override;

    std::string get_name() override;

    void get_terms(std::vector<Node *> &terms) override;
};


#endif //COMPUTERALGEBRATASK_MULTIPLICATION_H
