//
// Created by Nik Carlson on 18.12.2020.
//

#include "NotNumberDivision.h"

NotNumberDivision::NotNumberDivision(const std::string &message) :
        ParseException(std::move("Not numbers division: " + message)) {}
