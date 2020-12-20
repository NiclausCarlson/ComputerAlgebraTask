//
// Created by Nik Carlson on 20.12.2020.
//

#include "UnsupportedOperation.h"

UnsupportedOperation::UnsupportedOperation(const std::string &message, const std::string &cause) :
        ParseException(std::move("Unsupported operation: " + message + " " + cause)) {
}
