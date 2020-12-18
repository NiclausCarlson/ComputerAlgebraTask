//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_WRONGTOKEN_H
#define COMPUTERALGEBRATASK_WRONGTOKEN_H


#include "ParseException.h"

class WrongToken : public ParseException {
public:
    WrongToken(const std::string &);
};


#endif //COMPUTERALGEBRATASK_WRONGTOKEN_H
