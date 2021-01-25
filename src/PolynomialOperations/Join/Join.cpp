//
// Created by Nik Carlson on 15.01.2021.
//

#include "Join.h"

PolynomialTree recursive(std::vector<Node *>::const_iterator from,
                         std::vector<Node *>::const_iterator to,
                         char delimiter) {
    if (from == to - 1) return (*from)->clone();
    else {
        if (delimiter == '+') return new Sum((*from)->clone(), recursive(from + 1, to, delimiter));
        else return new Multiplication((*from)->clone(), recursive(from + 1, to, delimiter));
    }
}

PolynomialTree join(std::vector<Node *> &monomials, char delimiter) {
    if (monomials.empty()) return new Constant(0.0);
    if (monomials.size() == 1) return (*monomials.begin())->clone();
    AbstractBinaryOperation *joined;
    if (delimiter == '+')
        joined = new Sum((*monomials.begin())->clone(), nullptr);
    else
        joined = new Multiplication((*monomials.begin())->clone(), nullptr);
    joined->set_right_node(recursive(monomials.cbegin() + 1, monomials.cend(), delimiter));
    return joined;
}

PolynomialTree join(std::vector<Node *>::const_iterator from,
                    std::vector<Node *>::const_iterator to,
                    char delimiter){
    if(from == to) return nullptr;
    if(from + 1 == to) return (*from)->clone();
    AbstractBinaryOperation *joined;
    if (delimiter == '+')
        joined = new Sum((*from)->clone(), nullptr);
    else
        joined = new Multiplication((*from)->clone(), nullptr);
    joined->set_right_node(recursive(from + 1, to, delimiter));
    return joined;
}
