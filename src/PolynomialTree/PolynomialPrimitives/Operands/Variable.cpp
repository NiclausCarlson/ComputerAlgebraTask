//
// Created by Nik Carlson on 12.12.2020.
//

#include "Variable.h"


Variable::Variable(std::string name) : name(std::move(name)) {
}

std::string Variable::get_value() const {
    return name;
}

std::string Variable::get_name() {
    return name;
}

std::string Variable::to_str() {
    return get_name();
}