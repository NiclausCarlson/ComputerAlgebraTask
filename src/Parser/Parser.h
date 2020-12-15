//
// Created by Nik Carlson on 13.12.2020.
//

#ifndef COMPUTERALGEBRATASK_PARSER_H
#define COMPUTERALGEBRATASK_PARSER_H

#include <string>
#include "../PolynomialTree/PolynomialPrimitives/Node/Node.h"

class Parser {
private:
    std::string str;
    int cur_pos;
    int length;
    PolynomialTree polynomial;

    enum class Token {
        CONST,
        VARIABLE,
        UNARY_OPERATOR,
        BINARY_OPERATOR,
        END,
        ERROR
    };
    std::pair<Token, std::string> cur_token;

    void set_next_token();

    void tokenizer_helper(int (*)(int));

    void skip_whitespaces();

    PolynomialTree parseExponential();

    PolynomialTree parseProduct();

    PolynomialTree parseSum();

    PolynomialTree parseUnaryOperations();

    PolynomialTree parseConstAndVariables();

public:
    PolynomialTree parse(std::string);
};


#endif //COMPUTERALGEBRATASK_PARSER_H
