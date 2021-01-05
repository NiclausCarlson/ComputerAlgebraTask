//
// Created by Nik Carlson on 12.12.2020.
//

#include "Constant.h"

Constant::Constant(ld value) : value(value), stringValue(std::to_string(value)) {
}

ld Constant::get_value() const {
    return value;
}

std::string Constant::to_str() {
    return stringValue;
}

void Constant::get_monomials(std::vector<Node *> &monomials) {
    monomials.push_back(this);
}

void Constant::get_terms(std::vector<Node *> &terms) {
    this->get_monomials(terms);
}

