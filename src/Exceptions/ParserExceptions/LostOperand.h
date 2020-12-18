//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_LOSTOPERAND_H
#define COMPUTERALGEBRATASK_LOSTOPERAND_H


#include "ParseException.h"

class LostOperand : public ParseException {
public:
    explicit LostOperand(const std::string&);
};


#endif //COMPUTERALGEBRATASK_LOSTOPERAND_H
