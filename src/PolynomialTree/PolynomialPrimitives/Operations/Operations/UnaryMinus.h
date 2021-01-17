//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_UNARYMINUS_H
#define COMPUTERALGEBRATASK_UNARYMINUS_H


#include "../AbstractOperations/AbstractUnaryOperation.h"

class UnaryMinus : virtual public AbstractUnaryOperation {
public:
    explicit UnaryMinus(Node *);

    UnaryMinus *clone() override;

    std::string get_name() override;

    void get_terms(std::vector<Node *> &terms) override;

};


#endif //COMPUTERALGEBRATASK_UNARYMINUS_H
