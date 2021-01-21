//
// Created by Nik Carlson on 13.01.2021.
//
#include "Simplify.h"


//This method returns simplified polynomial
PolynomialTree get_simplified(PolynomialTree &t, MonomialOrder *order) {
    std::vector<Node *> monomials;
    t->get_monomials(monomials);
    for (auto &i: monomials) order->sort_monomial(i);
    for (auto &i: monomials) {
        std::string q = i->to_str();
    }
    auto comp = [&order](PolynomialTree t1, PolynomialTree t2) { return order->compare(t1, t2); };
    std::sort(monomials.begin(), monomials.end(), comp);

    std::vector<Node *> new_polynomial;
    Node *node = monomials[0];

    if (monomials.size() == 1) new_polynomial.push_back(node);
    else {
        Constant *c;
        for (auto it = monomials.begin() + 1; it != monomials.end(); ++it) {
            Node *joined_node = sumIfEquals(node, *it);
            if (joined_node != nullptr) {
                delete node;
                node = joined_node;
            } else {
                c = dynamic_cast<Constant *>(node);
                if (c == nullptr || c->get_value() != 0) new_polynomial.push_back(node);
                node = *it;
            }
        }
        c = dynamic_cast<Constant *>(node);
        if (c == nullptr || c->get_value() != 0) new_polynomial.push_back(node);
    }
    return join(new_polynomial, '+');
}