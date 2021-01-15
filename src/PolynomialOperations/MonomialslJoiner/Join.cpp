//
// Created by Nik Carlson on 15.01.2021.
//

#include "Join.h"

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