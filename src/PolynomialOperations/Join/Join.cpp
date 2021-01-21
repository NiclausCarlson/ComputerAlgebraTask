//
// Created by Nik Carlson on 15.01.2021.
//

#include "Join.h"

PolynomialTree recursive(std::vector<Node *>::iterator from,
                         std::vector<Node *>::iterator to,
                         char delimiter) {
    if (from == to - 1) return *from;
    else {
        if (delimiter == '+') return new Sum(*from, recursive(from + 1, to, delimiter));
        else return new Multiplication(*from, recursive(from + 1, to, delimiter));
    }
}

PolynomialTree join(std::vector<Node *> &monomials, char delimiter) {
    if (monomials.empty()) return new Constant(0.0);
    if (monomials.size() == 1) return *monomials.begin();
    AbstractBinaryOperation *joined;
    if (delimiter == '+')
        joined = new Sum(*monomials.begin(), nullptr);
    else
        joined = new Multiplication(*monomials.begin(), nullptr);
    std::string q = (*monomials.begin())->to_str();
    joined->set_right_node(recursive(monomials.begin() + 1, monomials.end(), delimiter));
    return joined;
}