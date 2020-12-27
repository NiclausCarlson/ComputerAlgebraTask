//
// Created by Nik Carlson on 27.12.2020.
//

#ifndef COMPUTERALGEBRATASK_LEX_H
#define COMPUTERALGEBRATASK_LEX_H


#include <set>
#include "../MonomialOrder.h"

class Lex : virtual public MonomialOrder {
private:
    std::set<std::string> variables;
public:
    Lex(const std::vector<std::string>&);

    bool compare(PolynomialTree t1, PolynomialTree t2) override;
};


#endif //COMPUTERALGEBRATASK_LEX_H
