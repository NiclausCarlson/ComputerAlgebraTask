//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_FGLM_H
#define COMPUTERALGEBRATASK_FGLM_H

#include "../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../PolynomialOperations/MonomialOrder/MonomialOrder.h"

class FGLM {
private:
    std::vector<PolynomialTree> old_basis;
    std::vector<PolynomialTree> new_basis;
    MonomialOrder *old_order;
    MonomialOrder *new_order;

    bool has_linear_relation();

    PolynomialTree get_normal_form(PolynomialTree polynomial); // returns normal form of polynomial with respect to old_basis and old order
public:
    FGLM(std::vector<PolynomialTree> &old_basis, MonomialOrder *old_order, MonomialOrder *new_order);

    std::vector<PolynomialTree> transform();

    std::string get_in_maple_dsl();
};


#endif //COMPUTERALGEBRATASK_FGLM_H
