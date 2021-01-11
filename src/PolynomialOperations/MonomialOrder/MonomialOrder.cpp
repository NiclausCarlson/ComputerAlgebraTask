//
// Created by Nik Carlson on 06.01.2021.
//

#include "MonomialOrder.h"

MonomialOrder::MonomialOrder(const std::vector<std::string> &order) {
    size_t len = order.size() + 1;
    for (const auto &i : order) {
        variables.push_back(i);
        variables_order[i] = len;
        --len;
    }
}

bool MonomialOrder::simplify_monomial(bool &minus,
                                      ld &constant,
                                      std::map<std::string, int> &variablesMap,
                                      PolynomialTree monomial) {

    std::string instance = get_instance(monomial);

    auto update_exp = [&](PolynomialTree val, std::map<std::string, int> &variablesMap) {
        auto *exp = dynamic_cast<Exponentiation *>(val);
        std::string variable = dynamic_cast<Variable *>(exp->getLeftNode())->get_value();
        int degree = (int) dynamic_cast<Constant *>(exp->getRightNode())->get_value();
        variablesMap[variable] += degree;
    };

    auto update_variable = [&](PolynomialTree val, std::map<std::string, int> &variablesMap) {
        std::string variable = dynamic_cast<Variable *>(val)->get_value();
        variablesMap[variable] += 1;
    };

    if (instance == "Constant" || instance == "Variable" || instance == "Exponentiation") {
        //already ordered
        return false;
    } else if (instance == "Multiplication") {
        auto *monom = dynamic_cast<Multiplication *>(monomial);
        std::vector<Node *> terms;
        monom->get_terms(terms);
        // there can be only Constants, Powers, Variables and Unary Minuses
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
        return true;
    }
    throw UnexpectedOperationException(instance);
}

void MonomialOrder::sort_monomial(PolynomialTree &monomial) {
    bool minus = false;//true - monomial have '-'
    ld constant = 1.0;
    std::map<std::string, int> variablesMap; // there <variable, degree>
    if (simplify_monomial(minus, constant, variablesMap, monomial)) {
        delete monomial;
        monomial = generate_new_monomial(minus, constant, variablesMap);
    }
}

PolynomialTree MonomialOrder::generate_new_monomial(bool minus, ld number, std::map<std::string, int> &terms) {
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

