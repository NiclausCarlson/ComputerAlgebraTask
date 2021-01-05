//
// Created by Nik Carlson on 12.12.2020.
//

#include "Exponentiation.h"

Exponentiation::Exponentiation(Node *left, Node *right) : AbstractBinaryOperation(left, right, "^",
                                                                                  Associativity::RIGHT) {
}

std::string Exponentiation::get_name() {
    return "^";
}

void Exponentiation::get_terms(std::vector<Node *> &terms) {
    terms.push_back(this);
}
