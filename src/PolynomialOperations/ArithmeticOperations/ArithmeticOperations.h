//
// Created by Nik Carlson on 15.01.2021.
//

#ifndef COMPUTERALGEBRATASK_ARITHMETICOPERATIONS_H
#define COMPUTERALGEBRATASK_ARITHMETICOPERATIONS_H

#include <utility>
#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../MonomialOrder/MonomialOrder.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/Sum.h"
#include "../../PolynomialOperations/Simplify/Simplify.h"
#include "../MonomialslJoiner/Join.h"

PolynomialTree sum(PolynomialTree left, PolynomialTree right, MonomialOrder *order);

PolynomialTree multiply_to_monomial(PolynomialTree polynomial, PolynomialTree monomial, MonomialOrder *order);

PolynomialTree divide_monomials(Node *divider, Node *dividend);

std::pair<PolynomialTree, PolynomialTree> divide(PolynomialTree, const std::vector<PolynomialTree> &);

#endif //COMPUTERALGEBRATASK_ARITHMETICOPERATIONS_H