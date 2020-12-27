//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_NODE_H
#define COMPUTERALGEBRATASK_NODE_H

#include <string>
#include <utility>
#include <vector>

class Node {

public:
    virtual std::string to_str() = 0;

    virtual void get_monomials(std::vector<Node*>& monomials) = 0;
};

typedef Node *PolynomialTree;

#endif //COMPUTERALGEBRATASK_NODE_H
