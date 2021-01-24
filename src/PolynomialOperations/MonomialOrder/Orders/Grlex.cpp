//
// Created by Nik Carlson on 05.01.2021.
//

#include "Grlex.h"

Grlex::Grlex(const std::vector<std::string> &order) : MonomialOrder(order) {
}

bool Grlex::compare(PolynomialTree t1, PolynomialTree t2) {
    MonomialOrder *plex = new Plex(variables);
    std::vector<Node *> t1_terms;
    std::vector<Node *> t2_terms;
    std::string q1 = t1->to_str();
    std::string q2 = t2->to_str();
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
    while (t1_pos < t1_terms.size()) {
        auto *t1_var = dynamic_cast<Variable *>(t1_terms[t1_pos]);
        auto *t1_exp = dynamic_cast<Exponentiation *>(t1_terms[t1_pos]);
        ++t1_pos;
        if (t1_var != nullptr) ++grad_1;
        else if (t1_exp != nullptr) {
            auto *degree1 = dynamic_cast<Constant *>(t1_exp->getRightNode());
            grad_1 += degree1->get_value();
        }
    }
    while (t2_pos < t2_terms.size()) {
        auto *t2_var = dynamic_cast<Variable *>(t2_terms[t2_pos]);
        auto *t2_exp = dynamic_cast<Exponentiation *>(t2_terms[t2_pos]);
        ++t2_pos;
        if (t2_var != nullptr) ++grad_2;
        else if (t2_exp != nullptr) {
            auto *degree2 = dynamic_cast<Constant *>(t2_exp->getRightNode());
            grad_2 += degree2->get_value();
        }
    }

    return grad_1 > grad_2 || (grad_1 == grad_2 && plex->compare(t1, t2));
}

Grlex::~Grlex() = default;
