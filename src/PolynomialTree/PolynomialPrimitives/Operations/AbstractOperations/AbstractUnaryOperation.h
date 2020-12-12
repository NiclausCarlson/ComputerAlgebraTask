//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_ABSTRACTUNARYOPERATION_H
#define COMPUTERALGEBRATASK_ABSTRACTUNARYOPERATION_H


#include "../../Node/Node.h"

class AbstractUnaryOperation : public Node {
protected:
    Node *operand;
    const std::string type;
public:
    AbstractUnaryOperation(Node *, std::string);

    std::string get_name() override;

    std::string to_str() override;

    Node const *getOperand() const;

    Node *getOperand();

    ~AbstractUnaryOperation() = default;
};


#endif //COMPUTERALGEBRATASK_ABSTRACTUNARYOPERATION_H
