//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_NOTNUMBERDIVISION_H
#define COMPUTERALGEBRATASK_NOTNUMBERDIVISION_H


#include "ParseException.h"

class NotNumberDivision : public ParseException {
public:
    explicit NotNumberDivision(const std::string &);
};


#endif //COMPUTERALGEBRATASK_NOTNUMBERDIVISION_H
