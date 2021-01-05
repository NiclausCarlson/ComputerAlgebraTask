//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_SUM_H
#define COMPUTERALGEBRATASK_SUM_H


#include "../AbstractOperations/AbstractBinaryOperation.h"

class Sum : virtual public AbstractBinaryOperation {
public:
    Sum(Node *, Node *);

    std::string get_name() override;

    void get_terms(std::vector<Node *> &terms) override;

};


#endif //COMPUTERALGEBRATASK_SUM_H
