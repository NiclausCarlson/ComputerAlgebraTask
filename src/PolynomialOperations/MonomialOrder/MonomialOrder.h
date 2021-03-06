//
// Created by Nik Carlson on 27.12.2020.
//

#ifndef COMPUTERALGEBRATASK_MONOMIALORDER_H
#define COMPUTERALGEBRATASK_MONOMIALORDER_H


#include "../../Exceptions/OrderExceptions/UnexpectedOperationException.h"
#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operands/Constant.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operands/Variable.h"
#include "../../PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h"
#include "../../Utils/Utils.h"
#include "../../Parser/Parser.h"
#include "../Join/Join.h"

#include <utility>
#include <map>
#include <set>
#include <algorithm>

/*
 * using for order monomial list
 */
class MonomialOrder {
private:
    PolynomialTree generate_new_monomial(bool, ld, std::map<std::string, int> &);

    Parser parser;
protected:
    bool simplify_monomial(bool &minus,
                           ld &constant,
                           std::map<std::string, int> &variablesMap,
                           PolynomialTree monomial);

    std::vector<std::string> variables;
    std::vector<std::string> other_variables;
    std::map<std::string, size_t> variables_order;
    size_t variable_quantity;
public:

    explicit MonomialOrder(const std::vector<std::string> &order);

    //return true, if t1 > t2
    virtual bool compare(PolynomialTree t1, PolynomialTree t2) = 0;

    void sort_monomial(PolynomialTree &monomial);

    void add_other_variable(const std::string &v);

    std::vector<std::string> get_variables() const ;

    virtual ~MonomialOrder();
};


#endif //COMPUTERALGEBRATASK_MONOMIALORDER_H
