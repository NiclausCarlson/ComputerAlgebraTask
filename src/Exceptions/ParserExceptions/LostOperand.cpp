//
// Created by Nik Carlson on 18.12.2020.
//

#include "LostOperand.h"

LostOperand::LostOperand(const std::string &message) :
        ParseException(std::move("Lost operand: " + message)) {}
