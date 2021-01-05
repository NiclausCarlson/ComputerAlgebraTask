//
// Created by Nik Carlson on 27.12.2020.
//

#include "Lex.h"
#include "../../../Exceptions/OrderExceptions/UnexpectedOperationException.h"

Lex::Lex(const std::vector<std::string> &order) {
    size_t len = order.size() + 1;
    for (const auto &i : order) {
        variables.push_back(i);
        variables_order[i] = len;
        --len;
    }
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
        if (t1_instance == "Constant" || t1_instance == "UnaryMinus") ++t1_pos;
        if (t2_instance == "Constant" || t2_instance == "UnaryMinus") ++t2_pos;
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

void Lex::sort_monomial(PolynomialTree &monomial) {
    std::string instance = get_instance(monomial);
    if (instance == "Constant" || instance == "Variable" || instance == "Exponentiation") {
        //already ordered
    } else if (instance == "Multiplication") {
        auto *monom = dynamic_cast<Multiplication *>(monomial);
        std::vector<Node *> terms;
        monom->get_terms(terms);

        // there can be only Constants, Powers, Variables and Unary Minuses
        bool minus = false;//true - monomial have '-'
        ld constant = 1.0;
        std::map<std::string, int> variablesMap; // there <variable, degree>
        for (const auto &k: variables) variablesMap[k] = 0;
        for (auto i : terms) {
            std::string id = get_instance(i);
            if (id == "UnaryMinus") {
                minus ^= true;
                auto *val = dynamic_cast<UnaryMinus *>(i)->getOperand();
                std::string id_name = get_instance(val);
                if (id_name == "Constant") {
                    constant *= dynamic_cast<Constant *>(val)->get_value();
                } else if (id_name == "Exponentiation") {
                    update_exp(val, variablesMap);
                } else if (id_name == "Variable") {
                    update_variable(val, variablesMap);
                }
            } else if (id == "Exponentiation") {
                update_exp(i, variablesMap);
            } else if (id == "Constant") {
                constant *= dynamic_cast<Constant *>(i)->get_value();
            } else if (id == "Variable") {
                update_variable(i, variablesMap);
            }
        }
        delete monomial;
        monomial = generate_new_monomial(minus, constant, variablesMap);
        return;
    }
    throw UnexpectedOperationException(instance);
}

void Lex::update_exp(PolynomialTree val, std::map<std::string, int> &variablesMap) {
    auto *exp = dynamic_cast<Exponentiation *>(val);
    std::string variable = dynamic_cast<Variable *>(exp->getLeftNode())->get_value();
    int degree = (int) dynamic_cast<Constant *>(exp->getRightNode())->get_value();
    variablesMap[variable] += degree;
}

void Lex::update_variable(PolynomialTree val, std::map<std::string, int> &variablesMap) {
    std::string variable = dynamic_cast<Variable *>(val)->get_value();
    variablesMap[variable] += 1;
}

PolynomialTree Lex::generate_new_monomial(bool minus, ld number, std::map<std::string, int> &terms) {
    std::vector<std::string> ordered_terms;
    if (minus) ordered_terms.emplace_back("-");
    if (number != 1.0) ordered_terms.push_back(std::to_string(number));
    for (const auto &v: variables) {
        if (terms[v] > 1) ordered_terms.emplace_back(v + '^' + std::to_string(terms[v]));
        else if (terms[v] == 1) ordered_terms.emplace_back(v);
    }
    std::string str;
    for (int i = 0; i < ordered_terms.size(); ++i) {
        if (i < ordered_terms.size() - 1 && ordered_terms[i] != "-") str += ordered_terms[i] + '*';
        else str += ordered_terms[i];
    }
    return parser.parse(str);
}
