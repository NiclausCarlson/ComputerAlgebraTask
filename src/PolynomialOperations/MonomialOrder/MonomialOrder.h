//
// Created by Nik Carlson on 27.12.2020.
//

#ifndef COMPUTERALGEBRATASK_MONOMIALORDER_H
#define COMPUTERALGEBRATASK_MONOMIALORDER_H


#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operands/Constant.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operands/Variable.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h"
#include "../../Utils/Utils.h"

#include <utility>
#include <map>
#include <set>

/*
 * using for order monomial list
 */
class MonomialOrder {
private:

    virtual PolynomialTree generate_new_monomial(bool, ld, std::map<std::string, int> &) = 0;

public:

    virtual bool compare(PolynomialTree t1, PolynomialTree t2) = 0;

    virtual void sort_monomial(PolynomialTree monomial) = 0;

};


#endif //COMPUTERALGEBRATASK_MONOMIALORDER_H
