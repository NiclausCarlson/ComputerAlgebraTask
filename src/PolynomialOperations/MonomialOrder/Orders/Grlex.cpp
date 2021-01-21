//
// Created by Nik Carlson on 05.01.2021.
//

#include "Grlex.h"

Grlex::Grlex(const std::vector<std::string> &order) : MonomialOrder(order) {
}

bool Grlex::compare(PolynomialTree t1, PolynomialTree t2) {

    std::vector<Node *> t1_terms;
    std::vector<Node *> t2_terms;

    t1->get_terms(t1_terms);
    t2->get_terms(t2_terms);

    size_t t1_pos = 0, t2_pos = 0;
    for (size_t i = 0; i < std::min(t1_terms.size(), t2_terms.size()); ++i) {
        std::string t1_instance = get_instance(t1_terms[i]);
        std::string t2_instance = get_instance(t2_terms[i]);
        if (t1_instance == "Constant") ++t1_pos;
        if (t2_instance == "Constant") ++t2_pos;
    }
    if (t1_pos == t1_terms.size() && t2_pos <= t2_terms.size()) return false;
    if (t1_pos < t1_terms.size() && t2_pos == t2_terms.size()) return true;
    //here can be only Variables or Exponentiation
    int grad_1 = 0, grad_2 = 0;
    bool is_lex_ordered = true;
    while (t1_pos < t1_terms.size() && t2_pos < t2_terms.size()) {
        auto *t1_var = dynamic_cast<Variable *>(t1_terms[t1_pos]);
        auto *t2_var = dynamic_cast<Variable *>(t2_terms[t2_pos]);
        auto *t1_exp = dynamic_cast<Exponentiation *>(t1_terms[t1_pos]);
        auto *t2_exp = dynamic_cast<Exponentiation *>(t2_terms[t2_pos]);
        ++t1_pos;
        ++t2_pos;

        if (t1_var != nullptr && t2_var != nullptr) {
            ++grad_1;
            ++grad_2;
            if (variables_order[t1_var->get_value()] < variables_order[t2_var->get_value()])
                is_lex_ordered ^= false;
        } else if (t1_var != nullptr && t2_exp != nullptr) {
            auto *t22_var = dynamic_cast<Variable *>(t2_exp->getLeftNode());
            auto *degree = dynamic_cast<Constant *>(t2_exp->getRightNode());
            ++grad_1;
            grad_2 += degree->get_value();
            if (variables_order[t1_var->get_value()] < variables_order[t22_var->get_value()])
                is_lex_ordered ^= false;
        } else if (t1_exp != nullptr && t2_var != nullptr) {
            auto *t12_var = dynamic_cast<Variable *>(t1_exp->getLeftNode());
            auto *degree = dynamic_cast<Constant *>(t1_exp->getRightNode());
            grad_1 += degree->get_value();
            ++grad_2;
            if (variables_order[t12_var->get_value()] < variables_order[t2_var->get_value()])
                is_lex_ordered ^= false;
        } else if (t1_exp != nullptr && t2_exp != nullptr) {
            auto *t12_var = dynamic_cast<Variable *>(t1_exp->getLeftNode());
            auto *t22_var = dynamic_cast<Variable *>(t2_exp->getLeftNode());
            auto *degree1 = dynamic_cast<Constant *>(t1_exp->getRightNode());
            auto *degree2 = dynamic_cast<Constant *>(t2_exp->getRightNode());
            grad_1 += degree1->get_value();
            grad_2 += degree2->get_value();
            if (variables_order[t12_var->get_value()] < variables_order[t22_var->get_value()])
                is_lex_ordered ^= false;
        }
    }

    if (grad_1 > grad_2) return true;
    else return t1_pos >= t1_terms.size() && t2_pos >= t2_terms.size() && is_lex_ordered;
}

Grlex::~Grlex() = default;
