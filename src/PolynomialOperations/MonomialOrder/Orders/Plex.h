//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_PLEX_H
#define COMPUTERALGEBRATASK_PLEX_H


#include "../MonomialOrder.h"
#include "../../../Parser/Parser.h"
#include "Lex.h"


class Plex : virtual public MonomialOrder {
public:
    explicit Plex(const std::vector<std::string> &);

    bool compare(PolynomialTree t1, PolynomialTree t2) override;

};

#endif //COMPUTERALGEBRATASK_PLEX_H
