//
// Created by Nik Carlson on 12.12.2020.
//

#include "Divide.h"

Divide::Divide(Node *left, Node *right): AbstractBinaryOperation(left, right, "/", Associativity::LEFT) {
}

std::string Divide::get_name() {
    return "/";
}
