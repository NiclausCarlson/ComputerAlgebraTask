//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_PARSEEXCEPTION_H
#define COMPUTERALGEBRATASK_PARSEEXCEPTION_H


#include <exception>
#include <string>

class ParseException : public std::exception {
private:
    std::string message;
public:
    explicit ParseException(std::string);

    const char *what() const noexcept override;
};


#endif //COMPUTERALGEBRATASK_PARSEEXCEPTION_H
