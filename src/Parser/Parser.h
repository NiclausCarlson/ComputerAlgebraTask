//
// Created by Nik Carlson on 13.12.2020.
//

#ifndef COMPUTERALGEBRATASK_PARSER_H
#define COMPUTERALGEBRATASK_PARSER_H

#include <string>
#include "../PolynomialTree/PolynomialPrimitives/Node/Node.h"

class Parser {
private:
    std::string input_str;
    int curPos;

    std::string next_token();

public:
    Parser(std::string);

    PolynomialTree parse();
};


#endif //COMPUTERALGEBRATASK_PARSER_H
