//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_ABSTRACTUNARYOPERATION_H
#define COMPUTERALGEBRATASK_ABSTRACTUNARYOPERATION_H


#include "../../Node/Node.h"
#include "../../Associativity.h"

class AbstractUnaryOperation : public Node {
protected:
    Node *operand;
    const Associativity associative; // false - left, true - right
    const std::string type;
public:
    AbstractUnaryOperation(Node *, std::string, Associativity);

    std::string get_name() override;

    std::string to_str() override;

    Node const *getOperand() const;

    Node *getOperand();

    ~AbstractUnaryOperation() = default;
};


#endif //COMPUTERALGEBRATASK_ABSTRACTUNARYOPERATION_H
