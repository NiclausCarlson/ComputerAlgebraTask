//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_GRLEX_H
#define COMPUTERALGEBRATASK_GRLEX_H


#include "../MonomialOrder.h"

class Grlex: virtual public MonomialOrder {
public:
    explicit Grlex(const std::vector <std::string> &order);

    bool compare(PolynomialTree t1, PolynomialTree t2) override;
};


#endif //COMPUTERALGEBRATASK_GRLEX_H
