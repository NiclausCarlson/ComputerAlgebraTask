//
// Created by Nik Carlson on 27.12.2020.
//

#ifndef COMPUTERALGEBRATASK_MONOMIALORDER_H
#define COMPUTERALGEBRATASK_MONOMIALORDER_H


#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"

/*
 * using for order monomial list
 */
class MonomialOrder {
public:
    virtual bool compare(PolynomialTree t1, PolynomialTree t2) = 0;
};


#endif //COMPUTERALGEBRATASK_MONOMIALORDER_H
