//
// Created by Nik Carlson on 18.12.2020.
//

#include "DivisionByZero.h"

DivisionByZero::DivisionByZero(const std::string &message) :
        ParseException(std::move("Division by zero: " + message)) {}
