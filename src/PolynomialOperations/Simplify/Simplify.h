//
// Created by Nik Carlson on 05.01.2021.
//
#ifndef COMPUTERALGEBRATASK_SIMPLIFY_H
#define COMPUTERALGEBRATASK_SIMPLIFY_H

#include <algorithm>

#include "../MonomialslJoiner/Join.h"
#include "Equals.h"

//This method returns simplified polynomial
PolynomialTree get_simplified(PolynomialTree &t, MonomialOrder *order);

#endif //COMPUTERALGEBRATASK_SIMPLIFY_H
