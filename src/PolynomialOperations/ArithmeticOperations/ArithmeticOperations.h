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
#include "../Join/Join.h"
#include "../../PolynomialTree/MonomialThings/MonomialThings.h"
#include "../MonomialOrder/Orders/Lex.h"
#include "../MonomialOrder/Orders/Plex.h"


PolynomialTree sum(PolynomialTree left, PolynomialTree right, MonomialOrder *order,
                   MonomialOrder *service_plex_order = new Plex({"x", "y", "z"}));

PolynomialTree multiply_to_monomial(PolynomialTree polynomial, PolynomialTree monomial, MonomialOrder *order,
                                    MonomialOrder *service_plex_order = new Plex({"x", "y", "z"}));

PolynomialTree divide_monomials(Node *divider, Node *dividend, MonomialOrder *order,
                                MonomialOrder *service_plex_order = new Plex({"x", "y", "z"}));

std::pair<std::vector<PolynomialTree>, PolynomialTree>
divide(PolynomialTree, const std::vector<PolynomialTree> &, MonomialOrder *,
       MonomialOrder *service_plex_order = new Plex({"x", "y", "z"}));

#endif //COMPUTERALGEBRATASK_ARITHMETICOPERATIONS_H
