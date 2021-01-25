//
// Created by Nik Carlson on 15.01.2021.
//

#ifndef COMPUTERALGEBRATASK_JOIN_H
#define COMPUTERALGEBRATASK_JOIN_H

#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../MonomialOrder/MonomialOrder.h"

PolynomialTree recursive(std::vector<Node *>::const_iterator from,
                         std::vector<Node *>::const_iterator to,
                         char delimiter);

PolynomialTree join(std::vector<Node *> &monomials, char delimiter);

PolynomialTree join(std::vector<Node *>::const_iterator from,
                        std::vector<Node *>::const_iterator to,
                        char delimiter);

#endif //COMPUTERALGEBRATASK_JOIN_H
