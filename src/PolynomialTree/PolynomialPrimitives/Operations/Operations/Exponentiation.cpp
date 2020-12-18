//
// Created by Nik Carlson on 12.12.2020.
//

#include "Exponentiation.h"

Exponentiation::Exponentiation(Node *left, Node *right) : AbstractBinaryOperation(left, right, "^", Associativity::RIGHT) {
}
