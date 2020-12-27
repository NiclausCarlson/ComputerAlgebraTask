//
// Created by Nik Carlson on 12.12.2020.
//

#include "UnaryMinus.h"

UnaryMinus::UnaryMinus(Node *operand) : AbstractUnaryOperation(operand, "-", Associativity::RIGHT) {
}

std::string UnaryMinus::get_name() {
    return "--";
}
