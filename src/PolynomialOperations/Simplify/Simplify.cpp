//
// Created by Nik Carlson on 05.01.2021.
//

#include<algorithm>

#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../MonomialOrder/MonomialOrder.h"

void simplify(PolynomialTree &t, MonomialOrder *order) {
    std::vector<Node *> monomials;
    t->get_monomials(monomials);
    for (auto &i: monomials) {
        order->sort_monomial(i);
    }
    auto comp = [&](PolynomialTree t1, PolynomialTree t2) { return order->compare(t1, t2); };
    std::sort(monomials.begin(), monomials.end(), comp);
    ld constant = 0.0;
    std::vector<Node *> new_polynomial;
    size_t pos = 0;
    for (auto i: monomials) {
        auto *tmp = dynamic_cast<Constant * >(i);
        if (tmp != nullptr) {
            constant += tmp->get_value();
        } else {
            //видимо, стоит действовать по аналогии с sort_monomial
        }
    }
}