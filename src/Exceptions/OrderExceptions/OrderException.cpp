//
// Created by Nik Carlson on 05.01.2021.
//

#include "OrderException.h"

OrderException::OrderException(std::string message) : message(std::move(message)) {
}

const char *OrderException::what() const noexcept {
    return message.c_str();
}
