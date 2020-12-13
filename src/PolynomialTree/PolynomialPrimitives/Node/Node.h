//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_NODE_H
#define COMPUTERALGEBRATASK_NODE_H

#include <string>
#include <utility>

class Node {

public:
    virtual std::string get_name() = 0;

    virtual std::string to_str() = 0;
};

typedef Node *PolynomialTree;

#endif //COMPUTERALGEBRATASK_NODE_H
