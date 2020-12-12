//
// Created by Nik Carlson on 12.12.2020.
//

#include "Constant.h"

Constant::Constant(double value) : value(value), stringValue(std::to_string(value)) {
}

double Constant::get_double_value() const {
    return value;
}

std::string Constant::get_name() {
    return stringValue;
}

std::string Constant::to_str() {
    return get_name();
}
