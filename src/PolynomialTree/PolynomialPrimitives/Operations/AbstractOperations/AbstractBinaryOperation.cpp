//
// Created by Nik Carlson on 12.12.2020.
//

#include "AbstractBinaryOperation.h"
#include "../Operations/Sum.h"


AbstractBinaryOperation::AbstractBinaryOperation(Node *left, Node *right, std::string type, Associativity associative)
        : left(left), right(right), type(std::move(type)), associative(associative) {
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
    if (associative == Associativity::RIGHT) {
        return left->to_str() + type + right->to_str();
    }
    return left->to_str() + " " + type + " " + right->to_str();
}

void AbstractBinaryOperation::get_monomials(std::vector<Node *> &monomials) {
    auto *sum_checker = dynamic_cast<Sum *>(this);

    if (sum_checker != nullptr) {
        Sum *left_checker = dynamic_cast<Sum *>(this->left);
        Sum *right_checker = dynamic_cast<Sum *>(this->right);

        if (left_checker == nullptr && right_checker == nullptr) {
            this->left->get_monomials(monomials);
            this->right->get_monomials(monomials);
        } else if (left_checker == nullptr) {
            monomials.push_back(this->left);
            this->right->get_monomials(monomials);
        } else if (right_checker == nullptr) {
            this->left->get_monomials(monomials);
            monomials.push_back(this->right);
        } else {
            monomials.push_back(this);
        }

    } else {
        monomials.push_back(this);
    }
}
