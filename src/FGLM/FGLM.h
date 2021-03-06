//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_FGLM_H
#define COMPUTERALGEBRATASK_FGLM_H

#include <set>
#include <boost/numeric/mtl/mtl.hpp>

#include "../PolynomialOperations/ArithmeticOperations/ArithmeticOperations.h"
#include "../PolynomialOperations/Simplify/Equals.h"

class FGLM {
private:
    const size_t FREE_VARIABLES_QUANTITY = 300;
    std::vector<Variable *> free_variables; //@_idx
    std::vector<PolynomialTree> old_basis;
    std::vector<PolynomialTree> new_basis;
    MonomialOrder *old_order;
    MonomialOrder *new_order;
    MonomialOrder *service_plex_order;
    MonomialOrder *linear_order;
    std::vector<Variable *> variables_list;

    bool get_linear_relation(Node *v, std::vector<std::pair<Node *, Node *>> const &MBasis, Node *&relation);

    // returns normal form of polynomial with respect to old_basis and old order
    PolynomialTree get_normal_form(PolynomialTree polynomial);

    bool is_product(Node *monom, std::vector<Node *> const &staircase);

public:
    FGLM(std::vector<PolynomialTree> &old_basis,
         MonomialOrder *old_order,
         MonomialOrder *new_order,
         std::vector<Variable *> variables_list);

    std::vector<PolynomialTree> transform();

    std::string get_in_maple_dsl();
};


#endif //COMPUTERALGEBRATASK_FGLM_H
