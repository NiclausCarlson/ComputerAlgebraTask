//
// Created by Nik Carlson on 12.12.2020.
//

#include "Variable.h"


Variable::Variable(std::string name) : name(std::move(name)) {
}

std::string Variable::get_value() const {
    return name;
}

std::string Variable::to_str() {
    return name;
}

void Variable::get_monomials(std::vector<Node *> &monomials) {
    monomials.push_back(this);
}

void Variable::get_terms(std::vector<Node *> &terms) {
    this->get_monomials(terms);
}

Variable *Variable::clone() {
    return new Variable(*this);
}
