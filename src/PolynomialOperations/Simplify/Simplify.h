//
// Created by Nik Carlson on 05.01.2021.
//
#ifndef COMPUTERALGEBRATASK_SIMPLIFY_H
#define COMPUTERALGEBRATASK_SIMPLIFY_H

#include <algorithm>

#include "../../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../MonomialOrder/MonomialOrder.h"
#include "Equals.h"

PolynomialTree recursive(std::vector<Node *>::iterator from,
                         std::vector<Node *>::iterator to,
                         Sum *joined) {
    if (from == to - 1) return joined;
    joined->set_right_node(new Sum(*from, recursive(from + 1, to, joined)));
    return joined;
}

PolynomialTree join_monomials(std::vector<Node *> &monomials) {
    if (monomials.empty()) return new Constant(0.0);
    if (monomials.size() == 1) return *monomials.begin();
    Sum *joined = new Sum(*monomials.begin(), nullptr);
    recursive(monomials.begin() + 1, monomials.end(), joined);
    return joined;
}

//This method returns vector of simplified polynomial
PolynomialTree get_simplified(PolynomialTree &t, MonomialOrder *order) {
    std::vector<Node *> monomials;
    t->get_monomials(monomials);
    for (auto &i: monomials) {
        order->sort_monomial(i);
    }
    auto comp = [&](PolynomialTree t1, PolynomialTree t2) { return order->compare(t1, t2); };
    std::sort(monomials.begin(), monomials.end(), comp);
    std::vector<Node *> new_polynomial;

    Node *node = monomials[0];
    auto *sum = dynamic_cast<Constant *>(node);
    if (monomials.size() == 1) new_polynomial.push_back(node);
    else {
        for (auto it = monomials.begin() + 1; it != monomials.end(); ++it) {
            Node *joined_node = sumIfEquals(node, *it);
            if (joined_node != nullptr) {
                delete node;
                node = joined_node;
            } else {
                delete joined_node;
                new_polynomial.push_back(node);
            }
        }
    }
    new_polynomial.push_back(node);
    if (sum != nullptr && sum->get_value() != 0.0) new_polynomial.push_back(sum);
    return join_monomials(new_polynomial);
}

#endif //COMPUTERALGEBRATASK_SIMPLIFY_H
