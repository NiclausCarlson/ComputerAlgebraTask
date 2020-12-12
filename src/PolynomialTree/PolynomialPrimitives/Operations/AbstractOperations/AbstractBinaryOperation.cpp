//
// Created by Nik Carlson on 12.12.2020.
//

#include "AbstractBinaryOperation.h"

AbstractBinaryOperation::AbstractBinaryOperation(Node *left, Node *right, std::string type, bool associative)
        : left(left), right(right), type(std::move(type)), associative(associative) {
}

std::string AbstractBinaryOperation::get_name() {
    return type;
}

Node const *AbstractBinaryOperation::getLeftNode() const {
    return left;
}

Node const *AbstractBinaryOperation::getRightNode() const {
    return right;
}

Node *AbstractBinaryOperation::getLeftNode() {
    return left;
}

Node *AbstractBinaryOperation::getRightNode() {
    return right;
}

std::string AbstractBinaryOperation::to_str() {
    if (associative) {
        return "(" + right->to_str() + " " + type + " " + left->to_str() + ")";
    }
    return "(" + left->to_str() + " " + type + " " + right->to_str() + ")";
}
