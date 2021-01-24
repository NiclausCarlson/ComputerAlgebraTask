//
// Created by Nik Carlson on 12.12.2020.
//

#include "AbstractBinaryOperation.h"
#include "../Operations/Sum.h"


AbstractBinaryOperation::AbstractBinaryOperation(Node *left, Node *right, std::string type, Associativity associative)
        : left(left), right(right), type(std::move(type)), associative(associative) {
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
        auto *left_checker = dynamic_cast<Sum *>(this->left);
        auto *right_checker = dynamic_cast<Sum *>(this->right);

        if (left_checker != nullptr) this->left->get_monomials(monomials);
        else monomials.push_back(this->left);
        if (right_checker != nullptr) this->right->get_monomials(monomials);
        else monomials.push_back(this->right);

    } else {
        monomials.push_back(this);
    }
}

void AbstractBinaryOperation::set_left_node(Node *node) {
    this->left = node;
}

void AbstractBinaryOperation::set_right_node(Node *node) {
    this->right = node;
}

