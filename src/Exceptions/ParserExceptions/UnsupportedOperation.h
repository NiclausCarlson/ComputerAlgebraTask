//
// Created by Nik Carlson on 20.12.2020.
//

#ifndef COMPUTERALGEBRATASK_UNSUPPORTEDOPERATION_H
#define COMPUTERALGEBRATASK_UNSUPPORTEDOPERATION_H


#include "ParseException.h"

class UnsupportedOperation : public ParseException {
public:
    explicit UnsupportedOperation(const std::string &, const std::string &cause = "");
};


#endif //COMPUTERALGEBRATASK_UNSUPPORTEDOPERATION_H
