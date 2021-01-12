//
// Created by Nik Carlson on 13.01.2021.
//

#include "Equals.h"

PolynomialTree generate_new_monomial(ld constant, std::vector<Node *> &terms) {
    Parser parser;
    std::string new_monomial = std::to_string(constant);
    if (!terms.empty()) {
        new_monomial += '*';
        for (auto it = terms.begin(); it != terms.end() - 1; ++it) {
            new_monomial += (*it)->to_str() + '*';
        }
        new_monomial += (*(terms.end() - 1))->to_str();
    }
    return parser.parse(new_monomial);
}


bool equals(std::vector<PolynomialTree> &t1_terms, std::vector<PolynomialTree> &t2_terms) {
    size_t t1_pos = 0, t2_pos = 0;
    for (size_t i = 0; i < std::min(t1_terms.size(), t2_terms.size()); ++i) {
        std::string t1_instance = get_instance(t1_terms[i]);
        std::string t2_instance = get_instance(t2_terms[i]);
        if (t1_instance == "Constant") ++t1_pos;
        if (t2_instance == "Constant") ++t2_pos;
    }
    //if (t1_pos >= t1_terms.size() || t2_pos >= t2_terms.size()) return false;
    if (t1_terms.size() - t1_pos != t2_terms.size() - t2_pos) return false;

    while (t1_pos < t1_terms.size() && t2_pos < t2_terms.size()) {
        std::string a = t1_terms[t1_pos]->to_str();
        std::string b = t2_terms[t2_pos]->to_str();
        if (t1_terms[t1_pos]->to_str() != t2_terms[t2_pos]->to_str()) return false;
        ++t1_pos;
        ++t2_pos;
    }
    return true;
}

// Working for two monomials
PolynomialTree sumIfEquals(PolynomialTree t1, PolynomialTree t2) {
    std::vector<PolynomialTree> t1_terms, t2_terms;
    t1->get_terms(t1_terms);
    t2->get_terms(t2_terms);

    if (equals(t1_terms, t2_terms)) {
        size_t t1_pos = 0, t2_pos = 0;
        auto *const1 = dynamic_cast<Constant *>(t1_terms[t1_pos]);
        auto *const2 = dynamic_cast<Constant *>(t2_terms[t2_pos]);
        if (const1 == nullptr) const1 = new Constant(1.0);
        else ++t1_pos;

        if (const2 == nullptr) const2 = new Constant(1.0);
        else ++t2_pos;

        ld new_const = const1->get_value() + const2->get_value();
        if (new_const == 0.0) return new Constant(0.0);
        else {
            std::vector<Node *> new_monomial_vector;
            size_t iter = std::min(t1_pos, t2_pos);
            while (iter < t2_terms.size()) {
                new_monomial_vector.push_back(t2_terms[iter]);
                ++iter;
            }
            return generate_new_monomial(new_const, new_monomial_vector);
        }
    } else return nullptr;
}