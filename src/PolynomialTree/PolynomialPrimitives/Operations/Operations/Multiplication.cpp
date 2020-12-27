//
// Created by Nik Carlson on 12.12.2020.
//

#include "Multiplication.h"

Multiplication::Multiplication(Node *left, Node *right): AbstractBinaryOperation(left, right, "*", Associativity::LEFT) {
}

std::string Multiplication::get_name() {
    return "*";
}
