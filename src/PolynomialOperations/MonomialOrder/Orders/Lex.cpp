//
// Created by Nik Carlson on 27.12.2020.
//

#include "Lex.h"

Lex::Lex(const std::vector<std::string> &order) : MonomialOrder(order) {
}

bool Lex::compare(PolynomialTree t1, PolynomialTree t2) {

    std::vector<Node *> t1_terms;
    std::vector<Node *> t2_terms;

    t1->get_terms(t1_terms);
    t2->get_terms(t2_terms);

    size_t t1_pos = 0, t2_pos = 0;
    for (size_t i = 0; i < __min(t1_terms.size(), t2_terms.size()); ++i) {
        std::string t1_instance = get_instance(t1_terms[i]);
        std::string t2_instance = get_instance(t2_terms[i]);
        if (t1_instance == "Constant") ++t1_pos;
        if (t2_instance == "Constant") ++t2_pos;
    }
    //here can be only Variables or Exponentiation
    do {
        if ((t1_pos >= t1_terms.size() && t2_pos >= t2_terms.size()) ||
            (t1_pos >= t1_terms.size() && t2_pos < t2_terms.size()))
            return false;
        else if (t1_pos < t1_terms.size() && t2_pos >= t2_terms.size()) return true;

        auto *t1_var = dynamic_cast<Variable *>(t1_terms[t1_pos]);
        auto *t2_var = dynamic_cast<Variable *>(t2_terms[t2_pos]);
        auto *t1_exp = dynamic_cast<Exponentiation *>(t1_terms[t1_pos]);
        auto *t2_exp = dynamic_cast<Exponentiation *>(t2_terms[t2_pos]);
        ++t1_pos;
        ++t2_pos;

        if (t1_var != nullptr && t2_var != nullptr) {
            if (variables_order[t1_var->get_value()] > variables_order[t2_var->get_value()]) return true;
            else if (variables_order[t1_var->get_value()] < variables_order[t2_var->get_value()]) return false;
        } else if (t1_var != nullptr && t2_exp != nullptr) {
            auto *t22_var = dynamic_cast<Variable *>(t2_exp->getLeftNode());
            if (variables_order[t1_var->get_value()] > variables_order[t22_var->get_value()]) return true;
            else if (variables_order[t1_var->get_value()] < variables_order[t22_var->get_value()]) return false;
        } else if (t1_exp != nullptr && t2_var != nullptr) {
            auto *t12_var = dynamic_cast<Variable *>(t1_exp->getLeftNode());
            if (variables_order[t12_var->get_value()] > variables_order[t2_var->get_value()]) return true;
            else if (variables_order[t12_var->get_value()] < variables_order[t2_var->get_value()]) return false;
        } else if (t1_exp != nullptr && t2_exp != nullptr) {
            auto *t12_var = dynamic_cast<Variable *>(t1_exp->getLeftNode());
            auto *t22_var = dynamic_cast<Variable *>(t2_exp->getLeftNode());
            if (variables_order[t12_var->get_value()] > variables_order[t22_var->get_value()]) return true;
            else if (variables_order[t12_var->get_value()] < variables_order[t22_var->get_value()])return false;
        }
    } while (t1_pos < t1_terms.size() && t2_pos < t2_terms.size());

    return false;
}

