//
// Created by Nik Carlson on 12.12.2020.
//

#include "Multiplication.h"
#include "UnaryMinus.h"

Multiplication::Multiplication(Node *left, Node *right) : AbstractBinaryOperation(left, right, "*",
                                                                                  Associativity::LEFT) {
}

std::string Multiplication::get_name() {
    return "*";
}

void Multiplication::get_terms(std::vector<Node *> &terms) {
    auto adder = [&](Node *node) {
        auto *mult_checker = dynamic_cast<Multiplication *> (node);
        if (mult_checker != nullptr) {
            mult_checker->get_terms(terms);
        } else {
            auto *minus_checker = dynamic_cast<UnaryMinus *> (node);
            if (minus_checker != nullptr) {
                node->get_terms(terms);
            } else {
                terms.push_back(node);
            }
        }
    };

    adder(this->left);
    adder(this->right);
}
