//
// Created by Nik Carlson on 12.12.2020.
//

#include "BinaryMinus.h"

BinaryMinus::BinaryMinus(Node *left, Node *right): AbstractBinaryOperation(left, right, "-", Associativity::LEFT) {
}

std::string BinaryMinus::get_name() {
    return "-";
}
