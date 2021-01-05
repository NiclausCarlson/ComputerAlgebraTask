//
// Created by Nik Carlson on 05.01.2021.
//

#include "UnexpectedOperationException.h"

UnexpectedOperationException::UnexpectedOperationException(std::string &message) :
        OrderException("Unexpected operation " + message + " in some order class. Ordering allows only monomials.") {
}
