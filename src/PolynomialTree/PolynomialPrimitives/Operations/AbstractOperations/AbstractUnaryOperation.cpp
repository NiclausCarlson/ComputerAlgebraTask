//
// Created by Nik Carlson on 12.12.2020.
//

#include "AbstractUnaryOperation.h"

AbstractUnaryOperation::AbstractUnaryOperation(Node *operand, std::string type, Associativity associative)
        : operand(operand), type(std::move(type)), associative(associative) {
}

Node const *AbstractUnaryOperation::getOperand() const {
    return operand;
}

Node *AbstractUnaryOperation::getOperand() {
    return operand;
}

std::string AbstractUnaryOperation::to_str() {
    return type + operand->to_str();
}

void AbstractUnaryOperation::get_monomials(std::vector<Node *> &monomials) {
    monomials.push_back(this);
}

void AbstractUnaryOperation::get_terms(std::vector<Node *> &terms) {

}
