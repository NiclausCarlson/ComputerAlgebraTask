//
// Created by Nik Carlson on 12.12.2020.
//

#include "Constant.h"

Constant::Constant(const Rational& value) : value(value), stringValue(value.to_str()) {
}

Rational Constant::get_value() const {
    return value;
}

std::string Constant::to_str() {
    return stringValue;
}

void Constant::get_monomials(std::vector<Node *> &monomials) {
    monomials.push_back(this);
}

