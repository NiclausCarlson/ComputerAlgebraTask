//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_UNEXPECTEDOPERATIONEXCEPTION_H
#define COMPUTERALGEBRATASK_UNEXPECTEDOPERATIONEXCEPTION_H


#include "OrderException.h"

class UnexpectedOperationException : public OrderException {
public:
    explicit UnexpectedOperationException(std::string&);
};


#endif //COMPUTERALGEBRATASK_UNEXPECTEDOPERATIONEXCEPTION_H
