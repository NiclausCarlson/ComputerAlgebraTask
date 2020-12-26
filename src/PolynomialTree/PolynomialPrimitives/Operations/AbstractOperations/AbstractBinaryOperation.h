//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_ABSTRACTBINARYOPERATION_H
#define COMPUTERALGEBRATASK_ABSTRACTBINARYOPERATION_H


#include "../../Node/Node.h"
#include "../../Associativity.h"

class AbstractBinaryOperation : public Node {
protected:
    Node *left;
    Node *right;
    const Associativity associative; // false - left, true - right
    const std::string type;
public:
    AbstractBinaryOperation(Node *, Node *, std::string, Associativity);

    std::string get_name() override;

    std::string to_str() override;

    Node const *getLeftNode() const;

    Node const *getRightNode() const;

    Node *getLeftNode();

    Node *getRightNode();

    void get_monomials(std::vector<Node*>& monomials) override;

    ~AbstractBinaryOperation() = default;
};


#endif //COMPUTERALGEBRATASK_ABSTRACTBINARYOPERATION_H
