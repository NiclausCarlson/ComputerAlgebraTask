//
// Created by Nik Carlson on 20.12.2020.
//

#include "InvalidArgument.h"

InvalidArgument::InvalidArgument(const std::string &message)
        : ParseException(std::move("Invalid argument: " + message)) {}
