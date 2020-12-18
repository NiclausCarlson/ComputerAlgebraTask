//
// Created by Nik Carlson on 18.12.2020.
//

#include "WrongToken.h"

WrongToken::WrongToken(const std::string &message)
        :ParseException(std::move("Wrong token: " + message)) {}
