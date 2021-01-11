//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_ABSTRACTBINARYOPERATION_H
#define COMPUTERALGEBRATASK_ABSTRACTBINARYOPERATION_H


#include "../../Node/Node.h"
#include "../../Associativity.h"

class AbstractBinaryOperation : virtual public Node {
protected:
    Node *left;
    Node *right;
    const Associativity associative;
    const std::string type;
public:
    AbstractBinaryOperation(Node *, Node *, std::string, Associativity);

    virtual std::string get_name() = 0;

    std::string to_str() override;

    void set_left_node(Node* node);

    void set_right_node(Node* node);

    Node *getLeftNode();

    Node *getRightNode();

    void get_monomials(std::vector<Node *> &monomials) override;

    void get_terms(std::vector<Node *> &terms) override = 0;

    ~AbstractBinaryOperation() override = default;
};


#endif //COMPUTERALGEBRATASK_ABSTRACTBINARYOPERATION_H
