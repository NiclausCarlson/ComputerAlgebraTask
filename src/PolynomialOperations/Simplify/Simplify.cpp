//
// Created by Nik Carlson on 13.01.2021.
//
#include "Simplify.h"

PolynomialTree recursive(std::vector<Node *>::iterator from,
                         std::vector<Node *>::iterator to) {
    if (from == to - 1) return *from;
    else return new Sum(*from, recursive(from + 1, to));
}

PolynomialTree join_monomials(std::vector<Node *> &monomials) {
    if (monomials.empty()) return new Constant(0.0);
    if (monomials.size() == 1) return *monomials.begin();
    Sum *joined = new Sum(*monomials.begin(), nullptr);
    std::string q = (*monomials.begin())->to_str();
    joined->set_right_node(recursive(monomials.begin() + 1, monomials.end()));
    return joined;
}

//This method returns simplified polynomial
PolynomialTree get_simplified(PolynomialTree &t, MonomialOrder *order) {
    std::vector<Node *> monomials;
    t->get_monomials(monomials);
    for (auto &i: monomials) order->sort_monomial(i);
    auto comp = [&](PolynomialTree t1, PolynomialTree t2) { return order->compare(t1, t2); };
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
    return join_monomials(new_polynomial);
}