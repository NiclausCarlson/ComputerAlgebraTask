//
// Created by Nik Carlson on 27.12.2020.
//

#ifndef COMPUTERALGEBRATASK_LEX_H
#define COMPUTERALGEBRATASK_LEX_H


#include "../MonomialOrder.h"
#include "../../../Parser/Parser.h"


class Lex : virtual public MonomialOrder {
private:
    //list of variables for ordering
    std::vector<std::string> variables;

    static void update_exp(PolynomialTree val, std::map<std::string, int> &variablesMap);

    static void update_variable(PolynomialTree val, std::map<std::string, int> &variablesMap);

    PolynomialTree generate_new_monomial(bool, ld, std::map<std::string, int> &) override;

    Parser parser;
public:
    explicit Lex(const std::vector<std::string>&);

    bool compare(PolynomialTree t1, PolynomialTree t2) override;

    //method which order monomial
    void sort_monomial(PolynomialTree& monomial) override;

};


#endif //COMPUTERALGEBRATASK_LEX_H
