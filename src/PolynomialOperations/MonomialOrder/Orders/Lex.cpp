//
// Created by Nik Carlson on 27.12.2020.
//

#include "Lex.h"

#include <utility>

Lex::Lex(const std::vector<std::string> &order) {
    for (const auto& i : order) variables.push_back(i);
}

bool Lex::compare(PolynomialTree t1, PolynomialTree t2) {

    return false;
}

void Lex::sort_monomial(PolynomialTree monomial) {
    auto *monom = dynamic_cast<Multiplication *>(monomial);
    //TODO: не правда, ещё может быть Constant, Variables и UnaryMinus
    if (monom == nullptr) {
        //TODO: make exceptions for this way
        monomial = nullptr;
        return;
    }

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
        } else {
            //TODO:: throw exception
        }
    }

    //TODO: удалить старый моном, сконструировать новый
    PolynomialTree new_term = generate_new_monomial(minus, constant, variablesMap);
    std::string a = new_term->to_str();
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
