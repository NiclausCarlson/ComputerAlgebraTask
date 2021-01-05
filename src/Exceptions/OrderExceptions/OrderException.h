//
// Created by Nik Carlson on 05.01.2021.
//

#ifndef COMPUTERALGEBRATASK_ORDEREXCEPTION_H
#define COMPUTERALGEBRATASK_ORDEREXCEPTION_H

#include <exception>
#include <string>

class OrderException : public std::exception {
private:
    std::string message;
public:
    explicit OrderException(std::string);

    const char *what() const noexcept override;
};


#endif //COMPUTERALGEBRATASK_ORDEREXCEPTION_H
