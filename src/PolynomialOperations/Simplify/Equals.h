//
// Created by Nik Carlson on 07.01.2021.
//

#include <algorithm>
#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../../Utils/Utils.h"
#include "../MonomialOrder/MonomialOrder.h"

#ifndef COMPUTERALGEBRATASK_EQUALS_H
#define COMPUTERALGEBRATASK_EQUALS_H

//Warning: This methods can only compare monomials with the same binomial ordering;
// otherwise, the behavior of the method is undefined.

PolynomialTree generate_new_monomial(ld constant, std::vector<Node *> &terms);


bool equals(std::vector<PolynomialTree> &t1_terms, std::vector<PolynomialTree> &t2_terms);

// Working for two monomials
PolynomialTree sumIfEquals(PolynomialTree t1, PolynomialTree t2);

#endif