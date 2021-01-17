//
// Created by Nik Carlson on 12.12.2020.
//

#include "Sum.h"

Sum::Sum(Node *left, Node *right) : AbstractBinaryOperation(left, right, "+", Associativity::LEFT) {
}

std::string Sum::get_name() {
    return "+";
}

void Sum::get_terms(std::vector<Node *> &terms) {
    throw nullptr; // TODO: create exception
}

Sum *Sum::clone() {
    return new Sum(*this);
}
