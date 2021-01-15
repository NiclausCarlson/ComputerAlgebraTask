//
// Created by Nik Carlson on 15.01.2021.
//

#include "ArithmeticOperations.h"

PolynomialTree sum(PolynomialTree left, PolynomialTree right, MonomialOrder *order) {
    PolynomialTree result = new Sum(left, right);
    return get_simplified(result, order);
}

PolynomialTree multiply_to_monomial(PolynomialTree polynomial, PolynomialTree monomial, MonomialOrder *order) {
    std::vector<Node *> monomials;
    polynomial->get_monomials(monomials);
    for (auto &it : monomials) it = new Multiplication(it, monomial);
    Node *result = join_monomials(monomials);
    return get_simplified(result, order);
}

PolynomialTree divide_monomials(Node *divider, Node *dividend) {

    return nullptr;
}

std::pair<PolynomialTree, PolynomialTree>
divide(PolynomialTree numerator, const std::vector<PolynomialTree> &denominators, MonomialOrder *order) {
    std::pair<PolynomialTree, PolynomialTree> quotient_and_modulo{nullptr, nullptr};

    auto update_pair = [&](PolynomialTree tree, bool projector) {
        if (projector) {
            if (quotient_and_modulo.first == nullptr) quotient_and_modulo.first = tree;
            else quotient_and_modulo.first = new Sum(quotient_and_modulo.first, tree);
        } else {
            if (quotient_and_modulo.second == nullptr) quotient_and_modulo.second = tree;
            else quotient_and_modulo.second = new Sum(quotient_and_modulo.second, tree);
        }
    };
    auto simplify_pair = [&]() {
        if (quotient_and_modulo.first != nullptr)
            quotient_and_modulo.first = get_simplified(quotient_and_modulo.first, order);
        if (quotient_and_modulo.second != nullptr)
            quotient_and_modulo.second = get_simplified(quotient_and_modulo.second, order);
    };

    size_t denominators_idx = 0;
    bool have_division = false;
    auto *is_zero = dynamic_cast<Constant *>(numerator);
    while (is_zero != nullptr && is_zero->get_value() != 0.0) {
        while (!have_division && denominators_idx < denominators.size()) {
            std::vector<Node *> monomials;
            denominators[denominators_idx]->get_monomials(monomials);
            Node *div_res = divide_monomials(denominators[denominators_idx], numerator);
            if (div_res != nullptr) {

                numerator = sum(numerator, multiply_to_monomial(
                        new Multiplication(new Constant(-1.0), div_res),
                        denominators[denominators_idx], order), order);
                have_division = true;
            } else ++denominators_idx;
        }
        if (!have_division) {

        }
        is_zero = dynamic_cast<Constant *>(numerator);
    }
    simplify_pair();
    return quotient_and_modulo;
}
