//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_DIVISIONBYZERO_H
#define COMPUTERALGEBRATASK_DIVISIONBYZERO_H


#include "ParseException.h"

class DivisionByZero : public ParseException {
public:
    explicit DivisionByZero(const std::string &);


};


#endif //COMPUTERALGEBRATASK_DIVISIONBYZERO_H
