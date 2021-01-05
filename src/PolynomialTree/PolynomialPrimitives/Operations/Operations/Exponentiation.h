//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_EXPONENTIATION_H
#define COMPUTERALGEBRATASK_EXPONENTIATION_H


#include "../AbstractOperations/AbstractBinaryOperation.h"

class Exponentiation : virtual public AbstractBinaryOperation {
public:
    Exponentiation(Node *, Node *);

    std::string get_name() override;

    void get_terms(std::vector<Node *> &terms) override;
};


#endif //COMPUTERALGEBRATASK_EXPONENTIATION_H
