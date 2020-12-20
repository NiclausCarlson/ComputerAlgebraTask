//
// Created by Nik Carlson on 20.12.2020.
//

#ifndef COMPUTERALGEBRATASK_INVALIDARGUMENT_H
#define COMPUTERALGEBRATASK_INVALIDARGUMENT_H


#include "ParseException.h"

class InvalidArgument : public ParseException {
public:
    explicit InvalidArgument(const std::string &);
};


#endif //COMPUTERALGEBRATASK_INVALIDARGUMENT_H
