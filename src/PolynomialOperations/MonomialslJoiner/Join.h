//
// Created by Nik Carlson on 15.01.2021.
//

#ifndef COMPUTERALGEBRATASK_JOIN_H
#define COMPUTERALGEBRATASK_JOIN_H

#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../MonomialOrder/MonomialOrder.h"

PolynomialTree recursive(std::vector<Node *>::iterator from,
                         std::vector<Node *>::iterator to);

PolynomialTree join_monomials(std::vector<Node *> &monomials);

#endif //COMPUTERALGEBRATASK_JOIN_H
