//
// Created by Nik Carlson on 12.12.2020.
//

#include "UnaryMinus.h"

UnaryMinus::UnaryMinus(Node *operand) : AbstractUnaryOperation(operand, "-", Associativity::RIGHT) {
}

std::string UnaryMinus::get_name() {
    return "-";
}

void UnaryMinus::get_terms(std::vector<Node *> &terms) {
    terms.push_back(this);
    this->operand->get_terms(terms);
}

UnaryMinus *UnaryMinus::clone() {
    return new UnaryMinus(*this);
}
