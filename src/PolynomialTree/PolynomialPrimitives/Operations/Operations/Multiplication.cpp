//
// Created by Nik Carlson on 12.12.2020.
//

#include "Multiplication.h"

Multiplication::Multiplication(Node *left, Node *right) : AbstractBinaryOperation(left, right, "*",
                                                                                  Associativity::LEFT) {
}

std::string Multiplication::get_name() {
    return "*";
}

void Multiplication::get_terms(std::vector<Node *> &terms) {
    auto *left_checker = dynamic_cast<Multiplication *> (this->left);
    if (left_checker != nullptr) {
        left_checker->get_terms(terms);
    } else {
        terms.push_back(this->left);
    }

    auto *right_checker = dynamic_cast<Multiplication *> (this->right);
    if (right_checker != nullptr) {
        right_checker->get_terms(terms);
    } else {
        terms.push_back(this->right);
    }
}
