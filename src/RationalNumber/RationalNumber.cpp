//
// Created by Nik Carlson on 18.12.2020.
//

#include "RationalNumber.h"

RationalNumber::RationalNumber(ll numerator, ll denominator = 1) :
        numerator(numerator),
        denominator(denominator),
        string_value("(" + std::to_string(numerator) + "/"
                     + std::to_string(denominator) + ")") {}

std::string RationalNumber::to_str() const {
    return string_value;
}

