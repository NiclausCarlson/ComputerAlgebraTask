//
// Created by Nik Carlson on 05.01.2021.
//

#include "Grlex.h"

Grlex::Grlex(const std::vector<std::string> &order) : MonomialOrder(order) {
}

bool Grlex::compare(PolynomialTree t1, PolynomialTree t2) {
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
    auto set_multideg = [](size_t &pos, int &grad, std::vector<Node *> &terms) {
        while (pos < terms.size()) {
            auto *t1_var = dynamic_cast<Variable *>(terms[pos]);
            auto *t1_exp = dynamic_cast<Exponentiation *>(terms[pos]);
            ++pos;
            if (t1_var != nullptr) ++grad;
            else if (t1_exp != nullptr) {
                auto *degree1 = dynamic_cast<Constant *>(t1_exp->getRightNode());
                grad += degree1->get_value();
            }
        }
    };
    set_multideg(t1_pos, grad_1, t1_terms);
    set_multideg(t2_pos, grad_2, t2_terms);

    MonomialOrder *plex = new Plex(variables);
    bool res = grad_1 > grad_2 || (grad_1 == grad_2 && plex->compare(t1, t2));
    return res;
}

Grlex::~Grlex() = default;
