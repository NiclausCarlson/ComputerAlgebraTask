//
// Created by Nik Carlson on 15.01.2021.
//

#include <iostream>
#include "ArithmeticOperations.h"


PolynomialTree sum(PolynomialTree left, PolynomialTree right, MonomialOrder *order, MonomialOrder *service_plex_order) {
    PolynomialTree result = new Sum(left, right);
    std::string e = result->to_str();
    Node *t = get_simplified(result, service_plex_order);
    return get_simplified(t, order);
}

PolynomialTree multiply_to_monomial(PolynomialTree polynomial, PolynomialTree monomial, MonomialOrder *order,
                                    MonomialOrder *service_plex_order) {
    std::vector<Node *> monomials;
    std::string h = polynomial->to_str();
    polynomial->get_monomials(monomials);
    for (auto &it : monomials) it = new Multiplication(it, monomial);
    Node *result = join(monomials, '+');
    std::string q = result->to_str();
    Node *t = get_simplified(result, service_plex_order);
    q = t->to_str();
    return get_simplified(t, order);
}

PolynomialTree
divide_monomials(Node *dividend, Node *divider, MonomialOrder *order, MonomialOrder *service_plex_order) {
    auto *is_constant = dynamic_cast<Constant *>(divider);
    if (is_constant != nullptr)
        return multiply_to_monomial(dividend,
                                    new Constant(1.0 / is_constant->get_value()),
                                    order,
                                    service_plex_order);
    std::vector<Node *> terms1;
    std::vector<Node *> terms2;
    dividend->get_terms(terms1);
    divider->get_terms(terms2);
    std::set<size_t> used_indexes;
    size_t idx_1 = 0, idx_2 = 0;
    ld constant_1 = 1.0, constant_2 = 1.0;
    auto *c1_checker = dynamic_cast<Constant *> (*terms1.begin());
    auto *c2_checker = dynamic_cast<Constant *> (*terms2.begin());
    if (c1_checker != nullptr) {
        used_indexes.insert(0);
        ++idx_1;
        constant_1 = c1_checker->get_value();
    }
    if (c2_checker != nullptr) {
        ++idx_2;
        constant_2 = c2_checker->get_value();
    }
    std::vector<Node *> new_terms;
    for (size_t i = idx_2; i < terms2.size(); ++i) {
        bool is_divides = false;
        auto is_var_divider = dynamic_cast<Variable *>(terms2[i]);
        auto is_exp_divider = dynamic_cast<Exponentiation *>(terms2[i]);
        for (size_t j = idx_1; j < terms1.size(); ++j) {
            auto is_var = dynamic_cast<Variable *>(terms1[j]);
            auto is_exp = dynamic_cast<Exponentiation *>(terms1[j]);
            if (is_var != nullptr && is_var_divider != nullptr) {
                if (is_var->to_str() == is_var_divider->to_str()) {
                    is_divides = true;
                    used_indexes.insert(j);
                }
            } else if (is_exp != nullptr) {
                auto var = dynamic_cast<Variable *>(is_exp->getLeftNode());
                auto number = dynamic_cast<Constant *>(is_exp->getRightNode());
                if (is_var_divider != nullptr) {
                    if (var->to_str() == is_var_divider->to_str()) {
                        is_divides = true;
                        new_terms.push_back(new Exponentiation(var, new Constant(number->get_value() - 1)));
                        used_indexes.insert(j);
                    }
                } else if (is_exp_divider != nullptr) {
                    auto dividers_var = is_exp_divider->getLeftNode();
                    auto dividers_number = dynamic_cast<Constant *>(is_exp_divider->getRightNode());
                    if (dividers_var->to_str() == var->to_str()
                        && dividers_number->get_value() <= number->get_value()) {
                        is_divides = true;
                        used_indexes.insert(j);
                        ld n = number->get_value() - dividers_number->get_value();
                        if (n != 0) new_terms.push_back(new Exponentiation(dividers_var, new Constant(n)));
                    }
                }
            }
        }
        if (!is_divides) return nullptr;
    }
    new_terms.push_back(new Constant(constant_1 / constant_2));
    for (size_t i = 0; i < terms1.size(); ++i) {
        if (used_indexes.count(i) == 0) new_terms.push_back(terms1[i]);
    }
//    Node *tree = generate_new_monomial(constant_1 / constant_2, new_terms);
    Node *tree = join(new_terms, '*');
    Node *t = get_simplified(tree, service_plex_order);
    return get_simplified(t, order);
}

std::pair<std::vector<PolynomialTree>, PolynomialTree>
divide(PolynomialTree numerator, const std::vector<PolynomialTree> &denominators, MonomialOrder *order,
       MonomialOrder *service_plex_order) {
    Node *numerator_copy = numerator->clone();
    std::vector<Node *> quotient;
    quotient.reserve(denominators.size());
    for (int i = 0; i < denominators.size(); ++i) quotient.emplace_back(nullptr);
    PolynomialTree modulo = nullptr;

    auto update_value = [&](PolynomialTree &to_update, Node *val) {
        if (to_update == nullptr) to_update = val;
        else
            to_update = sum(to_update,
                            val,
                            order,
                            service_plex_order);
    };

    size_t denominators_idx = 0;
    bool have_division;
    auto *is_zero = dynamic_cast<Constant *>(numerator_copy);
    Node *lt_1, *lt_2;
    while (is_zero == nullptr || is_zero->get_value() != 0.0) {
        have_division = false;
        denominators_idx = 0;
        lt_1 = nullptr;
        std::string q = numerator_copy->to_str();
        while (!have_division && denominators_idx < denominators.size()) {
            std::vector<Node *> monomials;
            denominators[denominators_idx]->get_monomials(monomials);
            lt_1 = get_LT(numerator_copy);
            lt_2 = get_LT(denominators[denominators_idx]);
            Node *div_res = divide_monomials(lt_1,
                                             lt_2,
                                             order,
                                             service_plex_order);
            if (div_res != nullptr) {
                std::string a = div_res->to_str();
                update_value(quotient[denominators_idx], div_res);
                numerator_copy = sum(multiply_to_monomial(denominators[denominators_idx],
                                                          new Multiplication(new Constant(-1.0), div_res),
                                                          order,
                                                          service_plex_order),
                                     numerator_copy, order, service_plex_order);
                q = numerator_copy->to_str();
                have_division = true;
            } else ++denominators_idx;
        }
        if (!have_division) {
            Node *copyed = lt_1->clone();
            update_value(modulo, copyed);
            numerator_copy = sum(multiply_to_monomial(lt_1, new Constant(-1.0), service_plex_order),
                                 numerator_copy,
                                 order,
                                 service_plex_order);
            std::string p = numerator_copy->to_str();
            std::string r = modulo->to_str();
        }
        is_zero = dynamic_cast<Constant *>(numerator_copy);
    }
    return {quotient, modulo};
}
