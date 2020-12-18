//
// Created by Nik Carlson on 18.12.2020.
//

#include "ParseException.h"

ParseException::ParseException(std::string message) : message(std::move(message)) {
}

const char *ParseException::what() const noexcept {
    return message.c_str();
}
