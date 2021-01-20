//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_FGLM_H
#define COMPUTERALGEBRATASK_FGLM_H

#include <set>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include "../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../PolynomialOperations/MonomialOrder/MonomialOrder.h"
#include "../PolynomialOperations/Simplify/Simplify.h"
#include "../PolynomialOperations/ArithmeticOperations/ArithmeticOperations.h"

class FGLM {
private:

    std::vector<Variable *> free_variables;// Variables looks like @_idx
    std::vector<PolynomialTree> old_basis;
    std::vector<PolynomialTree> new_basis;
    MonomialOrder *old_order;
    MonomialOrder *new_order;

    std::vector<Variable *> variables_list;

    bool has_linear_relation(Node *v, std::vector<std::pair<Node *, Node *>> const &MBasis, Node *&relation);

    PolynomialTree get_normal_form(
            PolynomialTree polynomial); // returns normal form of polynomial with respect to old_basis and old order

    bool is_product(Node *monom, std::vector<Node *> const &staircase);

    void insert_nexts(Node *v, std::set<Node *> &set_of_nexts);

public:
    FGLM(std::vector<PolynomialTree> &old_basis,
         MonomialOrder *old_order,
         MonomialOrder *new_order,
         std::vector<Variable *> &variables_list);

    std::vector<PolynomialTree> transform();

    std::string get_in_maple_dsl();
};


#endif //COMPUTERALGEBRATASK_FGLM_H
