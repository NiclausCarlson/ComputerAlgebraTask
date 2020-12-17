//
// Created by Nik Carlson on 12.12.2020.
//

#include "Constant.h"

Constant::Constant(RationalNumber value) : value(value), stringValue(value.to_str()) {
}

RationalNumber Constant::get_value() const {
    return value;
}

std::string Constant::get_name() {
    return stringValue;
}

std::string Constant::to_str() {
    return get_name();
}
