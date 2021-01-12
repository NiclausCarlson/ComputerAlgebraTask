//
// Created by Nik Carlson on 05.01.2021.
//
#ifndef COMPUTERALGEBRATASK_SIMPLIFY_H
#define COMPUTERALGEBRATASK_SIMPLIFY_H

#include <algorithm>

#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../MonomialOrder/MonomialOrder.h"
#include "Equals.h"

PolynomialTree recursive(std::vector<Node *>::iterator from,
                         std::vector<Node *>::iterator to);

PolynomialTree join_monomials(std::vector<Node *> &monomials);

//This method returns simplified polynomial
PolynomialTree get_simplified(PolynomialTree &t, MonomialOrder *order);

#endif //COMPUTERALGEBRATASK_SIMPLIFY_H
